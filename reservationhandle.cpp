#include "reservationhandle.h"
#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QPainter>
#include <QPdfWriter>
#include <QPixmap>
#include <QSqlError>
#include <QSqlQuery>
#include <QStandardPaths>
#include "qrcodegen.hpp"
using namespace qrcodegen;

ReservationHandler::ReservationHandler(QObject *parent)
    : QObject(parent)
{
    connectDatabase();
    cleanOldReservations();
}
void ReservationHandler::exportToPDF(const QString &fullName,
                                     const QString &route,
                                     const QString &date,
                                     const QString &seat,
                                     const QString &phone)
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

    //Header
    painter.setFont(headerFont);
    painter.drawText(x, y, "Ticket Receipt");

    y += sectionSpacing;

    //Ticket Info
    painter.setFont(regularFont);
    painter.drawText(x, y, "Passenger Name: " + fullName);
    y += lineSpacing;

    painter.drawText(x, y, "Phone NO: " + phone);
    y += lineSpacing;

    painter.drawText(x, y, "Seat No: " + seat);
    y += lineSpacing;

    painter.drawText(x, y, "Route: " + route);
    y += lineSpacing;

    painter.drawText(x, y, "Travel Date: " + date);
    y += lineSpacing;

    painter.drawText(x, y, "Issued: " + QDateTime::currentDateTime().toString("dd MMM yyyy hh:mm"));

    y += sectionSpacing + 55;

    // -------- QR Code --------
    using qrcodegen::QrCode;
    using qrcodegen::QrSegment;

    const QrCode qr
        = QrCode::encodeText(("Passenger: " + fullName + ", Seat: " + seat).toUtf8().constData(),
                             QrCode::Ecc::LOW);
    int qrSize = qr.getSize();
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

    // Thank You Message
    painter.setFont(italicFont);
    painter.drawText(x, y, "THANK YOU FOR CHOOSING US : HAMRO BUS SEWA");
    painter.end();
    qDebug() << "PDF file saved at:" << filePath;
}

bool ReservationHandler::connectDatabase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("bus_database.db");

    if (!db.open()) {
        qDebug() << "Database error: " << db.lastError().text();
        return false;
    }

    QSqlQuery query;
    QString create = R"(
        CREATE TABLE IF NOT EXISTS reservations (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT,
            phone TEXT,
            method TEXT,
            from_district TEXT,
            to_district TEXT,
            travel_date TEXT,
            reservation_date TEXT,
            seat TEXT,
            reference TEXT,
            amount REAL,
            user_id INTEGER
        )
    )";
    return query.exec(create);
}

bool ReservationHandler::saveReservation(QString name,
                                         QString phone,
                                         QString method,
                                         QString from,
                                         QString to,
                                         QString travelDate,
                                         QString seat,
                                         QString payRef,
                                         double amount)
{
    QSqlQuery query;
    query.prepare(R"(
        INSERT INTO reservations (name, phone, method, from_district, to_district, travel_date,
        reservation_date, seat, reference, amount, user_id)
        VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)
    )");
    query.addBindValue(name);
    query.addBindValue(phone);
    query.addBindValue(method);
    query.addBindValue(from);
    query.addBindValue(to);
    query.addBindValue(travelDate);
    query.addBindValue(QDateTime::currentDateTime().toString(Qt::ISODate));
    query.addBindValue(seat);
    query.addBindValue(payRef);
    query.addBindValue(amount);
    query.addBindValue(1); // replace with actual user ID later

    if (!query.exec()) {
        qDebug() << "Insert failed: " << query.lastError().text();
        return false;
    }

    return true;
}

void ReservationHandler::cleanOldReservations()
{
    QSqlQuery query;
    query.prepare("DELETE FROM reservations WHERE reservation_date <= datetime('now', '-1 day')");
    if (!query.exec()) {
        qDebug() << "Cleanup failed: " << query.lastError().text();
    }
}
