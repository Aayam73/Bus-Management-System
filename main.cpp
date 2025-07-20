
#include "homewindow.h"
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
    QDir().mkpath(dataDir);  // Make sure the directory exists

    QString dbPath = dataDir + "/bus_database.db";
    qDebug() << "Trying to open database at:" << dbPath;

    // Copy the default DB from resources if it doesn't exist
    if (!QFile::exists(dbPath)) {
        qDebug() << "Database file not found. Copying from resources...";
        if (!QFile::copy(":/assets/database/bus_database.db", dbPath)) {
            qDebug() << "Failed to copy default database.";
            QMessageBox::critical(nullptr, "Database Error", "Failed to copy default database from resources.");
            return;
        }
    }

    // Open database
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);
    if (!db.open()) {
        qDebug() << "Failed to open database:" << db.lastError().text();
        QMessageBox::critical(nullptr, "Database Error", "Failed to open database:\n" + db.lastError().text());
    } else {
        qDebug() << "Database connected successfully!";
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
    HomeWindow home;
    engine.rootContext()->setContextProperty("startWindow", &startWindow);
    engine.rootContext()->setContextProperty("signupWindow", &signup);
    engine.rootContext()->setContextProperty("loginWindow", &login);

    engine.load(QUrl("qrc:/Qml/StartPage.qml"));

    QObject::connect(&login, &LoginWindow::loginSuccess, [&]() {
        qDebug() << "Login successful. Closing QML and opening HomeWindow.";

        // Close QML view
        QObject *root = engine.rootObjects().first();
        if (auto window = qobject_cast<QWindow *>(root)) {
            window->close();
        }
    });

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

