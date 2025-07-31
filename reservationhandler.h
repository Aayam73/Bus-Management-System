#ifndef RESERVATIONHANDLE_H
#define RESERVATIONHANDLE_H

#include <QDateTime>
#include <QObject>
#include <QSqlDatabase>
#include <QQuickView>
extern int currentUserId;

class ReservationHandler : public QObject
{
    Q_OBJECT

public:
    explicit ReservationHandler(QObject *parent = nullptr);

    Q_INVOKABLE bool saveReservation(QString passengerName,
                                     QString passengerEmail,
                                     QString passengerPhone,
                                     QString method,
                                     QString routeId,
                                     int currentUserId);
    Q_INVOKABLE void cleanOldReservations();
    void setRouteId(const QString &routeId);
    Q_INVOKABLE void openReservation(
        const QString &routeId,
        const QString &passengerName,
        const QString &passengerEmail,
        const QString &passengerPhone,
        const QString &paymentMethod);
    Q_INVOKABLE void exportToPDF(const QString &fullName,
                                 const QString &route,
                                 const QString &travelDate,
                                 const QString &phoneNumber,
                                 const QString &seatNo,
                                 const QString &arrivalTime,
                                 const QString &departureTime,
                                 const QString &driverInfo,
                                 const QString &ticketPrice,
                                 const QString &contactPhone,
                                 const QString &reservationDate,
                                 const QString &method);
    QQuickView* view() const;
    Q_INVOKABLE QString generateQRCode(const QString &data);
    Q_INVOKABLE void decreaseAvailableSeats(const QString &routeId);
    void show();
    Q_INVOKABLE void close();

signals:
    void routeIdChanged(const QString &);
    void fromLocationChanged(const QString &);
    void toLocationChanged(const QString &);
    void departureTimeChanged(const QString &);
    void arrivalTimeChanged(const QString &);
    void ticketPriceChanged(const QString &);
    void busNoChanged(const QString &);
    void driverInfoChanged(const QString &);
    void contactPhoneChanged(const QString &);
    void seatNoChanged(const QString &);
    void fullNameChanged(const QString &);
    void emailChanged(const QString &);
    void phoneNumberChanged(const QString &);
    void methodChanged(const QString &);


private:
    QSqlDatabase db;
    QQuickView *m_view = nullptr;
    bool connectDatabase();
    QString m_routeId;
    QString m_fromLocation;
    QString m_toLocation;
    QString m_departureTime;
    QString m_arrivalTime;
    QString m_ticketPrice;
    QString m_busNo;
    QString m_driverInfo;
    QString m_contactPhone;
    QString m_seats;
    QString m_fullName;
    QString m_email;
    QString m_phoneNumber;
    QString m_method;
};

#endif // RESERVATIONHANDLE_H
