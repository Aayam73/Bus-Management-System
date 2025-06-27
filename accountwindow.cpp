#include "accountwindow.h"
#include "ui_accountwindow.h"

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
