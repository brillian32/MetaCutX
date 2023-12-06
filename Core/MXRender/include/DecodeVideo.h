//
// Created by brillan on 2023/11/8.
//

#ifndef DECODEVIDEO_H
#define DECODEVIDEO_H

#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdint>
#include <opencv2/core/mat.hpp>

extern "C" {
#include <libavformat/avformat.h>
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>
#include <libavcodec/avcodec.h>
#include <libavutil/imgutils.h>
#include <libavutil/timestamp.h>
#include <libavutil/samplefmt.h>
#include "libavformat/avio.h"
}

#include "GlobalDef.h"
#include "functional"

class MX_API DecodeVideo
{
public:
	explicit DecodeVideo(std::string videoPath);
	~DecodeVideo();


	bool isDecoding();
	void pauseDecoding();
	void setDecodeBegin(int64 beginFrame);
	cv::Mat getDecodeBegin(std::function<void(cv::Mat&)>  getMat);
	void decodeVideo(std::function<void(cv::Mat&)>  getMat);
	void setOutputFilePath(std::string path);
	cv::Mat getFrameMat(int64_t frames);
	cv::Mat getFrameMat2(double percent);
	cv::Mat getFrameMatAtTime(int64_t timeStamp);
	double getDuration();
	int64_t getFrameCount();
	int64 getCurDecodeFrame();

private:
	void init();

private:
	std::string m_videoPath;
	std::string m_outputFilePath;
	int m_videoStreamIndex = -1;

	int64 m_beginFrame = 0;
	int64 m_currentDecodeFrame = 0;
	int64 m_beginTimeStamp = 0;

	bool m_isDecoding = false;
	bool m_isPausedDecoding = false;

	AVFormatContext* m_formatContext = nullptr;
	AVCodecContext* m_codecContext = nullptr;
	AVCodecParameters* m_codecParameters = nullptr;

	std::mutex m_mutex;
};


#endif //DECODEVIDEO_H
