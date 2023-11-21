//
// Created by brillan on 2023/11/18.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "MXSpdLog.h"
#include <doctest/doctest.h>
#include "DecodeVideo.h"
#include "opencv2/opencv.hpp"

#define VIDEO_FILE_PATH "/Users/brillan/Desktop/xingshan.mp4"

TEST_CASE("Decode Video") {
	init_spdlog("test.log");

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
	}
	SUBCASE("play video")
	{
		DecodeVideo decode(VIDEO_FILE_PATH);
		LOG_RUN_TIME("play video");
		decode.decodeVideo();
	}
}


