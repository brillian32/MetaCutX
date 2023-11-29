
#ifndef FRAMEPROVIDER_H
#define FRAMEPROVIDER_H


#include <QObject>
#include <QVideoSink>
#include <QPointer>

class FrameProvider : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QVideoSink* videoSink READ videoSink WRITE setVideoSink NOTIFY videoSinkChanged)

public:
	explicit FrameProvider(QObject* parent = nullptr);
	~FrameProvider();

	QVideoSink* videoSink();
	void setVideoSink(QVideoSink* videoSink);

signals:
	void videoSinkChanged();

public slots:
	void deliverFrame(const QVideoFrame& frame);
	void debug();

private:

	QVideoFrame imageToVideoFrame(const QImage &image);
	QPointer<QVideoSink> m_videoSink;

};

#endif // FRAMEPROVIDER_H
