#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QObject>
#include <QQuickView>


class LoginWindow : public QObject
{
    Q_OBJECT

public:
    LoginWindow(QObject *parent = nullptr);
    ~LoginWindow();

    Q_INVOKABLE void handleLogin(const QString &username, const QString &password);
    Q_INVOKABLE void goToSignup();
    void show();

signals:
    void loginSuccess();
    void loginFailed(const QString &reason);

private:
    bool authenticateUser(const QString &username, const QString &password);

    QQuickView *m_view;

};
#endif // LOGINWINDOW_H
