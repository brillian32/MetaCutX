//
// Created by brillan on 2023/11/18.
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "MXSpdLog.h"
#include <doctest/doctest.h>
#include "DecodeVideo.h"
#include "opencv2/opencv.hpp"


TEST_CASE("Decode Video") {
	init_spdlog("test.log");
	spdlog::info("Decode Video");
	DecodeVideo decode("/Users/brillan/Desktop/xingshan.mp4");
	decode.setOutputFilePath("/Users/brillan/Desktop/1");

	SUBCASE("get frame")
	{
		spdlog::info("get frame");
		CHECK(!decode.getFrameMat(1).empty());
		spdlog::info("get end");
	}
	SUBCASE("play video")
	{
		decode.decodeVideo();
	}
}


