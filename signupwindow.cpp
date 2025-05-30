#include "signupwindow.h"
#include "loginwindow.h"
#include "ui_signupwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

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
    QFile file("users.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(',');
        if (parts.size() >= 1 && parts[0] == username)
            return true;
    }

    return false;
}

void SignupWindow::saveUser(const QString &username, const QString &password)
{
    QFile file("users.txt");
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << username << "," << password << "\n";
        file.close();
    }
}

void SignupWindow::on_btnLogin_clicked()
{
    LoginWindow *login = new LoginWindow();
    login->show();
    this->hide();
}


