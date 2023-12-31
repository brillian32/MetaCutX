//
// Created by brillan on 2023/11/18.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "DecodeVideo.h"
#include "MXSpdLog.h"
#include "opencv2/opencv.hpp"

#include <doctest/doctest.h>

#if WIN32
#define VIDEO_FILE_PATH "C:\\Users\\17305\\Documents\\Wondershare\\Wondershare Filmora\\Output\\我的影片.mp4"
#else
#define VIDEO_FILE_PATH "/Users/brillan/Desktop/xingshan.mp4"
#endif

TEST_CASE("log init")
{
	initSpdLog("test2.log");
}

TEST_CASE("Decode Video")
{
	SUBCASE("init")
	{
		LOG_RUN_TIME("init");
		DecodeVideo decode(VIDEO_FILE_PATH);
	}

	SUBCASE("get frame")
	{
		DecodeVideo decode(VIDEO_FILE_PATH);
		LOG_RUN_TIME("get frame");
		CHECK(!decode.getFrameMat2(1.0).empty());
		CHECK(!decode.getFrameMat(60).empty());
		decode.getDuration();
		CHECK(!decode.getFrameMatAtTime(575).empty());
	}
}

TEST_CASE("play video")
{
	DecodeVideo decode(VIDEO_FILE_PATH);
	LOG_RUN_TIME("play video");
	decode.setDecodeBegin(18 * 30);
	//	decode.decodeVideo();
}
