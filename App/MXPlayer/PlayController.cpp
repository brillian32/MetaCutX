//
// Created by 17305 on 2023/11/30.
//

#include "PlayController.h"
#include "FrameProvider.h"
#include "MXSpdLog.h"
#include <QtConcurrent/QtConcurrent>
#include <QQmlEngine>
#if WIN32
#define VIDEO_FILE_PATH "C:\\Users\\17305\\Documents\\Wondershare\\Wondershare Filmora\\Output\\我的影片-1.mp4"
#else
#define VIDEO_FILE_PATH "/Users/brillan/Desktop/xingshan.mp4"
#endif



PlayController::PlayController()
{
	connect(this, &PlayController::sigFrameReady, FrameProvider::Instance(), &FrameProvider::deliverFrame);
	m_decoder = new DecodeVideo(VIDEO_FILE_PATH);
	m_decoder->setDecodeBegin(0);
}
PlayController::~PlayController()
{
	delete m_decoder;
}
void PlayController::play()
{
	QtConcurrent::run([this]() {
		m_decoder->decodeVideo([this](cv::Mat& mat, int64& curFrame) {
			emit sigFrameReady(mat, curFrame);
			m_curFrame = curFrame;
		});
		INFO("play end");
	});
}

void PlayController::setVideoDecoder(DecodeVideo* decoder)
{
	m_decoder = decoder;
}
void PlayController::nextFrame()
{
	pause();
	m_curFrame++;
	setCurrentFrame(m_curFrame);
}
void PlayController::preFrame()
{
	pause();
	if (m_curFrame <= 0)
	{
		return;
	}
	m_curFrame--;
	setCurrentFrame(m_curFrame);
}
void PlayController::setCurrentFrame(int64 curFrame)
{
//	QThread::msleep(1300);
	INFO("setCurrentFrame:{}", curFrame);
	m_curFrame = curFrame;
	m_decoder->setDecodeBegin(curFrame);
	m_decoder->getDecodeBegin([this](cv::Mat& mat, int64& curFrame) { emit sigFrameReady(mat, curFrame); });
}
bool PlayController::isPlaying()
{
	auto isDecoding = m_decoder->isDecoding();
	INFO( "isPlaying:{}", isDecoding);
	return isDecoding;
}
void PlayController::pause()
{
	m_decoder->pauseDecoding();
//	QThread::msleep(100);
	m_curFrame = m_decoder->getCurDecodeFrame();
	INFO("pause");
}

int64 PlayController::getFrameCount()
{
	return m_decoder->getFrameCount();
}
