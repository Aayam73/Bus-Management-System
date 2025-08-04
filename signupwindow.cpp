#include "signupwindow.h"
#include "loginwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickView>
#include <QQuickItem>

// Constructor
SignupWindow::SignupWindow(QObject *parent)
    : QObject(parent)  // Changed from QWidget to QObject
{
    // Load QML SignupPage
    m_view = new QQuickView();
    m_view->setResizeMode(QQuickView::SizeRootObjectToView);
    m_view->rootContext()->setContextProperty("signupWindow", this);  // Expose this class to QML
    m_view->setSource(QUrl("qrc:/Qml/SignupPage.qml"));   // Or local file path
}

// Destructor
SignupWindow::~SignupWindow()
{
    if (m_view) {
        m_view->close();
        delete m_view;
    }
}


bool SignupWindow::saveUser(const QString &username, const QString &password)
{
    QSqlDatabase db = QSqlDatabase::database("main");
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }


    QSqlQuery query(db);
    query.prepare("INSERT INTO users (username, password) VALUES (:username, :password)");
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if (!query.exec()) {
        qDebug() << "Signup failed:" << query.lastError().text();
        return false;
    }
    return true;
}

bool SignupWindow::usernameExists(const QString &username)
{
    QSqlDatabase db = QSqlDatabase::database("main");
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("SELECT COUNT(*) FROM users WHERE username = :username");
    query.bindValue(":username", username);

    if (query.exec() && query.next()) {
        int count = query.value(0).toInt();
        return count > 0;
    }

    return false;
}

void SignupWindow::handleSignup(const QString &username, const QString &password, const QString &confirm)
{
    if (username.isEmpty() || password.isEmpty() || confirm.isEmpty()) {
        emit signupFailed("All fields are required");
        return;
    }

    if (password != confirm) {
        emit signupFailed("Passwords do not match.");
        return;
    }

    if (usernameExists(username)) {
        emit signupFailed("Username already exists.");
        return;
    }

    if (password.length() < 8) {
        emit signupFailed("Password must be at least 8 characters.");
        return;
    }

    if (saveUser(username, password)) {
        emit signupSuccess();

        if (m_view) {
            m_view->close();
        }
    }

}



void SignupWindow::show() {
    if (m_view)
        m_view->show();
}



