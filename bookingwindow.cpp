#include "bookingwindow.h"
#include "homewindow.h"
#include "ui_bookingwindow.h"

BookingWindow::BookingWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BookingWindow)
{
    ui->setupUi(this);
}

BookingWindow::~BookingWindow()
{
    delete ui;
}

void BookingWindow::setRouteData(const QString &routeId, const QString &from,
                                 const QString &to, const QString &departure,
                                 const QString &arrival, const QString &price,
                                 const QString &bus, const QString &driver,
                                 const QString &phone, const QString &seats) {
    ui->labelRouteId->setText(routeId);
    ui->labelFrom->setText(from);
    ui->labelTo->setText(to);
    ui->labelDeparture->setText(departure);
    ui->labelArrival->setText(arrival);
    ui->labelPrice->setText(price);
    ui->labelBus->setText(bus);
    ui->labelDriver->setText(driver);
    ui->labelPhone->setText(phone);
    ui->labelSeats->setText(seats);


}

void BookingWindow::on_btnReturn_clicked()
{
    HomeWindow *home = new HomeWindow;
    home->show();
    this->close();

}


void BookingWindow::on_pushButton_clicked()
{

}

