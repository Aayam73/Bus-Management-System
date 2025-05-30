#include "startwindow.h"
#include "ui_startwindow.h"
#include "loginwindow.h"
#include "signupwindow.h"


StartWindow::StartWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StartWindow)
{
    ui->setupUi(this);
}

StartWindow::~StartWindow()
{
    delete ui;
}

void StartWindow::on_btnLogin_clicked(){
    LoginWindow *login = new LoginWindow();
    login->show();
    this->hide();

}

void StartWindow::on_btnSignup_clicked(){
    SignupWindow *signup = new SignupWindow();
    signup->show();
    this->hide();
}
