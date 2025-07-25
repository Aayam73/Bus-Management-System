#ifndef RESERVATIONHANDLER_H
#define RESERVATIONHANDLER_H

#include <QObject>
#include <QSqlDatabase>
#include <QDateTime>

class ReservationHandler : public QObject
{
    Q_OBJECT
public:
    explicit ReservationHandler(QObject *parent = nullptr);
    Q_INVOKABLE bool saveReservation(QString name, QString phone, QString method,
                                     QString from, QString to, QString travelDate,
                                     QString seat, QString payRef, double amount);
    Q_INVOKABLE void cleanOldReservations();
    Q_INVOKABLE void exportToPDF(const QString &fullName, const QString &route, const QString &date, const QString &seat, const QString &phone);


private:
    QSqlDatabase db;
    bool connectDatabase();
};

#endif // RESERVATIONHANDLER_H
