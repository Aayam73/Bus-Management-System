#include "homewindow.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QStringList>
#include <QDebug>
#include <QCompleter>
#include <QQmlContext>

HomeWindow::HomeWindow(QObject *parent)
    : QObject(parent), m_districtModel(new QStringListModel(this)) {}

void HomeWindow::searchRoute(const QString &from, const QString &to)
{
    QSqlDatabase db = QSqlDatabase::database("main");
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return;
    }

    QSqlQuery query(db);
    query.prepare(R"(
        SELECT route_id, from_district, to_district, departure_time, arrival_time,
               price, bus_no, driver_info, drivers_cellno, seats
        FROM route_display
        WHERE from_district LIKE :fromDistrict AND to_district LIKE :toDistrict
    )");
    query.bindValue(":fromDistrict", "%" + from + "%");
    query.bindValue(":toDistrict", "%" + to + "%");

    if (!query.exec()) {
        qDebug() << "Query failed:" << query.lastError().text();
        return;
    }

    QVariantList routes;
    while (query.next()) {
        QVariantMap row;
        row["route_id"] = query.value("route_id");
        row["from_district"] = query.value("from_district");
        row["to_district"] = query.value("to_district");
        row["departure_time"] = query.value("departure_time");
        row["arrival_time"] = query.value("arrival_time");
        row["price"] = query.value("price");
        row["bus_no"] = query.value("bus_no");
        row["driver_info"] = query.value("driver_info");
        row["drivers_cellno"] = query.value("drivers_cellno");
        row["seats"] = query.value("seats");
        routes.append(row);
    }

    m_routes = routes;
    emit searchResultsReady(m_routes);
}

QStringList HomeWindow::getDistricts() const {
    QStringList list;
    QSqlDatabase db = QSqlDatabase::database("main");

    if (!db.isValid()) {
        qWarning() << "Database connection 'main' is not valid.";
        return list;
    }

    if (!db.isOpen() && !db.open()) {
        qWarning() << "Failed to open the database:" << db.lastError().text();
        return list;
    }

    QSqlQuery query(db);
    if (!query.exec("SELECT district_name FROM districts")) {
        qWarning() << "Failed to execute query:" << query.lastError().text();
        return list;
    }

    while (query.next()) {
        QString district = query.value(0).toString();
        qDebug() << "District:" << district;
        list << district;
    }

    return list;
}

HomeWindow::~HomeWindow()
{
    if (m_view) {
        m_view->hide();
        m_view->deleteLater();
        m_view = nullptr;
    }
}

void HomeWindow::show() {
    if (!m_view) {
        m_view = new QQuickView();
        m_view->setResizeMode(QQuickView::SizeRootObjectToView);

        QStringList districts = getDistricts();
        m_districtModel->setStringList(districts);

        m_view->rootContext()->setContextProperty("homeWindow", this);
        m_view->rootContext()->setContextProperty("districtModel", m_districtModel);
        m_view->setSource(QUrl("qrc:/Qml/HomePage.qml"));
    }
    m_view->show();
}
