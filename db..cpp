
#include <QCoreApplication>
#include <QtSql>
#include <QDebug>

    int main(int argc, char *argv[])
    {
        QCoreApplication a(argc, argv);

        // 1. Setup SQLite database connection
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");  // SQLite driver
        db.setDatabaseName("bus_database.db");                   // SQLite file

        if (!db.open()) {
            qDebug() << "Error: Unable to open database!";
            return -1;
        }
        qDebug() << "Database opened successfully.";

        QSqlQuery query;

        // 2. Create the buses table
        bool ok = query.exec(
            "CREATE TABLE IF NOT EXISTS buses ("
            "busid INTEGER PRIMARY KEY AUTOINCREMENT,"
            "busno TEXT NOT NULL,"
            "busname TEXT NOT NULL,"
            "route_destination TEXT NOT NULL);"
            );

        if (!ok) {
            qDebug() << "Failed to create table:" << query.lastError();
        } else {
            qDebug() << "Table created successfully.";
        }

        // 3. Insert a sample row
        ok = query.exec(
            "INSERT INTO buses (busno, busname, route_destination) "
            "VALUES ('51634', 'Jayalaxmi Super Deluxe', 'KTM-PKR');"
            );

        if (!ok) {
            qDebug() << "Insert failed:" << query.lastError();
        } else {
            qDebug() << "Data inserted successfully.";
        }

        // 4. Select and display all rows
        ok = query.exec("SELECT busid, busno, busname, route_destination FROM buses;");

        if (!ok) {
            qDebug() << "Select failed:" << query.lastError();
        } else {
            qDebug() << "\nBus Table Contents:";
            while (query.next()) {
                int id = query.value(0).toInt();
                QString busno = query.value(1).toString();
                QString busname = query.value(2).toString();
                QString route = query.value(3).toString();

                qDebug() << "ID:" << id
                         << "| Bus No:" << busno
                         << "| Name:" << busname
                         << "| Route:" << route;
            }
        }

        return a.exec();
    }

