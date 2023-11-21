//
// Created by brillan on 2023/11/8.
//

#include "DecodeVideo.h"
#include <utility>
#include <QApplication>
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"
#include "qpixmap.h"
#include "QImage"
#include "QDebug"
#include "qpainter.h"

extern "C" {
#include <libavformat/avformat.h>
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>
#include <libavcodec/avcodec.h>
#include <libavutil/imgutils.h>
#include <libavutil/timestamp.h>		//av_ts2timestr
#include <libavutil/samplefmt.h>
#include "libavformat/avio.h"
}
#include "spdlog/spdlog.h"

// 创建Mat对象，并分配数据和行指针
void ConvertAVFrameToMat(AVFrame* frame)
{
	using namespace cv;
	Mat rgbMat;
	Mat yuv_I420;
	yuv_I420.create(frame->height * 3 / 2, frame->width, CV_8UC1);

	uint8_t* p_data = yuv_I420.data;
	for (int j = 0; j < frame->height; j++)
	{
		memcpy(p_data
			, frame->data[0] + j * frame->linesize[0], frame->width);
		p_data += frame->width;
	}

	for (int j = 0; j < frame->height / 2; j++)
	{
		memcpy(p_data
			, frame->data[1] + j * frame->linesize[1], frame->width / 2);
		p_data += frame->width / 2;

	}

	for (int j = 0; j < frame->height / 2; j++)
	{
		memcpy(p_data
			, frame->data[2] + j * frame->linesize[2], frame->width / 2);
		p_data += frame->width / 2;
	}
	cvtColor(yuv_I420, rgbMat, COLOR_YUV2BGR_I420);
	cv::imshow( "bgr_show", rgbMat);
	waitKey(1);
}

void DisplayFrame(const cv::Mat& frame) {
	cv::imshow("Frame", frame);
	cv::waitKey(1);  // 等待1毫秒，以更新显示
}
DecodeVideo::DecodeVideo(std::string videoPath)
{
	m_videoPath = std::move(videoPath);
	init();
}
DecodeVideo::~DecodeVideo()
= default;

cv::Mat AVFrame2CvMat(AVFrame *frame) {

	int width = frame->width;
	int height = frame->height;
	cv::Mat image(height, width, CV_8UC3);
	int cv_lines_sizes[1];
	cv_lines_sizes[0] = image.step1();
	SwsContext* conversion = sws_getContext(width, height, (AVPixelFormat)frame->format,
											width, height, AV_PIX_FMT_BGR24, SWS_FAST_BILINEAR,
											nullptr, nullptr, nullptr);

	sws_scale(conversion, frame->data, frame->linesize, 0, height, &image.data, cv_lines_sizes);
	sws_freeContext(conversion);
	return image;
}

void DecodeVideo::decodeVideo()
{
	// 初始化FFmpeg
//	av_register_all(); 4版本后已移除


	// 分配AVPacket和AVFrame
	AVPacket* packet = av_packet_alloc();
	AVFrame* frame = av_frame_alloc();

	// 读取帧数据
	while (av_read_frame(formatContext, packet) >= 0) {
		if (packet->stream_index == videoStreamIndex) {
			// 解码帧数据
			avcodec_send_packet(codecContext, packet);
			while (avcodec_receive_frame(codecContext, frame) == 0) {
				// 将AVFrame转换为OpenCV的Mat
//				 ConvertAVFrameToMat(frame);
				cv::Mat cvFrame = AVFrame2CvMat(frame);
				// 显示帧
				DisplayFrame(cvFrame);
			}
		}

		av_packet_unref(packet);
	}

	// 释放资源
	avformat_close_input(&formatContext);
	avcodec_free_context(&codecContext);
	av_frame_free(&frame);
	av_packet_free(&packet);


}

void DecodeVideo::setOutputFilePath(std::string path)
{
	m_outputFilePath = std::move(path);
}

void DecodeVideo::init()
{
	// 打开输入文件

	if (avformat_open_input(&formatContext, m_videoPath.c_str(), nullptr, nullptr) != 0) {
		// 处理打开文件错误
		spdlog::log(spdlog::level::err, "打开文件失败");
		return ;
	}

	// 查找视频流
	for (int i = 0; i < formatContext->nb_streams; i++) {
		if (formatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
			videoStreamIndex = i;
			codecParameters = formatContext->streams[i]->codecpar;
			break;
		}
	}

	if (videoStreamIndex == -1 || codecParameters == nullptr) {
		// 没有找到视频流
		spdlog::log(spdlog::level::err, "没有找到视频流");
		return ;
	}

	// 没有找到视频流
	const AVCodec *codec = avcodec_find_decoder(codecParameters->codec_id);
	if (!codec) {
		// 没有找到解码器
		spdlog::log(spdlog::level::err, "没有找到视频流失败1");
		return ;
	}

	codecContext = avcodec_alloc_context3(codec);
	if (!codecContext) {
		// 没有找到视频流
		spdlog::log(spdlog::level::err, "没有找到视频流");
		return ;
	}

	if (avcodec_parameters_to_context(codecContext, codecParameters) < 0) {
		// 填充解码器上下文失败
		spdlog::log(spdlog::level::err, "填充解码器上下文失败");
		return ;
	}

	if (avcodec_open2(codecContext, codec, nullptr) < 0) {
		// 打开解码器失败
		spdlog::log(spdlog::level::err, "打开解码器失败");
		return ;
	}
}
cv::Mat DecodeVideo::getFrameMat(double percentage)
{
	AVRational time_base = formatContext->streams[videoStreamIndex]->time_base;
	double duration = formatContext->streams[videoStreamIndex]->duration * av_q2d(time_base);
	double timestamp = percentage * duration;
	int64_t pts = timestamp / av_q2d(time_base);
	int ret = av_seek_frame(formatContext, videoStreamIndex, pts, AVSEEK_FLAG_BACKWARD);
	if (ret < 0) {
		return cv::Mat();
	}
	AVPacket *pkt = av_packet_alloc();

	// 读取帧数据
	while (av_read_frame(formatContext, pkt) >= 0) {
		if (pkt->stream_index == videoStreamIndex) {
			// 解码帧数据
			ret = avcodec_send_packet(codecContext, pkt);
			if (ret < 0) {
				return {};
			}
			AVFrame *seek_frame = av_frame_alloc();
			while (avcodec_receive_frame(codecContext, seek_frame) == 0) {
				// 将AVFrame转换为OpenCV的Mat
//				 ConvertAVFrameToMat(frame);
				cv::Mat cvFrame = AVFrame2CvMat(seek_frame);
				// 显示帧
//				DisplayFrame(cvFrame);
				av_packet_unref(pkt);
				return cvFrame;
			}
		}
	}
	return {};
}
