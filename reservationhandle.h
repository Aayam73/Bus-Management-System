#ifndef RESERVATIONHANDLE_H
#define RESERVATIONHANDLE_H

#include <QDateTime>
#include <QObject>
#include <QSqlDatabase>

class ReservationHandler : public QObject
{
    Q_OBJECT
public:
    explicit ReservationHandler(QObject *parent = nullptr);
    Q_INVOKABLE bool saveReservation(QString name,
                                     QString phone,
                                     QString method,
                                     QString from,
                                     QString to,
                                     QString travelDate,
                                     QString seat,
                                     QString payRef,
                                     double amount);
    Q_INVOKABLE void cleanOldReservations();
    Q_INVOKABLE void exportToPDF(const QString &fullName,
                                 const QString &route,
                                 const QString &date,
                                 const QString &seat,
                                 const QString &phone);

private:
    QSqlDatabase db;
    bool connectDatabase();
};

#endif // RESERVATIONHANDLE_H
