#include "paymenthandler.h"
#include <QDebug>
#include <QMessageBox>

PaymentHandler::PaymentHandler(QObject *parent) : QObject(parent) {}

void PaymentHandler::processPayment(const QString &name, const QString &email, const QString &phone,
                                    bool isEsewa, const QString &paymentId, const QString &mpin)
{
    qDebug() << "Processing payment...";

    // Input Validations (similar to your original validateInputs(), but using signals)
    if (name.trimmed().isEmpty()) {
        emit validationError("nameField", "Please enter your name.");
        return;
    }
    if (email.trimmed().isEmpty()) {
        emit validationError("emailField", "Please enter your email.");
        return;
    }
    QString emailTrimmed = email.trimmed();
    if (!validateEmail(emailTrimmed)) {
        emit validationError("emailField", "Please enter a valid email address.");
        return;
    }

    if (phone.trimmed().isEmpty()) {
        emit validationError("phoneField", "Please enter your phone number.");
        return;
    }
    QString phoneTrimmed = phone.trimmed();
    if (!validatePhone(phoneTrimmed)) {
        emit validationError("phoneField", "Please enter a valid 10-digit phone no (starting 98/97).");
        return;
    }

    // Payment method specific validations
    if (isEsewa) {
        if (paymentId.trimmed().isEmpty()) {
            emit validationError("esewaId", "Please enter your eSewa ID.");
            return;
        }
        if (mpin.trimmed().isEmpty()) {
            emit validationError("esewaMpin", "Please enter your eSewa MPIN.");
            return;
        }
        QString mpinTrimmed = mpin.trimmed();
        if (!validateMpin(mpinTrimmed)) {
            emit validationError("esewaMpin", "Please enter a valid 4-digit eSewa MPIN.");
            return;
        }
    } else { // Khalti
        if (paymentId.trimmed().isEmpty()) {
            emit validationError("khaltiId", "Please enter your Khalti ID.");
            return;
        }
        if (mpin.trimmed().isEmpty()) {
            emit validationError("khaltiMpin", "Please enter your Khalti MPIN.");
            return;
        }
        QString kmpinTrimmed = mpin.trimmed(); // Using mpin for Khalti MPIN as well from function arg
        if (!validateMpin(kmpinTrimmed)) {
            emit validationError("khaltiMpin", "Please enter a valid 4-digit Khalti MPIN.");
            return;
        }
    }

    // If all validations pass
    QString method = isEsewa ? "eSewa" : "Khalti";
    qDebug() << "All inputs valid. Simulating payment success for:" << name << "via" << method;

    // In a real application, you'd integrate with a payment gateway here.
    // For this example, we'll just emit success.
    emit paymentSuccess("Thank you, " + name + "! Your payment was successful via " + method + ".");
    // emit paymentFlowComplete(); // Optional: signal to tell QML flow is done
}

bool PaymentHandler::validateEmail(const QString &email) {
    QRegularExpression emailRegex(R"(^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}$)");
    return emailRegex.match(email).hasMatch();
}

bool PaymentHandler::validatePhone(const QString &phone) {
    QRegularExpression phoneRegex(R"(^(98|97)\d{8}$)");
    return phoneRegex.match(phone).hasMatch();
}

bool PaymentHandler::validateMpin(const QString &mpin) {
    QRegularExpression mpinRegex(R"(^\d{4}$)");
    return mpinRegex.match(mpin).hasMatch();
}
