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

    // Create completers for the 'From' and 'To' QLineEdit inputs
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

}

void HomeWindow::on_btnAccount_clicked()
{
    AccountWindow *account = new AccountWindow;
    this->hide();
    account->show();
}

