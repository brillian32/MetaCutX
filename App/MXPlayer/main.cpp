#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "FrameProvider.h"
#include "QQmlContext"
#include "QTimer"
#include <QVideoFrame>
#include "MXSpdLog.h"

int main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);

	init_spdlog("player");
	QQmlApplicationEngine engine;
	const QUrl url(u"qrc:/Player/main.qml"_qs);
	QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
		&app, [url](QObject *obj, const QUrl &objUrl) {
			if (!obj && url == objUrl)
				QCoreApplication::exit(-1);
		}, Qt::QueuedConnection);


//	qmlRegisterType<FrameProvider>("FrameProvider", 1, 0, "FrameProvider");
	auto frameProvider = new FrameProvider(&app);
	engine.rootContext()->setContextProperty("frameProvider", frameProvider);

	engine.load(url);

	QTimer::singleShot(1000,&app,[frameProvider](){
		frameProvider->deliverFrame(QVideoFrame());
	});


	return app.exec();
}
