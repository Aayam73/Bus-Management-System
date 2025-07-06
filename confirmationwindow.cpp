#include "confirmationwindow.h"
#include "ui_confirmationwindow.h"
#include "startwindow.h"
#include "accountwindow.h"

ConfirmationWindow::ConfirmationWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ConfirmationWindow)
{
    ui->setupUi(this);
}

ConfirmationWindow::~ConfirmationWindow()
{
    delete ui;
}

void ConfirmationWindow::on_buttonBox_accepted()
{
    StartWindow *start = new StartWindow;
    this->close();
    start->show();
}


void ConfirmationWindow::on_buttonBox_rejected()
{
    AccountWindow *account = new AccountWindow;
    this->close();
    account->show();
}

