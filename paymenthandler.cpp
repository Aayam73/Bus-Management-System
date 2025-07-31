#include "paymenthandler.h"
#include "reservationhandler.h"
#include <QDebug>
#include <QMessageBox>
#include <QQuickView>
#include <QQmlContext>
#include <QQuickItem>
#include <QSqlQuery>
#include <QSqlError>


PaymentHandler::PaymentHandler(QObject *parent) : QObject(parent)
{
    m_view = new QQuickView(nullptr);
    m_view->rootContext()->setContextProperty("paymentHandler",this);
    m_view->setResizeMode(QQuickView::SizeRootObjectToView);
    m_view->setSource(QUrl(QStringLiteral("qrc:/Qml/PaymentPage.qml")));
    m_view->rootContext()->setContextProperty("routeId", m_routeId);

    qDebug() << "QML status:" << m_view->status();
    QObject::connect(m_view, &QQuickView::statusChanged, [this](QQuickView::Status s) {
        qDebug() << "QQuickView status changed:" << s;

        if (s == QQuickView::Error) {
            for (const auto &err : m_view->errors()) {
                qDebug() << "QML error:" << err.toString();
            }
        }
    });
    connect(this, &PaymentHandler::onPaymentFailed, this, [this](const QString &msg){
        QMessageBox::warning(nullptr, "Booking Failed", msg);
    });

    connect(this, &PaymentHandler::seatsUpdated, this, [this](const QString &routeId, int seats){
        // Update UI seat count dynamically
        QObject *rootObj = m_view->rootObject();
        if (rootObj) {
            rootObj->setProperty("availableSeats", seats); // QML property
        }
    });
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

void PaymentHandler::setRouteId(const QString &routeId)
{
    if (m_routeId != routeId) {
        m_routeId = routeId;
        emit routeIdChanged();

        qDebug() << "PaymentHandler::routeId updated to:" << m_routeId;
    }
}

void PaymentHandler::payNowClicked(
    const QString &routeId,
    const QString &passengerName,
    const QString &passengerEmail,
    const QString &passengerPhone,
    const QString &paymentMethod)
{
    // Hide payment window
    if (m_view) m_view->hide();

    // Decrease seat count by 1, only if seats > 0
    QSqlDatabase db = QSqlDatabase::database("main"); // Use your existing connection
    if (!db.isOpen()) {
        qDebug() << "DB not open, attempting to open...";
        if (!db.open()) {
            qDebug() << "Failed to open DB:" << db.lastError().text();
            return;
        }
    }

    QSqlQuery query(db);

    // Update only if seats > 0
    query.prepare("UPDATE routes1 SET seats = seats - 1 WHERE route_id = :routeId AND seats > 0");

    query.bindValue(":routeId", routeId);

    if (!query.exec()) {
        qDebug() << "Error updating seats:" << query.lastError().text();
    } else if (query.numRowsAffected() == 0) {
        qDebug() << "No seats available for this route!";
        return;
    } else {
        qDebug() << "Seat count decreased for routeId:" << routeId;
    }


    QSqlQuery fetchQuery(db);
    fetchQuery.prepare("SELECT seats FROM routes1_view WHERE route_id = :routeId");
    fetchQuery.bindValue(":routeId", routeId);

    if (fetchQuery.exec() && fetchQuery.next()) {
        int updatedSeats = fetchQuery.value(0).toInt();
        emit seatsUpdated(routeId, updatedSeats); // Inform UI
        qDebug() << "Updated seats: " << updatedSeats;
    }

    if (!m_reservationHandler) {
        m_reservationHandler = new ReservationHandler(nullptr);
    }

    // Let ReservationHandler handle everything
    m_reservationHandler->openReservation(
        routeId, passengerName, passengerEmail, passengerPhone, paymentMethod);
}


QQuickView* PaymentHandler::view() const
{
    return m_view;
}
