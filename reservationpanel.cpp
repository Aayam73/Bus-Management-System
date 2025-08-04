#include "reservationpanel.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

ReservationPanel::ReservationPanel(SessionManager *sessionManager, QObject *parent)
    : QAbstractListModel(parent), m_sessionManager(sessionManager)
{
}

int ReservationPanel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return m_reservations.count();
}

QVariant ReservationPanel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= m_reservations.count())
        return QVariant();

    const QVariantMap &reservation = m_reservations.at(index.row());

    switch(role) {
    case FromDistrictRole:
        return reservation.value("fromDistrict");
    case ToDistrictRole:
        return reservation.value("toDistrict");
    case TravelDateRole:
        return reservation.value("travelDate");
    case AmountRole:
        return reservation.value("amount");
    case DepartureTimeRole:
        return reservation.value("departureTime");
    case ArrivalTimeRole:
        return reservation.value("arrivalTime");
    case BusNoRole:
        return reservation.value("busNo");
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> ReservationPanel::roleNames() const
{
    return {
        { FromDistrictRole, "fromDistrict" },
        { ToDistrictRole, "toDistrict" },
        { TravelDateRole, "travelDate" },
        { AmountRole, "amount" },
        { DepartureTimeRole, "departureTime" },
        { ArrivalTimeRole, "arrivalTime" },
        { BusNoRole, "busNo" }
    };
}

void ReservationPanel::fetchReservations()
{
    beginResetModel();
    m_reservations.clear();

    int userId = m_sessionManager->userId();
    if (userId == -1) {
        qWarning() << "User not logged in!";
        endResetModel();
        return;
    }

    QSqlDatabase db = QSqlDatabase::database("main");
    if (!db.isOpen()) {
        qWarning() << "Database not open!";
        endResetModel();
        return;
    }

    QSqlQuery query(db);
    query.prepare("SELECT from_district, to_district, travel_date, amount, departure_time, arrival_time, bus_no "
                  "FROM reservations WHERE user_id = :userId");
    query.bindValue(":userId", userId);

    if (!query.exec()) {
        qWarning() << "Failed to fetch reservations:" << query.lastError().text();
        endResetModel();
        return;
    }

    while (query.next()) {
        QVariantMap reservationItem;
        reservationItem["fromDistrict"] = query.value("from_district").toString();
        reservationItem["toDistrict"] = query.value("to_district").toString();
        reservationItem["travelDate"] = query.value("travel_date").toString();
        reservationItem["amount"] = query.value("amount").toDouble();
        reservationItem["departureTime"] = query.value("departure_time").toString();
        reservationItem["arrivalTime"] = query.value("arrival_time").toString();
        reservationItem["busNo"] = query.value("bus_no").toString();

        m_reservations.append(reservationItem);
    }

    endResetModel();
}
