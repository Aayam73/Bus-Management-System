#ifndef PAYMENTHANDLER_H
#define PAYMENTHANDLER_H

#include <QObject>
#include <QString>
#include <QDebug>

class PaymentHandler : public QObject
{
    Q_OBJECT
public:
    explicit PaymentHandler(QObject *parent = nullptr);

    Q_INVOKABLE void processPayment(const QString &name,
                                    const QString &email,
                                    const QString &phone,
                                    const QString &id,
                                    bool isEsewa,
                                    const QString &mpin);

signals:
    void validationFailed(const QString &message);
    void paymentProcessed(const QString &name, const QString &method);
};

#endif // PAYMENTHANDLER_H
