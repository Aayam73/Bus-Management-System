
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


void connectToDatabase() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    QString dbPath = "database/bus_database.db";
    qDebug() << "Trying to open database at:" << dbPath;
    db.setDatabaseName(dbPath);
    if (!db.open()) {
        qDebug() << " Failed to open database:" << db.lastError().text();
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
    engine.rootContext()->setContextProperty("startWindow", &startWindow);
    engine.rootContext()->setContextProperty("signupWindow", &signup);
    engine.rootContext()->setContextProperty("loginWindow", &login);

    engine.load(QUrl("qrc:/Qml/StartPage.qml"));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

