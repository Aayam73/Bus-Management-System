#include "signupwindow.h"
#include "loginwindow.h"
#include "ui_signupwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>



SignupWindow::SignupWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SignupWindow)
{
    ui->setupUi(this);
    ui->txtPass->setEchoMode(QLineEdit::Password);
    ui->txtCPass->setEchoMode(QLineEdit::Password);

}

SignupWindow::~SignupWindow()
{
    delete ui;
}

bool SignupWindow::saveUser(const QString &username, const QString &password)
{
    QSqlQuery query;
    query.prepare("INSERT INTO users (username, password) VALUES (:username, :password)");
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if (!query.exec()) {
        qDebug() << "Signup failed:" << query.lastError().text();
        return false;
    }
    return true;
}

void SignupWindow::on_btnConfirm_clicked()
{
    QString username = ui->txtUsername->text().trimmed();
    QString password = ui->txtPass->text();
    QString confirm = ui->txtCPass->text();

    if (username.isEmpty() || password.isEmpty() || confirm.isEmpty()) {
        QMessageBox::warning(this, "Signup Failed", "All fields are required.");
        return;
    }

    if (password != confirm) {
        QMessageBox::warning(this, "Signup Failed", "Passwords do not match.");
        return;
    }

    if (usernameExists(username)) {
        QMessageBox::warning(this, "Signup Failed", "Username already exists.");
        return;
    }
    if (password.length() < 8) {
        QMessageBox::information(this, "Invalid Password", "It must have minimum of 8 characters");
        return;
    }

    saveUser(username, password);
    QMessageBox::information(this, "Signup Success", "Account created successfully.");
    close();

    LoginWindow *login = new LoginWindow();
    login->show();
    this->hide();
}
void SignupWindow::on_btnCancel_clicked()
{
    close();
}

bool SignupWindow::usernameExists(const QString &username)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM users WHERE username = :username");
    query.bindValue(":username", username);

    if (query.exec() && query.next()) {
        int count = query.value(0).toInt();
        return count > 0;
    }

    return false;
}

void SignupWindow::on_btnLogin_clicked()
{
    LoginWindow *login = new LoginWindow();
    login->show();
    this->hide();
}




