#ifndef SIGNUPWINDOW_H
#define SIGNUPWINDOW_H

#include <QObject>
#include <QQuickView>

class SignupWindow : public QObject
{
    Q_OBJECT

public:
    explicit SignupWindow(QObject *parent = nullptr);
    ~SignupWindow();

    Q_INVOKABLE void handleSignup(const QString &username, const QString &password, const QString &confirm);
    Q_INVOKABLE void goToLogin();
    void show();


signals:
    void signupSuccess();


private:
    bool usernameExists(const QString &username);
    bool saveUser(const QString &username, const QString &password);

    QQuickView *m_view;
};

#endif // SIGNUPWINDOW_H
