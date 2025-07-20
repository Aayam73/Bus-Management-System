#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QUrl>

#include "PaymentHandler.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    PaymentHandler handler;  // ✅ This line actually uses the class
    engine.rootContext()->setContextProperty("paymentHandler", &handler);

    engine.load(QUrl(QStringLiteral("qrc:/paymentportal.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
