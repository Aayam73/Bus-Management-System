#include "accountwindow.h"
#include "ui_accountwindow.h"
#include "homewindow.h"
#include "confirmationwindow.h"

AccountWindow::AccountWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AccountWindow)
{
    ui->setupUi(this);
}

AccountWindow::~AccountWindow()
{
    delete ui;
}

void AccountWindow::on_btnReturn_clicked()
{
    HomeWindow *home = new HomeWindow;
    this->hide();
    home->show();
}


void AccountWindow::on_btnLogout_clicked()
{
    ConfirmationWindow *confirm = new ConfirmationWindow;
    this->close();
    confirm->show();
}

