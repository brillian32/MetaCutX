#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "FrameProvider.h"
#include "QQmlContext"
#include "QTimer"
#include <QVideoFrame>
#include "MXSpdLog.h"
#include "DecodeVideo.h"
#include <opencv2/opencv.hpp>
#define VIDEO_FILE_PATH "/Users/brillan/Desktop/xingshan.mp4"

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


//	qmlRegisterType<FrameProvider>("FrameProvider", 1, 0, "FrameProvider");

	engine.rootContext()->setContextProperty("frameProvider", FrameProvider::Instance());

	engine.load(url);

	DecodeVideo decode(VIDEO_FILE_PATH);
	decode.setDecodeBegin(18*30);
	decode.decodeVideo([](cv::Mat& mat){
		FrameProvider::Instance()->deliverFrame(mat);
	});

//	QTimer::singleShot(1000,&app,[](){
//		FrameProvider::Instance()->deliverFrame(QVideoFrame());
//	});


	return app.exec();
}
