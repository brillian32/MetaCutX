#include <iostream>
#include <MXRenderTest.h>
#include <QCoreApplication>
#include "DecodeVideo.h"

int main(int argc, char *argv[])
{
	MXRenderTest test;
	test.test();
	DecodeVideo decode("/Users/brillan/Desktop/xingshan.mp4");
	decode.setOutputFilePath("/Users/brillan/Desktop/1");
	decode.decodeVideo();
	return 0;
}
