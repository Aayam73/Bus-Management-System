
#include "bookingwindow.h"
#include "homewindow.h"
#include "paymenthandler.h"
#include "startwindow.h"
#include "signupwindow.h"
#include "loginwindow.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QCoreApplication>
#include <QDir>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtCore/qurl.h>
#include <QQuickStyle>
#include <QApplication>
#include <QStandardPaths>



void connectToDatabase() {
    QString dataDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(dataDir);
    QString dbPath = dataDir + "/bus_database.db";
    qDebug() << "Trying to open database at:" << dbPath;

    // Copy if DB doesn't exist
    if (!QFile::exists(dbPath)) {
        qDebug() << "Database not found. Copying from resources...";
        if (QFile::copy(":/assets/database/bus_database.db", dbPath)) {
            QFile dbFile(dbPath);
            if (!dbFile.setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner)) {
                qWarning() << "Failed to set write permissions on database.";
            }
        } else {
            qWarning() << "Failed to copy database.";
            QMessageBox::critical(nullptr, "Database Error", "Unable to copy default database.");
            return;
        }
    }

    // Open with a named connection
    if (!QSqlDatabase::contains("main")) {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "main");
        db.setDatabaseName(dbPath);
        db.open();
        if (!db.open()) {
            qWarning() << "Database open error:" << db.lastError().text();
            QMessageBox::critical(nullptr, "Database Error", db.lastError().text());
        } else {
            qDebug() << "Database opened successfully!";
        }
    }
}


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    connectToDatabase();

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QQuickStyle::setStyle("Fusion");  // or "Basic", "Material"

    QQmlApplicationEngine engine;

    StartWindow startWindow;
    SignupWindow signup;
    LoginWindow login;
    HomeWindow homeWindow;
    BookingWindow bookingWindow;
    PaymentHandler paymentHandler;
    engine.rootContext()->setContextProperty("startWindow", &startWindow);
    engine.rootContext()->setContextProperty("signupWindow", &signup);
    engine.rootContext()->setContextProperty("loginWindow", &login);
    engine.rootContext()->setContextProperty("homeWindow", &homeWindow);
    engine.rootContext()->setContextProperty("bookingWindow", &bookingWindow);
    engine.rootContext()->setContextProperty("paymentHandler", &paymentHandler);

    engine.load(QUrl("qrc:/Qml/StartPage.qml"));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

