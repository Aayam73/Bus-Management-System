#ifndef BUSDB_H
#define BUSDB_H

#include <QSqlDatabase>
#include <QSqlQuery>

class BusDB {
public:
    static bool initialize();
};

#endif // BUSDB_H
