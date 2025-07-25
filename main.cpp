#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQuickControls2/QQuickStyle>
#include "reservationhandler.h"
#include <QtCore/QString>


using namespace Qt::StringLiterals;



int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQuickStyle::setStyle("Material");

    QQmlApplicationEngine engine;

    ReservationHandler reservationHandler;
    engine.rootContext()->setContextProperty("reservationHandler", &reservationHandler);
    QVariantMap booking;
    booking["name"] = "Test User";
    booking["phone"] = "9812345678";
    booking["paymentMethod"] = "Esewa";
    booking["from"] = "Kathmandu";
    booking["to"] = "Pokhara";
    booking["seatNumber"] = "A1";
    booking["reservationDate"] = "2025-07-26";
    engine.rootContext()->setContextProperty("booking", booking);

    const QUrl url(u"qrc:/ReservationWindow.qml"_s);

    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);

    engine.load(url);
    return app.exec();
}
