#include "database.h"
#include <QDebug>
#include <QSqlError>

bool BusDB::initialize() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("bus_database.db");

    if (!db.open()) {
        qDebug() << "Error: Unable to open database!";
        return false;
    }
    qDebug() << "Database opened successfully.";

    QSqlQuery query;

    // 1. Create the buses table
    bool ok = query.exec(
        "CREATE TABLE IF NOT EXISTS buses ("
        "BusID INTEGER PRIMARY KEY AUTOINCREMENT,"
        "BusNO TEXT NOT NULL,"
        "Name TEXT NOT NULL,"
        "route_destination TEXT NOT NULL);"
        );

    if (!ok) {
        qDebug() << "Failed to create table:" << query.lastError();
        return false;
    } else {
        qDebug() << "Table created successfully.";
    }

    // 2. Insert sample row (optional; remove after dev)
    ok = query.exec(
        "INSERT INTO buses (BusNo, Name, route_destination) "
        "VALUES ('51634', 'Bus Company', 'KTM-PKR');"
        );

    if (!ok) {
        qDebug() << "Insert failed (might already exist):" << query.lastError();
    } else {
        qDebug() << "Sample data inserted.";
    }

    return true;
}
