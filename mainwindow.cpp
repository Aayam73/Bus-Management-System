#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QHeaderView>
#include <QTime>
#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Bus Filter Search");
    resize(900, 500);

    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    QVBoxLayout *mainLayout = new QVBoxLayout(central);

    // Filter inputs
    QHBoxLayout *filterLayout = new QHBoxLayout();

    QLabel *startLabel = new QLabel("Departure Location:");
    startEdit = new QLineEdit();
    startEdit->setPlaceholderText("e.g., Kathmandu");

    QLabel *endLabel = new QLabel("Arrival Location:");
    endEdit = new QLineEdit();
    endEdit->setPlaceholderText("e.g., Pokhara");

    QLabel *timeLabel = new QLabel("Departure Time:");
    timeEdit = new QTimeEdit();
    timeEdit->setDisplayFormat("HH:mm");
    timeEdit->setTime(QTime(0, 0));

    searchButton = new QPushButton("Search");

    connect(searchButton, &QPushButton::clicked, this, &MainWindow::handleSearch);

    filterLayout->addWidget(startLabel);
    filterLayout->addWidget(startEdit);
    filterLayout->addSpacing(10);
    filterLayout->addWidget(endLabel);
    filterLayout->addWidget(endEdit);
    filterLayout->addSpacing(10);
    filterLayout->addWidget(timeLabel);
    filterLayout->addWidget(timeEdit);
    filterLayout->addSpacing(10);
    filterLayout->addWidget(searchButton);

    mainLayout->addLayout(filterLayout);

    // Results table
    tableView = new QTableView();
    model = new QSqlTableModel(this);
    model->setTable("buses");
    model->select();  // Load all rows initially
    tableView->setModel(model);
    tableView->setEditTriggers(QTableView::NoEditTriggers);
    tableView->setSelectionBehavior(QTableView::SelectRows);
    tableView->horizontalHeader()->setStretchLastSection(true);
    tableView->setMinimumHeight(400);

    mainLayout->addWidget(tableView);
}

void MainWindow::handleSearch() {
    QString start = startEdit->text().trimmed();
    QString end = endEdit->text().trimmed();
    QString time = timeEdit->time().toString("HH:mm");

    QString filter = QString("route_destination LIKE '%%1%-%2%'")
     .arg(start, end); // Adjust this depending on your DB format

    QSqlTableModel *model = new QSqlTableModel(this);
    model->setTable("buses");
    model->setFilter(filter);
    model->select();

    tableView->setModel(model);
}

