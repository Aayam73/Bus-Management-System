#include "PaymentHandler.h"
#include <QRegularExpression>
#include <QDebug>
#include <QMetaObject>

PaymentHandler::PaymentHandler(QObject *parent) : QObject(parent) {}

void PaymentHandler::processPayment(const QString &name,
                                    const QString &email,
                                    const QString &phone,
                                    const QString &id,
                                    bool isEsewa,
                                    const QString &mpin)
{
    // Validate empty fields first
    if (name.trimmed().isEmpty()) {
        emit validationFailed("Name cannot be empty");
        qWarning() << "Payment failed: Empty name";
        return;
    }

    if (email.trimmed().isEmpty()) {
        emit validationFailed("Email cannot be empty");
        qWarning() << "Payment failed: Empty email";
        return;
    }

    if (phone.trimmed().isEmpty()) {
        emit validationFailed("Phone number cannot be empty");
        qWarning() << "Payment failed: Empty phone";
        return;
    }

    // Email validation
    static const QRegularExpression emailRegex(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    if (!emailRegex.match(email).hasMatch()) {
        emit validationFailed("Please enter a valid email address");
        qWarning() << "Payment failed: Invalid email format" << email;
        return;
    }

    // Phone validation (Nepali format)
    static const QRegularExpression phoneRegex(R"(^(98|97|96)[0-9]{8}$)");
    if (!phoneRegex.match(phone).hasMatch()) {
        emit validationFailed("Phone number must be 10 digits starting with 98, 97, or 96");
        qWarning() << "Payment failed: Invalid phone format" << phone;
        return;
    }

    // MPIN validation
    static const QRegularExpression mpinRegex(R"(^\d{4,6}$)");
    if (!mpinRegex.match(mpin).hasMatch()) {
        QString error = isEsewa ? "MPIN must be 4-6 digits" : "Password must be at least 4 characters";
        emit validationFailed(error);
        qWarning() << "Payment failed: Invalid credentials";
        return;
    }

    // Payment processing simulation
    QString method = isEsewa ? "eSewa" : "Khalti";
    qInfo() << "Processing" << method << "payment for:" << name;
    qDebug() << "Details - Email:" << email << "| Phone:" << phone << "| ID:" << id;

    // Simulate network delay
    QMetaObject::invokeMethod(this, [this, name, method]() {
        emit paymentProcessed(name, method);
        qInfo() << "Payment successful for" << name << "via" << method;
    }, Qt::QueuedConnection);
}
