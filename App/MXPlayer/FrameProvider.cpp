
#include "FrameProvider.h"
#include "QDebug"
#include "QVideoFrame"

#include <QVideoFrameFormat>
#include <libyuv/convert_from_argb.h>
#include "MXSpdLog.h"
#include "qthread.h"


QVideoFrame  FrameProvider::imageToVideoFrame(const QImage &img)
{
	LOG_RUN_TIME("imageToVideoFrame");
	QVideoFrameFormat fmt( img.size(), QVideoFrameFormat::Format_YUYV );
	QVideoFrame vf( fmt );
	vf.map( QVideoFrame::WriteOnly );
	libyuv::ARGBToYUY2( (const uint8_t*) img.bits(), img.bytesPerLine(), vf.bits( 0 ),
				   vf.bytesPerLine( 0 ), img.width(), img.height() );
	vf.unmap();
	return vf;
}

FrameProvider::FrameProvider(QObject *parent)
	: QObject{parent}
{

}

FrameProvider::~FrameProvider()
{

}

QVideoSink *FrameProvider::videoSink()
{
	return m_videoSink;
}

void FrameProvider::setVideoSink(QVideoSink *videoSink)
{
	m_videoSink = videoSink;
	qDebug() << "videoSinkChanged";
	emit videoSinkChanged();
}

void FrameProvider::deliverFrame(const QVideoFrame& frame) {
	if (m_videoSink.isNull())
		return;
	QImage image(2000, 1000, QImage::Format_ARGB32);
	image.fill(QColor(0, 255, 0, 10));
	auto frame2 =imageToVideoFrame(image);
	m_videoSink->setVideoFrame(frame2);
}

void FrameProvider::debug()
{
	qDebug() << "FrameProvider debug";
}
