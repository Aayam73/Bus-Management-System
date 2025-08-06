#include "reservationhandler.h"
#include "qrcodegen.hpp"
#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QPainter>
#include <QPdfWriter>
#include <QPixmap>
#include <QSqlError>
#include <QSqlQuery>
#include <QStandardPaths>
#include <QQuickView>
#include <QQmlContext>
#include <QQuickItem>
#include <QTimer>

using namespace qrcodegen;

ReservationHandler::ReservationHandler(QObject *parent)
    : QObject(parent)
{

    db = QSqlDatabase::database("main");
    if (!db.isOpen()) {
        if (!db.open()) {
            qWarning() << "Failed to open database in ReservationHandler:" << db.lastError().text();
        }
    }
    qDebug() << "DB connection name:" << db.connectionName();
    qDebug() << "DB file path:" << db.databaseName();
    qDebug() << "DB is open?" << db.isOpen();

    QSqlQuery check(db);
    check.exec("PRAGMA table_info(reservations)");
    while (check.next()) {
        qDebug() << "Column:" << check.value(1).toString();
    }
    if (!connectDatabase()) {
        qWarning() << "Failed to connect DB!";
    }
    QTimer *cleanupTimer = new QTimer(this);
    connect(cleanupTimer, &QTimer::timeout, this, &ReservationHandler::cleanOldReservations);
    cleanupTimer->start(24 * 60 * 60 * 1000);


    qDebug() << "Checking db in cleanOldReservations:" << db.connectionName() << db.isOpen();

    m_view = new QQuickView();
    m_view->rootContext()->setContextProperty("reservationHandler", this);
    m_view->setSource(QUrl("qrc:/Qml/ReservationWindow.qml"));
    m_view->setResizeMode(QQuickView::SizeRootObjectToView);
}

void ReservationHandler::decreaseAvailableSeats(const QString &routeId)
{
    const int numSeatsToDecrease = 1;

    qDebug() << "C++: Attempting to decrease seats for routeId:" << routeId << "by (hardcoded):" << numSeatsToDecrease;

    if (!db.isOpen()) {
        if (!connectDatabase()) {
            qWarning() << "DB is not open. Cannot decrease seats!";
            return;
        }
    }

    QSqlQuery query(db);
    query.prepare("UPDATE routes SET seats = MAX(0, seats - ?) WHERE route_id = ?");
    query.addBindValue(numSeatsToDecrease);
    query.addBindValue(routeId);

    if (query.exec()) {
        if (query.numRowsAffected() > 0) {
            qDebug() << "C++: Successfully decreased seats for routeId:" << routeId;
        } else {
            qWarning() << "C++: Failed to decrease seats. Route ID not found or no seats to update for:" << routeId;
        }
    } else {
        qWarning() << "C++ ERROR: Failed to execute seat decrease query:" << query.lastError().text();
    }
}

void ReservationHandler::exportToPDF(const QString &fullName,
                                     const QString &route,
                                     const QString &travelDate,
                                     const QString &phoneNumber,
                                     const QString &departureTime,
                                     const QString &arrivalTime,
                                     const QString &busNo,
                                     const QString &driverInfo,
                                     const QString &contactPhone,
                                     const QString &ticketPrice,
                                     const QString &method,
                                     const QString &reservationDate)
{
    QString filePath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)
    + QDir::separator() + "Ticket_"
        + QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss") + ".pdf";

    QPdfWriter writer(filePath);
    writer.setPageSize(QPageSize::A5);
    writer.setResolution(300);

    QPainter painter(&writer);

    // Layout
    int margin = 65;
    int x = margin;
    int y = margin;
    const int lineSpacing = 65;
    const int sectionSpacing = 80;

    // Fonts
    QFont headerFont("Arial", 25, QFont::Bold);
    QFont regularFont("Arial", 13);
    QFont italicFont("Arial", 15, QFont::StyleItalic);

    // Header
    painter.setFont(headerFont);
    painter.drawText(x, y, "Ticket Receipt");
    y += sectionSpacing;

    // Passenger Info
    painter.setFont(regularFont);
    painter.drawText(x, y, "Passenger Name: " + fullName); y += lineSpacing;
    painter.drawText(x, y, "Phone Number: " + phoneNumber); y += lineSpacing;
    painter.drawText(x, y, "Route: " + route); y += lineSpacing;
    painter.drawText(x, y, "Travel Date: " + travelDate); y += lineSpacing;
    painter.drawText(x, y, "Departure Time: " + departureTime); y += lineSpacing;
    painter.drawText(x, y, "Arrival Time: " + arrivalTime); y += lineSpacing;
    painter.drawText(x, y, "Bus No: " + busNo); y += lineSpacing;
    painter.drawText(x, y, "Driver: " + driverInfo); y += lineSpacing;
    painter.drawText(x, y, "Driver Contact: " + contactPhone); y += lineSpacing;
    painter.drawText(x, y, "Price: Rs. " + ticketPrice); y += lineSpacing;
    painter.drawText(x, y, "Payment Method: " + method); y += lineSpacing;
    painter.drawText(x, y, "Reservation Date: " + reservationDate); y += sectionSpacing + 20;

    // -------- QR Code --------
    using qrcodegen::QrCode;
    using qrcodegen::QrSegment;

    QString qrData = QString("Passenger: %1\nRoute: %2\nDate: %3\nPrice: Rs.%4")
                         .arg(fullName, route, travelDate, ticketPrice);

    const QrCode qr = QrCode::encodeText(qrData.toUtf8().constData(), QrCode::Ecc::LOW);
    const int qrSize = qr.getSize();
    const int scale = 8;

    int qrX = x;
    int qrY = y;

    for (int r = 0; r < qrSize; ++r) {
        for (int c = 0; c < qrSize; ++c) {
            if (qr.getModule(c, r)) {
                painter.fillRect(qrX + c * scale, qrY + r * scale, scale, scale, Qt::black);
            }
        }
    }

    y = qrY + qrSize * scale + sectionSpacing + 55;

    // Footer message
    painter.setFont(italicFont);
    painter.drawText(x, y, "THANK YOU FOR CHOOSING US : HAMRO BUS SEWA");

    painter.end();
    qDebug() << "PDF file saved at:" << filePath;
}



QString ReservationHandler::generateQRCode(const QString &data)
{
    using qrcodegen::QrCode;

    QrCode qr = QrCode::encodeText(data.toUtf8().constData(), QrCode::Ecc::LOW);

    int size = qr.getSize();
    QImage qrImage(size, size, QImage::Format_RGB888);
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            qrImage.setPixelColor(x, y, qr.getModule(x, y) ? Qt::black : Qt::white);
        }
    }

    // Save to temporary file
    QString tempDir = QStandardPaths::writableLocation(QStandardPaths::TempLocation);
    QDir().mkpath(tempDir);
    QString filePath = tempDir + "/ticket_qr.png";
    qrImage.scaled(200, 200, Qt::KeepAspectRatio).save(filePath);

    return filePath;
}


bool ReservationHandler::connectDatabase()
{

    if (!db.isOpen()) {
        qDebug() << "DB not open, trying to open...";
        if (!db.open()) {
            qWarning() << "Failed to open DB:" << db.lastError().text();
            return false;
        }
        qDebug() << "DB opened successfully.";
    } else {
        qDebug() << "DB already open.";
    }

    // Check or recreate the table
    QSqlQuery checkQuery(db);
    if (!checkQuery.exec("PRAGMA table_info(reservations);")) {
        qWarning() << "Failed to get table info:" << checkQuery.lastError().text();
        return false;
    }

    int columnCount = 0;
    while (checkQuery.next()) {
        columnCount++;
    }

    if (columnCount > 0 && columnCount != 17) {
        qDebug() << "Old table detected with" << columnCount << "columns. Dropping table.";

        // Close the DB connection first to avoid locking issues
        db.close();

        // Reopen the DB connection
        if (!db.open()) {
            qWarning() << "Failed to reopen DB:" << db.lastError().text();
            return false;
        }

        QSqlQuery dropQuery(db);
        if (!dropQuery.exec("DROP TABLE reservations;")) {
            qWarning() << "Failed to drop old table:" << dropQuery.lastError().text();
            return false;
        }
    }


    // (Re)create the table
    QSqlQuery createQuery(db);
    if (!createQuery.exec(R"(
        CREATE TABLE IF NOT EXISTS reservations (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT,
            email TEXT,
            phone TEXT,
            method TEXT,
            from_district TEXT,
            to_district TEXT,
            travel_date,
            reservation_date TEXT,
            seat TEXT,
            amount REAL,
            user_id INTEGER,
            departure_time TEXT,
            arrival_time TEXT,
            bus_no TEXT,
            driver_info TEXT,
            contact_phone_bus TEXT,
            route_id TEXT
        )
    )")) {
        qWarning() << "Create table failed:" << createQuery.lastError().text();
        return false;
    }

    if (!db.isOpen()) {
        if (!db.open()) {
            qWarning() << "DB failed to reopen after table creation:" << db.lastError().text();
            return false;
        }
    }

    qDebug() << "Table 'reservations' created/verified successfully.";
    return true;
}

void ReservationHandler::setRouteId(const QString &routeId)
{
    qDebug() << "setRouteId: isOpen =" << db.isOpen();

    if (!db.isOpen()) {
        if (!connectDatabase()) {
            qWarning() << "DB is not open. Cannot fetch route details!";
            return;
        }
    }

    m_routeId = routeId;
    emit routeIdChanged(routeId);

    // Fetch route details from the database
    QSqlQuery query(db);
    query.prepare(R"(
        SELECT from_district, to_district, date, departure_time, arrival_time,
               price, bus_no, driver_info, drivers_cellno, seats
        FROM routes1_view
        WHERE route_id = ?
    )");

    query.addBindValue(routeId.toInt());

    if (query.exec() && query.next()) {
        QString from = query.value(0).toString();
        QString to = query.value(1).toString();
        QDate date = QDate::fromString(query.value(2).toString(), "yyyy-MM-dd");
        QString departure = query.value(3).toString();
        QString arrival = query.value(4).toString();
        QString priceStr = query.value(5).toString();
        double price = priceStr.toDouble();
        QString bus = query.value(6).toString();
        QString driver = query.value(7).toString();
        QString phone = query.value(8).toString();
        QString seats = query.value(9).toString();

        // Push data into QML
        if (m_view && m_view->rootObject()) {
            QQuickItem *root = m_view->rootObject();
            root->setProperty("fromLocation", from);
            root->setProperty("toLocation", to);
            root->setProperty("date", date);
            root->setProperty("departureTime", departure);
            root->setProperty("arrivalTime", arrival);
            root->setProperty("ticketPrice", price);
            root->setProperty("busNo", bus);
            root->setProperty("driverInfo", driver);
            root->setProperty("contactPhone", phone);
            root->setProperty("seats", seats);
        }
    } else {
        qDebug() << "Failed to fetch route details for:" << routeId
                 << "Error:" << query.lastError().text();
    }
}




bool ReservationHandler::saveReservation(
    QString passengerName,
    QString passengerEmail,
    QString passengerPhone,
    QString method,
    QString routeId,
    int userId)
{
    if (!db.isOpen()) {
        if (!connectDatabase()) {
            qWarning() << "DB is not open. Cannot save reservation!";
            return false;
        }
    }

    // 1. Fetch data from DB using routeId
    QSqlQuery fetchQuery(db);
    fetchQuery.prepare(R"(
        SELECT from_district, to_district, departure_time, arrival_time,
               price, bus_no, driver_info, drivers_cellno, seats, date
        FROM routes1_view
        WHERE route_id = ?
    )");
    fetchQuery.addBindValue(routeId);

    if (!fetchQuery.exec() || !fetchQuery.next()) {
        qDebug() << "Failed to fetch route details for routeId:" << routeId
                 << "Error:" << fetchQuery.lastError().text();
        return false;
    }

    // Store values fetched from DB
    QString fromLocation   = fetchQuery.value(0).toString();
    QString toLocation     = fetchQuery.value(1).toString();
    QString departureTime  = fetchQuery.value(2).toString();
    QString arrivalTime    = fetchQuery.value(3).toString();
    QString ticketPrice    = fetchQuery.value(4).toString();
    QString busNo          = fetchQuery.value(5).toString();
    QString driverInfo     = fetchQuery.value(6).toString();
    QString contactPhoneBus= fetchQuery.value(7).toString();
    QString seats          = fetchQuery.value(8).toString();
    QDate travelDate = QDate::fromString(fetchQuery.value(9).toString(), "yyyy-MM-dd");

    // 2. Insert reservation into DB
    QSqlQuery query(db);
    query.prepare(R"(
        INSERT INTO reservations (
            name, email, phone, method, from_district, to_district, reservation_date,
            seat, amount, user_id, departure_time, arrival_time,
            bus_no, driver_info, contact_phone_bus, route_id, travel_date)
        VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)
    )");

    query.addBindValue(passengerName);
    query.addBindValue(passengerEmail);
    query.addBindValue(passengerPhone);
    query.addBindValue(method);
    query.addBindValue(fromLocation);
    query.addBindValue(toLocation);
    query.addBindValue(QDateTime::currentDateTime().toString(Qt::ISODate));
    query.addBindValue(seats);
    query.addBindValue(ticketPrice.toDouble());
    query.addBindValue(userId);
    query.addBindValue(departureTime);
    query.addBindValue(arrivalTime);
    query.addBindValue(busNo);
    query.addBindValue(driverInfo);
    query.addBindValue(contactPhoneBus);
    query.addBindValue(routeId);
    query.addBindValue(travelDate.toString(Qt::ISODate));

    if (!query.exec()) {
        qDebug() << "Insert failed:" << query.lastError().text();
        return false;
    }

    qDebug() << "Reservation saved successfully!";
    return true;
}



void ReservationHandler::cleanOldReservations()
{

    qDebug() << "cleanOldReservations db isOpen:" << db.isOpen();

    if (!db.isOpen()) {
        if (!db.open()) {
            qWarning() << "Failed to open DB during cleanup:" << db.lastError().text();
            return;
        }
    }

    QSqlQuery query(db);
    query.prepare("DELETE FROM reservations WHERE reservation_date <= datetime('now', '-1 day')");
    if (!query.exec()) {
        qDebug() << "Cleanup failed: " << query.lastError().text();
    } else {
        qDebug() << "Old reservations cleaned up.";
    }
}


QQuickView* ReservationHandler::view() const
{
    return m_view;
}

void ReservationHandler::openReservation(
    const QString &routeId,
    const QString &passengerName,
    const QString &passengerEmail,
    const QString &passengerPhone,
    const QString &paymentMethod)
{

    qDebug() << "openReservation called with:";
    qDebug() << "  routeId:" << routeId;
    qDebug() << "  passengerName:" << passengerName;
    qDebug() << "  passengerEmail:" << passengerEmail;
    qDebug() << "  passengerPhone:" << passengerPhone;
    qDebug() << "  paymentMethod:" << paymentMethod;

    // Store passenger info for later (if needed)
    m_fullName = passengerName;
    m_email = passengerEmail;
    m_phoneNumber = passengerPhone;
    m_method = paymentMethod;

    // Fetch route details
    setRouteId(routeId);

    // Push passenger details into QML
    if (m_view && m_view->rootObject()) {
        QQuickItem *root = m_view->rootObject();
        root->setProperty("fullName", passengerName);
        qDebug() << "C++ Setting QML fullName to:" << passengerName;
        root->setProperty("email", passengerEmail);
         qDebug() << "C++ Setting QML email to:" << passengerEmail;
        root->setProperty("phoneNumber", passengerPhone);
        root->setProperty("method", paymentMethod);
        root->setProperty("routeId", routeId);
    }

    // Show ReservationWindow
    m_view->show();
}



void ReservationHandler::show() {
    if (m_view) {
        m_view->show();
    }
}
void ReservationHandler::close(){
    if(m_view){
        m_view->close();
    }
}
