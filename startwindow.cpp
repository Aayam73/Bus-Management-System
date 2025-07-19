#include "startwindow.h"
#include "loginwindow.h"
#include "signupwindow.h"
#include <QDebug>

StartWindow::StartWindow(QObject *parent) : QObject(parent){}

    StartWindow::~StartWindow() {}


    void StartWindow::openLoginWindow()
    {
        if (!loginWindow)
            loginWindow = new LoginWindow();

        loginWindow->show();


    }

    void StartWindow::openSignupWindow()
    {
        if (!signupWindow)
            signupWindow = new SignupWindow();

        signupWindow->show();


    }

