#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include <QIcon>
#include <QPalette>

#include "PaymentHandler.h"

int main(int argc, char *argv[])
{
    // Core settings
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    // Set this BEFORE creating QGuiApplication
  // Or "Material", "Basic"
    QGuiApplication app(argc, argv);
    app.setApplicationName("Payment Portal");
    app.setWindowIcon(QIcon(":/assets/icon.png"));

    // Style configuration (try these in order if Fusion doesn't work
    // Set palette for Fusion styl

    QQmlApplicationEngine engine;

    // Register C++ components
    PaymentHandler paymentHandler;
    engine.rootContext()->setContextProperty("paymentHandler", &paymentHandler);

    // Load QML with error handling
    const QUrl qmlUrl(QStringLiteral("qrc:/paymentportal.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [qmlUrl](QObject *obj, const QUrl &objUrl) {
                         if (!obj && qmlUrl == objUrl)
                             QCoreApplication::exit(-1);
                     }, Qt::QueuedConnection);

    engine.load(qmlUrl);

    return app.exec();
}
