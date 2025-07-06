#include "homewindow.h"
#include "ui_homewindow.h"
#include "loginwindow.h"
#include "accountwindow.h"

HomeWindow::HomeWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::HomeWindow)
{
    ui->setupUi(this);
}

HomeWindow::~HomeWindow()
{
    delete ui;
}

void HomeWindow::on_btnSearch_clicked()
{

}

void HomeWindow::on_btnAccount_clicked()
{
    AccountWindow *account = new AccountWindow;
    this->hide();
    account->show();
}

