#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "FrameProvider.h"
#include "QQmlContext"
#include "QTimer"
#include <QVideoFrame>
#include "MXSpdLog.h"
#include "DecodeVideo.h"
#include "PlayController.h"
#include <opencv2/opencv.hpp>

#if WIN32
#define VIDEO_FILE_PATH "C:\\Users\\17305\\Documents\\Wondershare\\Wondershare Filmora\\Output\\我的影片.mp4"
#else
#define VIDEO_FILE_PATH "/Users/brillan/Desktop/xingshan.mp4"
#endif

int main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);

	initSpdLog("player");
	QQmlApplicationEngine engine;
	const QUrl url(u"qrc:/Player/main.qml"_qs);
	QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
		&app, [url](QObject *obj, const QUrl &objUrl) {
			if (!obj && url == objUrl)
				QCoreApplication::exit(-1);
		}, Qt::QueuedConnection);


	qmlRegisterType<PlayController>("MXPlayController", 1, 0, "PlayController");
//	qmlRegisterSingletonType<PlayController>("MXPlayController", 1, 0, "PlayController",getPlayController);
	engine.rootContext()->setContextProperty("frameProvider", FrameProvider::Instance());

	engine.load(url);

	return app.exec();
}
