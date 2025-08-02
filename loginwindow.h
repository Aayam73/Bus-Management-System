#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include "homewindow.h"
#include <QObject>
#include <QQuickView>


class LoginWindow : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString username READ username WRITE setUsername NOTIFY usernameChanged)


public:
    LoginWindow(QObject *parent = nullptr);
    ~LoginWindow();

    Q_INVOKABLE void handleLogin(const QString &username, const QString &password);
    Q_INVOKABLE void goToSignup();
    void show();
    void close();
    QQuickView* view() const { return m_view; }
    QString username() const { return m_username; }
    void setUsername(const QString &username) {
        if (m_username != username) {
            m_username = username;
            emit usernameChanged();
        }
    }

signals:
    void loginSuccess();
    void loginFailed(const QString &reason);
    void loginSuccessWithUserId(int userId);
    void usernameChanged();

private:
    bool authenticateUser(const QString &username, const QString &password);

    QQuickView *m_view;
    HomeWindow *m_homeWindow = nullptr;
    QString m_username;


};
#endif // LOGINWINDOW_H
