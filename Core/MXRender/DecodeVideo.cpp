//
// Created by brillan on 2023/11/8.
//

#include "DecodeVideo.h"
#include <utility>
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"


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
#include "MXSpdLog.h"


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
//	cv::imshow("Frame", frame);
//	cv::waitKey(1);  // 等待1毫秒，以更新显示
}
DecodeVideo::DecodeVideo(std::string videoPath)
{
	m_videoPath = std::move(videoPath);
	init();
}
DecodeVideo::~DecodeVideo()
{
	// 释放资源
	avformat_close_input(&m_formatContext);
	avcodec_free_context(&m_codecContext);
}

cv::Mat AVFrame2CvMat(AVFrame *frame) {

	int width = frame->width;
	int height = frame->height;
	cv::Mat image(height, width, CV_8UC4);
	int cv_lines_sizes[1];
	cv_lines_sizes[0] = image.step1();
	SwsContext* conversion = sws_getContext(width, height, (AVPixelFormat)frame->format,
											width, height, AV_PIX_FMT_BGRA, SWS_FAST_BILINEAR,
											nullptr, nullptr, nullptr);

	sws_scale(conversion, frame->data, frame->linesize, 0, height, &image.data, cv_lines_sizes);
	sws_freeContext(conversion);
	return image;
}

void DecodeVideo::setDecodeBegin(int64 beginFrame)
{
	std::unique_lock lock(m_mutexDecode);
	AVRational time_base = m_formatContext->streams[m_videoStreamIndex]->time_base;
	AVRational frame_rate = m_formatContext->streams[m_videoStreamIndex]->r_frame_rate;

	m_beginFrame = beginFrame;
	m_currentDecodeFrame = beginFrame;

	int64 targetTime = (double)beginFrame/(double)av_q2d(frame_rate)/(double)av_q2d(time_base);
	m_beginTimeStamp = targetTime;
	INFO("seek frame to targetTime {}", targetTime);
	auto ret = av_seek_frame(m_formatContext, m_videoStreamIndex, targetTime,  AVSEEK_FLAG_BACKWARD);
	if (ret < 0) {
		ERROR("seek frame error");
	}
}

void DecodeVideo::decodeVideo(std::function<void(cv::Mat&,int64& curFrame)>  getMat)
{
	std::unique_lock lock(m_mutexDecode);
	m_isPausedDecoding = false;
	m_mutex.lock();
	m_isDecoding = true;
	m_mutex.unlock();
	AVPacket* packet = av_packet_alloc();
	AVFrame* frame = av_frame_alloc();

	// 读取帧数据
	while (av_read_frame(m_formatContext, packet) >= 0) {
		if (packet->stream_index == m_videoStreamIndex) {
			// 解码帧数据
			if(m_isPausedDecoding)
			{
				m_mutex.lock();
				m_isDecoding = false;
				m_mutex.unlock();
				return;
			}
			avcodec_send_packet(m_codecContext, packet);
			while (avcodec_receive_frame(m_codecContext, frame) == 0) {
				// 将AVFrame转换为OpenCV的Mat
//				 ConvertAVFrameToMat(frame);
				if(m_isPausedDecoding)
				{
					m_mutex.lock();
					m_isDecoding = false;
					m_mutex.unlock();
					return;
				}
				cv::Mat cvFrame = AVFrame2CvMat(frame);
				// 显示帧
				m_currentDecodeFrame++;
				DisplayFrame(cvFrame);
				getMat(cvFrame,m_currentDecodeFrame);
			}
		}
		av_packet_unref(packet);
	}

	av_frame_free(&frame);
	av_packet_free(&packet);
	m_mutex.lock();
	m_isDecoding = false;
	m_mutex.unlock();
}

void DecodeVideo::init()
{
	// 打开输入文件

	if (avformat_open_input(&m_formatContext, m_videoPath.c_str(), nullptr, nullptr) != 0) {
		// 处理打开文件错误
		spdlog::log(spdlog::level::err, "打开文件失败");
		return ;
	}

	// 查找视频流
	for (int i = 0; i < m_formatContext->nb_streams; i++) {
		if (m_formatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
			m_videoStreamIndex = i;
			m_codecParameters = m_formatContext->streams[i]->codecpar;
			break;
		}
	}

	if (m_videoStreamIndex == -1 || m_codecParameters == nullptr) {
		// 没有找到视频流
		spdlog::log(spdlog::level::err, "没有找到视频流");
		return ;
	}

	// 没有找到视频流
	const AVCodec *codec = avcodec_find_decoder(m_codecParameters->codec_id);
	if (!codec) {
		// 没有找到解码器
		spdlog::log(spdlog::level::err, "没有找到视频流失败1");
		return ;
	}

	m_codecContext = avcodec_alloc_context3(codec);
	if (!m_codecContext) {
		// 没有找到视频流
		spdlog::log(spdlog::level::err, "没有找到视频流");
		return ;
	}

	if (avcodec_parameters_to_context(m_codecContext, m_codecParameters) < 0) {
		// 填充解码器上下文失败
		spdlog::log(spdlog::level::err, "填充解码器上下文失败");
		return ;
	}

	if (avcodec_open2(m_codecContext, codec, nullptr) < 0) {
		// 打开解码器失败
		spdlog::log(spdlog::level::err, "打开解码器失败");
		return ;
	}
}
cv::Mat DecodeVideo::getFrameMat2(double percentage)
{
	AVRational time_base = m_formatContext->streams[m_videoStreamIndex]->time_base;
	double duration = m_formatContext->streams[m_videoStreamIndex]->duration * av_q2d(time_base);
	double timestamp = percentage * duration;
	int64_t pts = timestamp / av_q2d(time_base);
	int ret = av_seek_frame(m_formatContext, m_videoStreamIndex, pts, AVSEEK_FLAG_BACKWARD);
	if (ret < 0) {
		return cv::Mat();
	}
	AVPacket *pkt = av_packet_alloc();

	// 读取帧数据
	while (av_read_frame(m_formatContext, pkt) >= 0) {
		if (pkt->stream_index == m_videoStreamIndex) {
			// 解码帧数据
			ret = avcodec_send_packet(m_codecContext, pkt);
			if (ret < 0) {
				return {};
			}
			AVFrame *seek_frame = av_frame_alloc();
			while (avcodec_receive_frame(m_codecContext, seek_frame) == 0) {
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
double DecodeVideo::getDuration()
{
	AVRational time_base = m_formatContext->streams[m_videoStreamIndex]->time_base;
	double duration = m_formatContext->streams[m_videoStreamIndex]->duration * av_q2d(time_base);
	return duration;
}
cv::Mat DecodeVideo::getFrameMat(int64_t frames)
{
	AVRational time_base = m_formatContext->streams[m_videoStreamIndex]->time_base;
	auto cntFrames = m_formatContext->streams[m_videoStreamIndex]->nb_frames;
	double duration = m_formatContext->streams[m_videoStreamIndex]->duration;
	int64_t timestamp = frames*1.0/cntFrames * duration;
	int ret = av_seek_frame(m_formatContext, m_videoStreamIndex, timestamp, AVSEEK_FLAG_BACKWARD);
	if (ret < 0) {
		return cv::Mat();
	}
	AVPacket *pkt = av_packet_alloc();

	// 读取帧数据
	while (av_read_frame(m_formatContext, pkt) >= 0) {
		if (pkt->stream_index == m_videoStreamIndex) {
			// 解码帧数据
			ret = avcodec_send_packet(m_codecContext, pkt);
			if (ret < 0) {
				return {};
			}
			AVFrame *seek_frame = av_frame_alloc();
			while (avcodec_receive_frame(m_codecContext, seek_frame) == 0) {
				// 将AVFrame转换为OpenCV的Mat
//				 ConvertAVFrameToMat(frame);
				cv::Mat cvFrame = AVFrame2CvMat(seek_frame);
				// 显示帧
				DisplayFrame(cvFrame);
				av_packet_unref(pkt);
				return cvFrame;
			}
		}
	}
	av_packet_unref(pkt);
	return {};
}

cv::Mat DecodeVideo::getFrameMatAtTime(int64_t timeStamp)
{
	AVRational time_base = m_formatContext->streams[m_videoStreamIndex]->time_base;
	int64_t timestamp = timeStamp / av_q2d(time_base);
	int ret = av_seek_frame(m_formatContext, m_videoStreamIndex, timestamp, AVSEEK_FLAG_BACKWARD);
	if (ret < 0) {
		return cv::Mat();
	}
	AVPacket *pkt = av_packet_alloc();

	// 读取帧数据
	while (av_read_frame(m_formatContext, pkt) >= 0) {
		if (pkt->stream_index == m_videoStreamIndex) {
			// 解码帧数据
			ret = avcodec_send_packet(m_codecContext, pkt);
			if (ret < 0) {
				return {};
			}
			AVFrame *seek_frame = av_frame_alloc();
			while (avcodec_receive_frame(m_codecContext, seek_frame) == 0) {
				// 将AVFrame转换为OpenCV的Mat
//				 ConvertAVFrameToMat(frame);
				cv::Mat cvFrame = AVFrame2CvMat(seek_frame);
				// 显示帧
				DisplayFrame(cvFrame);
				av_packet_unref(pkt);
				return cvFrame;
			}
		}
	}
	av_packet_unref(pkt);
	return {};
}
cv::Mat DecodeVideo::getDecodeBegin(std::function<void(cv::Mat&, int64& curFrame)>  getMat)
{
	std::unique_lock lock(m_mutexDecode);
	AVPacket* packet = av_packet_alloc();
	AVFrame* frame = av_frame_alloc();
	// 读取帧数据
	while (av_read_frame(m_formatContext, packet) >= 0) {
		if (packet->stream_index == m_videoStreamIndex) {
			// 解码帧数据
			avcodec_send_packet(m_codecContext, packet);
			while (avcodec_receive_frame(m_codecContext, frame) == 0) {
				// 将AVFrame转换为OpenCV的Mat
//				 ConvertAVFrameToMat(frame);
				cv::Mat cvFrame = AVFrame2CvMat(frame);
				// 显示帧
				DisplayFrame(cvFrame);
				if (frame->pkt_dts >= m_beginTimeStamp) {
					DEBUG("pts:{}", frame->pts);
					DEBUG("pkt_dts:{}", frame->pkt_dts);
					DEBUG("time_base:{:.9}", av_q2d(frame->time_base));
					DEBUG("is keyFrame:{}", frame->key_frame==1);
					DEBUG("Frame type:{}",(int)frame->pict_type);
					av_frame_free(&frame);
					av_packet_free(&packet);
					getMat(cvFrame, m_beginFrame);
					return cvFrame;
				}
			}
		}
	}

	av_frame_free(&frame);
	av_packet_free(&packet);
	return {};
}

bool DecodeVideo::isDecoding()
{
	std::unique_lock<std::mutex> lock(m_mutex);
	return m_isDecoding;
}

void DecodeVideo::pauseDecoding()
{
	m_isPausedDecoding = true;
}

int64_t DecodeVideo::getFrameCount()
{
	auto cntFrames =m_formatContext->streams[m_videoStreamIndex]->nb_frames;
	DEBUG("cntFrames:{}", cntFrames);
	DEBUG("duration:{}", m_formatContext->streams[m_videoStreamIndex]->duration);
	DEBUG("time_base:{:.9}", av_q2d(m_formatContext->streams[m_videoStreamIndex]->time_base));
	DEBUG("avg_frame_rate:{:.9}", av_q2d(m_formatContext->streams[m_videoStreamIndex]->avg_frame_rate));
	DEBUG("r_frame_rate:{:.9}", av_q2d(m_formatContext->streams[m_videoStreamIndex]->r_frame_rate));
	return cntFrames;
}
int64 DecodeVideo::getCurDecodeFrame()
{
	return m_currentDecodeFrame;
}

