#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include "loginwindow.h"
#include "signupwindow.h"
#include <QObject>
#include <QQuickView>

class StartWindow : public QObject
{
    Q_OBJECT

public:
    explicit StartWindow(QObject *parent = nullptr);
    ~StartWindow();

    Q_INVOKABLE void openLoginWindow();
    Q_INVOKABLE void openSignupWindow();

private:
    QQuickView *m_view;
    LoginWindow *loginWindow = nullptr;
    SignupWindow *signupWindow = nullptr;
};
#endif // STARTWINDOW_H
