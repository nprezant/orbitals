#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuick3D/qquick3d.h>

#include "orbitalsinterface.h"

int main(int argc, char* argv[])
{
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);
  qmlRegisterType<OrbitalsInterface>("OrbitalsInterface", 1, 0, "OrbitalsInterface");
  qmlRegisterType<OrbitalChangeData>("OrbitalsInterface", 1, 0, "OrbitalChangeData");

  QSurfaceFormat::setDefaultFormat(QQuick3D::idealSurfaceFormat(4));

  QQmlApplicationEngine engine;
  const QUrl url(QStringLiteral("qrc:/main.qml"));
  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreated, &app,
      [url](QObject* obj, const QUrl& objUrl) {
        if (!obj && url == objUrl)
          QCoreApplication::exit(-1);
      },
      Qt::QueuedConnection);
  engine.load(url);

  return app.exec();
}