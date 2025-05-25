#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QHeaderView>
#include <QTime>

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

    QLabel *startLabel = new QLabel("Start Destination:");
    startEdit = new QLineEdit();
    startEdit->setPlaceholderText("e.g., Kathmandu");

    QLabel *endLabel = new QLabel("End Destination:");
    endEdit = new QLineEdit();
    endEdit->setPlaceholderText("e.g., Pokhara");

    QLabel *timeLabel = new QLabel("Departure Time:");
    timeEdit = new QTimeEdit();
    timeEdit->setDisplayFormat("HH:mm");
    timeEdit->setTime(QTime(0, 0));

    searchButton = new QPushButton("Search");

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
    tableView->setEditTriggers(QTableView::NoEditTriggers);
    tableView->setSelectionBehavior(QTableView::SelectRows);
    tableView->horizontalHeader()->setStretchLastSection(true);
    tableView->setMinimumHeight(400);

    mainLayout->addWidget(tableView);
}
