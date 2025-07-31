
#include "bookingwindow.h"
#include "homewindow.h"
#include "paymenthandler.h"
#include "startwindow.h"
#include "signupwindow.h"
#include "loginwindow.h"
#include "reservationhandler.h"
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
#include <QFile> // Added for QFile::copy and QFile::exists

void connectToDatabase() {
    QString dataDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(dataDir); // Ensure the directory exists
    QString dbPath = dataDir + "/bus_database.db";
    qDebug() << "Trying to open database at:" << dbPath;

    // Copy database from resources if it doesn't exist in the data directory
    if (!QFile::exists(dbPath)) {
        qDebug() << "Database not found at" << dbPath << ". Copying from resources...";
        if (QFile::copy(":/assets/database/bus_database.db", dbPath)) {
            QFile dbFile(dbPath);
            // Set permissions to ensure the application can read and write to the copied database file
            if (!dbFile.setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner)) {
                qWarning() << "Failed to set write permissions on database file:" << dbPath;
                // This might not be a fatal error, but it's good to log
            }
            qDebug() << "Database copied successfully to:" << dbPath;
        } else {
            qWarning() << "Failed to copy database from ':/assets/database/bus_database.db' to" << dbPath;
            QMessageBox::critical(nullptr, "Database Error", "Unable to copy default database. Application cannot start.");
            return; // Critical error: cannot proceed without the database file
        }
    }

    // Check if a connection named "main" already exists and is open
    if (QSqlDatabase::contains("main")) {
        QSqlDatabase db = QSqlDatabase::database("main");
        if (db.isOpen()) {
            qDebug() << "Database connection 'main' already exists and is open.";
            return; // Database is already connected and open, nothing more to do
        } else {
            qDebug() << "Database connection 'main' exists but is not open. Attempting to open...";
            // If it exists but is not open, try to open it
            if (!db.open()) {
                qWarning() << "Failed to re-open existing database connection 'main':" << db.lastError().text();
                QMessageBox::critical(nullptr, "Database Error", "Failed to re-open existing database connection: " + db.lastError().text());
                return;
            } else {
                qDebug() << "Existing database connection 'main' successfully re-opened.";
                return;
            }
        }
    }

    // If no "main" connection exists, add and open a new one
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "main");
    db.setDatabaseName(dbPath);

    if (!db.open()) {
        qWarning() << "Database open error for new connection 'main':" << db.lastError().text();
        QMessageBox::critical(nullptr, "Database Error", "Failed to open database: " + db.lastError().text());
        // Consider exiting the application here as the database is crucial
        // QCoreApplication::exit(-1);
    } else {
        qDebug() << "New database connection 'main' opened successfully!";
    }
}



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    connectToDatabase();
        qDebug() << "Qt version:" << QT_VERSION_STR;
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QQuickStyle::setStyle("Fusion");  // or "Basic", "Material"

    QQmlApplicationEngine engine;

    StartWindow startWindow;
    SignupWindow signup;
    LoginWindow login;
    HomeWindow homeWindow;
    BookingWindow bookingWindow;
    PaymentHandler paymentHandler;
    ReservationHandler reservationHandler;
    engine.rootContext()->setContextProperty("startWindow", &startWindow);
    engine.rootContext()->setContextProperty("signupWindow", &signup);
    engine.rootContext()->setContextProperty("loginWindow", &login);
    engine.rootContext()->setContextProperty("homeWindow", &homeWindow);
    engine.rootContext()->setContextProperty("bookingWindow", &bookingWindow);
    engine.rootContext()->setContextProperty("paymentHandler", &paymentHandler);
    engine.rootContext()->setContextProperty("reservationHandler", &reservationHandler);

    const QUrl url(QStringLiteral("qrc:/Qml/ReservationWindow.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
                         if (!obj && url == objUrl)
                             QCoreApplication::exit(-1);
                     }, Qt::QueuedConnection);

    engine.load(QUrl("qrc:/Qml/StartPage.qml"));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

