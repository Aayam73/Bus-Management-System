
#include "startwindow.h"
#include <QApplication>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QCoreApplication>
#include <QDir>

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
    QApplication a(argc, argv);
    connectToDatabase();
    StartWindow w;
    w.show();
    return a.exec();
}

