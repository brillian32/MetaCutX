//
// Created by 16940 on 2023/11/22.
//

#include <QGuiApplication>
//#include <QQmlApplicationEngine>
#include <QUrl>
#include <QtQml/QQmlApplicationEngine>
#include <QObject>


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/resourceEditor/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
                if (!obj && url == objUrl)
                    QCoreApplication::exit(-1);
            }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
