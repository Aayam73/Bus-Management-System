#include "loginwindow.h"
#include "signupwindow.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QQmlContext>
#include <QQmlComponent>
#include <QQmlEngine>


LoginWindow::LoginWindow(QObject *parent)
    : QObject(parent)
{
    m_view = new QQuickView();
    m_view->setResizeMode(QQuickView::SizeRootObjectToView);
    m_view->rootContext()->setContextProperty("loginWindow", this);
    m_view->rootContext()->setContextProperty("homeWindow", m_homeWindow);
    m_view->setSource(QUrl("qrc:/Qml/LoginPage.qml"));

    m_homeWindow = new HomeWindow(this);
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
        emit loginFailed("Incorrect Username or Password");
        return;
    }

    if (username.isEmpty() || password.isEmpty()) {
        emit loginFailed("Please enter both username and password.");
        return;
    }

    if (authenticateUser(username, password)) {
        QSqlDatabase db = QSqlDatabase::database("main");
        QSqlQuery query(db);
        query.prepare("SELECT id FROM users WHERE username = :username");
        query.bindValue(":username", username);

        if (query.exec() && query.next()) {
            currentUserId = query.value(0).toInt();   // set global user ID
            qDebug() << "Logged-in user ID is:" << currentUserId;
        } else {
            qDebug() << "Could not fetch user ID:" << query.lastError().text();
            currentUserId = -1;
        }
        emit loginSuccess();
        if (m_view) {
            m_view->hide();
            qDebug() << "Login view is:" << m_view;
        }


    }

     else {
        emit loginFailed("Incorrect username or password.");
    }
}

bool LoginWindow::authenticateUser(const QString &username, const QString &password)
{
    QSqlDatabase db = QSqlDatabase::database("main");
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return false;
    }

    QSqlQuery query(db);
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

void LoginWindow::close() {
    if (m_view)
        m_view->close();
}

