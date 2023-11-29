
#ifndef FRAMEPROVIDER_H
#define FRAMEPROVIDER_H


#include <QObject>
#include <QVideoSink>
#include <QPointer>
#include <opencv2/core/mat.hpp>
#include "Singleton.h"

class FrameProvider : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QVideoSink* videoSink READ videoSink WRITE setVideoSink NOTIFY videoSinkChanged)
	DECLARE_SINGLETON(FrameProvider)

public:
	explicit FrameProvider(QObject* parent = nullptr);
	~FrameProvider();

	QVideoSink* videoSink();
	void setVideoSink(QVideoSink* videoSink);

signals:
	void videoSinkChanged();

public slots:
	void deliverFrame(cv::Mat frame);
	void debug();

private:

	QVideoFrame imageToVideoFrame(const QImage &image);
	QPointer<QVideoSink> m_videoSink;

};

#endif // FRAMEPROVIDER_H
