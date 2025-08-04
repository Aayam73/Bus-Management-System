#ifndef PAYMENTHANDLER_H
#define PAYMENTHANDLER_H

#include <QObject>
#include <QString>
#include <QRegularExpression>
#include <QQuickView>
#include "reservationhandler.h"
#include "sessionmanager.h"


class PaymentHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString routeId READ routeId WRITE setRouteId NOTIFY routeIdChanged)
public:
    explicit PaymentHandler(SessionManager* sessionManager, QObject *parent = nullptr);

    // Q_INVOKABLE method callable from QML
    Q_INVOKABLE void processPayment(const QString &name, const QString &email, const QString &phone,
                                    bool isEsewa, const QString &paymentId, const QString &mpin);
    void setRouteId(const QString &routeId);
    QString routeId() const { return m_routeId; }
    QQuickView* view() const;
    Q_INVOKABLE void payNowClicked(
        const QString &routeId,
        const QString &passengerName,
        const QString &passengerEmail,
        const QString &passengerPhone,
        const QString &paymentMethod);


signals:
    // Signals to communicate back to QML
    void onPaymentSuccess(const QString &message);
    void onPaymentFailed(const QString &errorMessage); // Good for general failures
    void onValidationError(const QString &fieldName, const QString &errorMessage); // For specific input issues
    void paymentFlowComplete(); // Optional: signal that payment process is done (success/fail)
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
    void routeIdChanged();
    void seatsUpdated(const QString &routeId, int seats);

private:
    // Private helper functions for validation
    SessionManager* m_sessionManager = nullptr;
    bool validateEmail(const QString &email);
    bool validatePhone(const QString &phone);
    bool validateMpin(const QString &mpin);
    QQuickView *m_view = nullptr;
    ReservationHandler *m_reservationHandler = nullptr;
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
    QSqlDatabase db;
    bool connectDatabase();
};

#endif // PAYMENTHANDLER_H
