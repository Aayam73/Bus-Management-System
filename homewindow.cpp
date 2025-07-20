#include "homewindow.h"
#include "routemodel.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <utility>
#include <QSqlQuery>
#include <QStringList>
#include <QDebug>
#include <QCompleter>
#include <QQmlContext>



HomeWindow::HomeWindow(QObject *parent)
    : QObject(parent), m_model(new RouteModel(this)) {}

RouteModel *HomeWindow::model() const
{
    return m_model;
}

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
               price, bus_no, driver_info, drivers_cellno, seats,
               'Book' AS book
        FROM route_display
        WHERE from_district = :fromDistrict AND to_district = :toDistrict
    )");
    query.bindValue(":fromDistrict", "%" + from + "%");
    query.bindValue(":toDistrict", "%" + to + "%");

    if (!query.exec()) {
        qDebug() << "Query failed:" << query.lastError().text();
        return;
    }

    m_model->setQuery(std::move(query));
}

QStringList HomeWindow::getDistricts() const {
    QStringList list;
    QSqlDatabase db = QSqlDatabase::database("main");

    if (!db.isOpen()) {
        qDebug() << "DB not open";
        return list;
    }

    QSqlQuery query("SELECT district_name FROM districts", db);
    while (query.next()) {
        list << query.value(0).toString();
    }

    return list;
}


HomeWindow::~HomeWindow()
{
    if (m_view) {
        m_view->close();
        delete m_view;
    }
}

void HomeWindow::show() {
    if (!m_view) {
        m_view = new QQuickView();
        m_view->setResizeMode(QQuickView::SizeRootObjectToView);

        // Expose HomeWindow object
        m_view->rootContext()->setContextProperty("homeWindow", this);

        // Fetch and expose districts to QML
        QStringList districts = getDistricts();  // <-- make sure this method is defined
        m_view->rootContext()->setContextProperty("districtList", QVariant::fromValue(districts));

        m_view->setSource(QUrl("qrc:/Qml/HomePage.qml"));
    }

    m_view->show();
}



