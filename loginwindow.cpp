#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QMessageBox>
#include "signupwindow.h"
#include "homewindow.h"
#include <QFile>
#include <QTextStream>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>


LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    QAbstractButton::connect(ui->btnLogin, &QPushButton::clicked, this, &::LoginWindow::handlelogin);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}
void LoginWindow::handlelogin()
{
    QString username = ui->txtUsername->text().trimmed();
    QString password = ui->txtPass->text();

    if (password.length() < 8) {
        QMessageBox::information(this, "Invalid Password", "It must have minimum of 8 characters");
        return;
    }

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Login Failed", "Please enter both username and password.");
        return;
    }

    if (authenticateUser(username, password)) {
        QMessageBox::information(this, "Login", "Login successful!");
        HomeWindow *menu = new HomeWindow();
        menu->show();
        this->hide();
    } else {
        QMessageBox::warning(this, "Login Failed", "Incorrect username or password.");
    }
}


void LoginWindow::on_btnSignup_clicked()
{
    SignupWindow *signup = new SignupWindow();
    signup->show();
    this->hide();

}
bool LoginWindow::authenticateUser(const QString &username, const QString &password)
{
    QSqlQuery query;
    query.prepare("SELECT password FROM users WHERE username = :username");
    query.bindValue(":username", username);

    if (!query.exec()) {
        qDebug() << "Login query failed:" << query.lastError().text();
        return false;
    }

    if (query.next()) {
        QString storedPassword = query.value(0).toString();
        return storedPassword == password;
    }


    return false;
}

