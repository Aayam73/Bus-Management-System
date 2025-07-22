#ifndef BOOKINGWINDOW_H
#define BOOKINGWINDOW_H

#include "paymenthandler.h"
#include <QObject>
#include <QQuickView>

class BookingWindow : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString routeId READ routeId NOTIFY routeIdChanged)
    Q_PROPERTY(QString fromLocation READ fromLocation NOTIFY fromLocationChanged)
    Q_PROPERTY(QString toLocation READ toLocation NOTIFY toLocationChanged)
    Q_PROPERTY(QString departureTime READ departureTime NOTIFY departureTimeChanged)
    Q_PROPERTY(QString arrivalTime READ arrivalTime NOTIFY arrivalTimeChanged)
    Q_PROPERTY(QString ticketPrice READ ticketPrice NOTIFY ticketPriceChanged)
    Q_PROPERTY(QString busNo READ busNo NOTIFY busNoChanged)
    Q_PROPERTY(QString driverInfo READ driverInfo NOTIFY driverInfoChanged)
    Q_PROPERTY(QString contactPhone READ contactPhone NOTIFY contactPhoneChanged)
    Q_PROPERTY(QString seatNo READ seatNo NOTIFY seatNoChanged)

public:
    explicit BookingWindow(QObject *parent = nullptr);
    ~BookingWindow();

    // Getter methods for properties
    QString routeId() const { return m_routeId; }
    QString fromLocation() const { return m_fromLocation; }
    QString toLocation() const { return m_toLocation; }
    QString departureTime() const { return m_departureTime; }
    QString arrivalTime() const { return m_arrivalTime; }
    QString ticketPrice() const { return m_ticketPrice; }
    QString busNo() const { return m_busNo; }
    QString driverInfo() const { return m_driverInfo; }
    QString contactPhone() const { return m_contactPhone; }
    QString seatNo() const { return m_seatNo;}

    // Method to set all route data at once
    void setRouteData(const QString &routeId, const QString &from,
                      const QString &to, const QString &departure,
                      const QString &arrival, const QString &price,
                      const QString &bus, const QString &driver,
                      const QString &phone, const QString &seats);

    Q_INVOKABLE void showHomeWindow();
    Q_INVOKABLE void payNowClicked();
    Q_INVOKABLE void closeWindow();
    QQuickView* view() const { return m_view; }

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

private:
    QQuickView *m_view = nullptr;
    PaymentHandler *m_paymentHandler = nullptr;
    QString m_routeId;
    QString m_fromLocation;
    QString m_toLocation;
    QString m_departureTime;
    QString m_arrivalTime;
    QString m_ticketPrice;
    QString m_busNo;
    QString m_driverInfo;
    QString m_contactPhone;
    QString m_seatNo;
};

#endif // BOOKINGWINDOW_H
