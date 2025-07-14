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
                                 const QString &to, const QString &departure) {
    ui->labelRouteId->setText(routeId);
    ui->labelFrom->setText(from);
    ui->labelTo->setText(to);
    ui->labelDeparture->setText(departure);


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

