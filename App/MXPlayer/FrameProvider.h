
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
	void frameChanged(int64 currentFrame);

public slots:
	void deliverFrame(cv::Mat frame,int64 curFrameNum);
	void debug();

private:
	QVideoFrame imageToVideoFrame(const QImage &image);
	QVideoFrame matToVideoFrame(cv::Mat mat);


	QPointer<QVideoSink> m_videoSink;


};

#endif // FRAMEPROVIDER_H
