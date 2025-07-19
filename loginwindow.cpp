#include "loginwindow.h"
#include "homewindow.h"
#include "signupwindow.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QQmlContext>


LoginWindow::LoginWindow(QObject *parent)
    : QObject(parent)
{
    m_view = new QQuickView();
    m_view->setResizeMode(QQuickView::SizeRootObjectToView);
    m_view->rootContext()->setContextProperty("loginWindow", this);
    m_view->setSource(QUrl("qrc:/Qml/LoginPage.qml"));
}

LoginWindow::~LoginWindow()
{
    if (m_view) {
        m_view->close();
        delete m_view;
    }
}

void LoginWindow::handleLogin(const QString &username, const QString &password)
{
    if (password.length() < 8) {
        emit loginFailed("Password must have at least 8 characters.");
        return;
    }

    if (username.isEmpty() || password.isEmpty()) {
        emit loginFailed("Please enter both username and password.");
        return;
    }

    if (authenticateUser(username, password)) {
        emit loginSuccess();

        // Open home window (old UI widget) if you want or handle in QML navigation
        HomeWindow *home = new HomeWindow();
        home->show();

        if (m_view) {
            m_view->close();
        }

    } else {
        emit loginFailed("Incorrect username or password.");
    }
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

void LoginWindow::goToSignup()
{
    if (m_view) {
        m_view->close();
        delete m_view;
        m_view = nullptr;
    }

    // Open Signup window (which manages its own QQuickView)
    SignupWindow *signup = new SignupWindow();
    Q_UNUSED(signup);
}

void LoginWindow::show() {
    if (m_view)
        m_view->show();
}

