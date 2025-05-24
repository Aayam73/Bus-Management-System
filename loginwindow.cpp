#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QMessageBox>

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    connect(ui->btnLogin, &QPushButton::clicked, this, &::LoginWindow::handlelogin);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}
void LoginWindow::handlelogin(){
    QString username = ui->txtUsername->text();
    QString password = ui->txtPass->text();
    if(password.length()<8){
        QMessageBox::information(this,"Invalid Password","It must have minimun of 8 characters");
    }
    //add file read logic
    if (username == "user" && password == "12345678") {
        QMessageBox::information(this, "Login", "Login successful!");
    }
    //need to apen main window
    else {
        QMessageBox::warning(this, "Login Failed", "Incorrect username or password.");
    }
}
