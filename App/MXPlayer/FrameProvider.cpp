
#include "FrameProvider.h"
#include "QDebug"
#include "QVideoFrame"

#include <QVideoFrameFormat>
#include <libyuv/convert_from_argb.h>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>
#include "MXSpdLog.h"
#include "qthread.h"


QVideoFrame  FrameProvider::imageToVideoFrame(const QImage &img)
{
	LOG_RUN_TIME("imageToVideoFrame");
	QVideoFrameFormat fmt( img.size(), QVideoFrameFormat::Format_RGBX8888 );
	QVideoFrame vf( fmt );
	vf.map( QVideoFrame::WriteOnly );
	memcpy(vf.bits(0),(void *)img.bits(), vf.bytesPerLine(0)*vf.height());
	vf.unmap();
	return vf;
}

QVideoFrame  FrameProvider::matToVideoFrame(cv::Mat mat)
{
	QVideoFrameFormat fmt(QSize(mat.cols, mat.rows), QVideoFrameFormat::Format_BGRA8888);
	QVideoFrame vf( fmt );
	vf.map( QVideoFrame::WriteOnly );
	memcpy(vf.bits(0),(void *)mat.data, mat.cols*mat.rows*mat.channels());
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

QImage MatToQImage(const cv::Mat& mat)
{
	// 8-bits unsigned, NO. OF CHANNELS = 1
	if(mat.type() == CV_8UC1)
	{
		QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
		// Set the color table (used to translate colour indexes to qRgb values)
		image.setColorCount(256);
		for(int i = 0; i < 256; i++)
		{
			image.setColor(i, qRgb(i, i, i));
		}
		// Copy input Mat
		uchar *pSrc = mat.data;
		for(int row = 0; row < mat.rows; row ++)
		{
			uchar *pDest = image.scanLine(row);
			memcpy(pDest, pSrc, mat.cols);
			pSrc += mat.step;
		}
		return image;
	}
		// 8-bits unsigned, NO. OF CHANNELS = 3
	else if(mat.type() == CV_8UC3)
	{
		// Copy input Mat
		const uchar *pSrc = (const uchar*)mat.data;
		// Create QImage with same dimensions as input Mat
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
		return image.rgbSwapped();
	}
	else if(mat.type() == CV_8UC4)
	{
		qDebug() << "CV_8UC4";
		// Copy input Mat
		const uchar *pSrc = (const uchar*)mat.data;
		cv::cvtColor(mat, mat, cv::COLOR_BGRA2RGBA);
		// Create QImage with same dimensions as input Mat
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB32);
		return image.copy();
	}
	else
	{
		qDebug() << "ERROR: Mat could not be converted to QImage.";
		return QImage();
	}
}

void FrameProvider::deliverFrame(cv::Mat mat) {
	if (m_videoSink.isNull())
		return;
//	LOG_RUN_TIME("deliverFrame");
	INFO("deliverFrame");
	auto frame2 = matToVideoFrame(mat);
	m_videoSink->setVideoFrame(frame2);
}

void FrameProvider::debug()
{
	qDebug() << "FrameProvider debug";
}
