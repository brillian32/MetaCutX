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

class DecodeVideo
{
public:
	explicit DecodeVideo(std::string videoPath);
	~DecodeVideo();


	void decodeVideo();
	void setOutputFilePath(std::string path);
	cv::Mat getFrameMat(int64_t frames);
	cv::Mat getFrameMat2(double percent);
	double getDuration();

private:
	void init();

private:
	std::string m_videoPath;
	std::string m_outputFilePath;

	AVFormatContext* formatContext = nullptr;
	int videoStreamIndex = -1;
	AVCodecContext* codecContext = nullptr;
	AVCodecParameters* codecParameters = nullptr;

};


#endif //DECODEVIDEO_H
