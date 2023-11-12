#include <iostream>
#include <MXRenderTest.h>
#include <QCoreApplication>
#include "DecodeVideo.h"
#include <spdlog/spdlog.h>

int main(int argc, char *argv[])
{
	spdlog::set_level(spdlog::level::info);
	QCoreApplication app(argc, argv);
	std::cout << "Hello, World!" << std::endl;
	MXRenderTest test;
	test.test();
	DecodeVideo decode("/Users/brillan/Desktop/xingshan.mp4");
	decode.setOutputFilePath("/Users/brillan/Desktop/1");
	decode.decodeVideo();
//	decode.decodeVideo();
	return 0;
}
