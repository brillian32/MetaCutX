#include <iostream>
#include <MXRenderTest.h>
#include <QCoreApplication>
#include "DecodeVideo.h"

int main(int argc, char *argv[])
{
	MXRenderTest test;
	test.test();
	DecodeVideo decode("C:\\Users\\16940\\20231121_112745.mp4");
	decode.setOutputFilePath("/Users/brillan/Desktop/1");
	decode.decodeVideo();
	return 0;
}
