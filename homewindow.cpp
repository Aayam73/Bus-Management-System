#include "homewindow.h"
#include "ui_homewindow.h"
#include "accountwindow.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <utility>
#include <QSqlQuery>
#include <QStringList>
#include <QDebug>
#include <QCompleter>
#include "BookingButtonDelegate.h"
#include "bookingwindow.h"



HomeWindow::HomeWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::HomeWindow)
{
    ui->setupUi(this);
    model = new QSqlQueryModel(this);
    ui->tableView->setModel(model);

    QStringList districts;
    QSqlQuery query("SELECT district_name FROM districts");
    while (query.next()) {
        districts << query.value(0).toString();
    }

    QCompleter *completerFrom = new QCompleter(districts, this);
    completerFrom->setCaseSensitivity(Qt::CaseInsensitive);
    completerFrom->setFilterMode(Qt::MatchContains);
    ui->srchFrom->setCompleter(completerFrom);

    QCompleter *completerTo = new QCompleter(districts, this);
    completerTo->setCaseSensitivity(Qt::CaseInsensitive);
    completerTo->setFilterMode(Qt::MatchContains);
    ui->srchTo->setCompleter(completerTo);
}


HomeWindow::~HomeWindow()
{
    delete ui;
}

void HomeWindow::on_btnSearch_clicked()
{
    QString fromDistrict = ui->srchFrom->text();
    QString toDistrict = ui->srchTo->text();


    QString queryStr = R"(
        SELECT r.route_id, d1.district_name AS from_district, d2.district_name AS to_district,
               r.departure_time, r.arrival_time
        FROM routes r
        JOIN districts d1 ON r.from_district = d1.districts_id
        JOIN districts d2 ON r.to_district = d2.districts_id
        WHERE d1.district_name = :fromDistrict AND d2.district_name = :toDistrict
    )";

    QSqlQuery query;
    query.prepare(queryStr);
    query.bindValue(":fromDistrict", fromDistrict);
    query.bindValue(":toDistrict", toDistrict);

    if (!query.exec()) {
        QMessageBox::warning(this, "Search Error", query.lastError().text());
        return;
    }

    model->setQuery(std::move(query));


    // Add a column header name
    model->setHeaderData(4, Qt::Horizontal, "Book");

    // NOTE: QSqlQueryModel is read-only — use a delegate to simulate the button
    BookingButtonDelegate *delegate = new BookingButtonDelegate(this);
    ui->tableView->setItemDelegateForColumn(4, delegate);

    // Connect button click
    connect(delegate, &BookingButtonDelegate::bookButtonClicked, this, [=](const QModelIndex &index) {
        QString routeId = index.sibling(index.row(), 0).data().toString();
        QString from = index.sibling(index.row(), 1).data().toString();
        QString to = index.sibling(index.row(), 2).data().toString();
        QString departure = index.sibling(index.row(), 3).data().toString();

        BookingWindow *booking = new BookingWindow;
        booking->setRouteData(routeId, from, to, departure); // Define this method in BookingWindow
        booking->show();
        this->hide();
    });
}

void HomeWindow::on_btnAccount_clicked()
{
    AccountWindow *account = new AccountWindow;
    this->hide();
    account->show();
}

