// paymenthandler.h
#ifndef PAYMENTHANDLER_H
#define PAYMENTHANDLER_H

#include <QObject>
#include <QString>
#include <QRegularExpression>

class PaymentHandler : public QObject
{
    Q_OBJECT
public:
    explicit PaymentHandler(QObject *parent = nullptr);

    // Q_INVOKABLE method callable from QML
    Q_INVOKABLE void processPayment(const QString &name, const QString &email, const QString &phone,
                                    bool isEsewa, const QString &paymentId, const QString &mpin);

signals:
    // Signals to communicate back to QML
    void paymentSuccess(const QString &message);
    void paymentFailed(const QString &errorMessage); // Good for general failures
    void validationError(const QString &fieldName, const QString &errorMessage); // For specific input issues
    void paymentFlowComplete(); // Optional: signal that payment process is done (success/fail)

private:
    // Private helper functions for validation
    bool validateEmail(const QString &email);
    bool validatePhone(const QString &phone);
    bool validateMpin(const QString &mpin);
};

#endif // PAYMENTHANDLER_H
