#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QMessageBox>
#include "signupwindow.h"
#include "mainwindow.h"
#include <QFile>
#include <QTextStream>


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
        MainWindow *menu = new MainWindow();
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
    QFile file("users.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;  // File doesn't exist or can't open
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        QStringList parts = line.split(",");

        if (parts.size() >= 2) {
            QString storedUsername = parts[0];
            QString storedPassword = parts[1];

            if (storedUsername == username && storedPassword == password) {
                return true;
            }
        }
    }

    return false;
}

