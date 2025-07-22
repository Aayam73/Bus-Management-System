#include "paymenthandler.h"
#include <QDebug>
#include <QMessageBox>
#include <QQuickView>
#include <QQmlContext>

PaymentHandler::PaymentHandler(QObject *parent) : QObject(parent)
{
    m_view = new QQuickView();
    m_view->rootContext()->setContextProperty("paymentHandler",this);
    m_view->setResizeMode(QQuickView::SizeRootObjectToView);
    m_view->setSource(QUrl(QStringLiteral("qrc:/Qml/PaymentPage.qml")));
}

void PaymentHandler::processPayment(const QString &name, const QString &email, const QString &phone,
                                    bool isEsewa, const QString &paymentId, const QString &mpin)
{
    qDebug() << "Processing payment...";

    // Input Validations (similar to your original validateInputs(), but using signals)
    if (name.trimmed().isEmpty()) {
        emit onValidationError("nameField", "Please enter your name.");
        return;
    }
    if (email.trimmed().isEmpty()) {
        emit onValidationError("emailField", "Please enter your email.");
        return;
    }
    QString emailTrimmed = email.trimmed();
    if (!validateEmail(emailTrimmed)) {
        emit onValidationError("emailField", "Please enter a valid email address.");
        return;
    }

    if (phone.trimmed().isEmpty()) {
        emit onValidationError("phoneField", "Please enter your phone number.");
        return;
    }
    QString phoneTrimmed = phone.trimmed();
    if (!validatePhone(phoneTrimmed)) {
        emit onValidationError("phoneField", "Please enter a valid 10-digit phone no (starting 98/97).");
        return;
    }

    // Payment method specific validations
    if (isEsewa) {
        if (paymentId.trimmed().isEmpty()) {
            emit onValidationError("esewaId", "Please enter your eSewa ID.");
            return;
        }
        if (mpin.trimmed().isEmpty()) {
            emit onValidationError("esewaMpin", "Please enter your eSewa MPIN.");
            return;
        }
        QString mpinTrimmed = mpin.trimmed();
        if (!validateMpin(mpinTrimmed)) {
            emit onValidationError("esewaMpin", "Please enter a valid 4-digit eSewa MPIN.");
            return;
        }
    } else { // Khalti
        if (paymentId.trimmed().isEmpty()) {
            emit onValidationError("khaltiId", "Please enter your Khalti ID.");
            return;
        }
        if (mpin.trimmed().isEmpty()) {
            emit onValidationError("khaltiMpin", "Please enter your Khalti MPIN.");
            return;
        }
        QString kmpinTrimmed = mpin.trimmed(); // Using mpin for Khalti MPIN as well from function arg
        if (!validateMpin(kmpinTrimmed)) {
            emit onValidationError("khaltiMpin", "Please enter a valid 4-digit Khalti MPIN.");
            return;
        }
    }

    // If all validations pass
    QString method = isEsewa ? "eSewa" : "Khalti";
    qDebug() << "All inputs valid. Simulating payment success for:" << name << "via" << method;

    // In a real application, you'd integrate with a payment gateway here.
    // For this example, we'll just emit success.
    emit onPaymentSuccess("Thank you, " + name + "! Your payment was successful via " + method + ".");
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

QQuickView* PaymentHandler::view() const
{
    return m_view;
}
