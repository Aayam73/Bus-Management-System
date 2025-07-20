#include "PaymentHandler.h"
#include <QRegularExpression>
#include <QDebug>

PaymentHandler::PaymentHandler(QObject *parent) : QObject(parent) {}

void PaymentHandler::processPayment(const QString &name,
                                    const QString &email,
                                    const QString &phone,
                                    const QString &id,
                                    bool isEsewa,
                                    const QString &mpin)
{
    if (name.trimmed().isEmpty() || email.trimmed().isEmpty() || phone.trimmed().isEmpty()) {
        qDebug() << "Input Error: Missing name/email/phone";
        return;
    }

    QRegularExpression emailRegex(R"(^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}$)");
    if (!emailRegex.match(email).hasMatch()) {
        qDebug() << "Invalid email";
        return;
    }

    QRegularExpression phoneRegex(R"(^(98|97)\d{8}$)");
    if (!phoneRegex.match(phone).hasMatch()) {
        qDebug() << "Invalid phone number";
        return;
    }

    QRegularExpression mpinRegex(R"(^\d{4}$)");
    if (!mpinRegex.match(mpin).hasMatch()) {
        qDebug() << "Invalid MPIN";
        return;
    }

    QString method = isEsewa ? "eSewa" : "Khalti";
    qDebug() << "Payment successful via" << method << "for user" << name;
}
