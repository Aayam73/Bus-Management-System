/********************************************************************************
** Form generated from reading UI file 'loginwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWINDOW_H
#define UI_LOGINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginWindow
{
public:
    QWidget *centralwidget;
    QLabel *label_2;
    QLabel *label;
    QLineEdit *txtUsername;
    QLineEdit *txtPass;
    QPushButton *btnLogin;
    QPushButton *btnSignup;
    QLineEdit *txtnoacc;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *LoginWindow)
    {
        if (LoginWindow->objectName().isEmpty())
            LoginWindow->setObjectName("LoginWindow");
        LoginWindow->resize(650, 373);
        LoginWindow->setAutoFillBackground(false);
        centralwidget = new QWidget(LoginWindow);
        centralwidget->setObjectName("centralwidget");
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(230, 100, 61, 16));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(230, 60, 61, 16));
        txtUsername = new QLineEdit(centralwidget);
        txtUsername->setObjectName("txtUsername");
        txtUsername->setGeometry(QRect(340, 60, 113, 24));
        txtPass = new QLineEdit(centralwidget);
        txtPass->setObjectName("txtPass");
        txtPass->setGeometry(QRect(340, 100, 113, 24));
        txtPass->setMaxLength(24);
        txtPass->setEchoMode(QLineEdit::EchoMode::Password);
        btnLogin = new QPushButton(centralwidget);
        btnLogin->setObjectName("btnLogin");
        btnLogin->setGeometry(QRect(280, 160, 80, 24));
        btnSignup = new QPushButton(centralwidget);
        btnSignup->setObjectName("btnSignup");
        btnSignup->setGeometry(QRect(360, 200, 80, 24));
        txtnoacc = new QLineEdit(centralwidget);
        txtnoacc->setObjectName("txtnoacc");
        txtnoacc->setGeometry(QRect(200, 200, 171, 24));
        txtnoacc->setReadOnly(true);
        LoginWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(LoginWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 650, 21));
        LoginWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(LoginWindow);
        statusbar->setObjectName("statusbar");
        LoginWindow->setStatusBar(statusbar);
        QWidget::setTabOrder(txtUsername, txtPass);
        QWidget::setTabOrder(txtPass, btnLogin);
        QWidget::setTabOrder(btnLogin, txtnoacc);
        QWidget::setTabOrder(txtnoacc, btnSignup);

        retranslateUi(LoginWindow);

        btnLogin->setDefault(true);


        QMetaObject::connectSlotsByName(LoginWindow);
    } // setupUi

    void retranslateUi(QMainWindow *LoginWindow)
    {
        LoginWindow->setWindowTitle(QCoreApplication::translate("LoginWindow", "LoginWindow", nullptr));
        label_2->setText(QCoreApplication::translate("LoginWindow", "Password", nullptr));
        label->setText(QCoreApplication::translate("LoginWindow", "Username ", nullptr));
        btnLogin->setText(QCoreApplication::translate("LoginWindow", "Login", nullptr));
        btnSignup->setText(QCoreApplication::translate("LoginWindow", "Signup", nullptr));
        txtnoacc->setText(QCoreApplication::translate("LoginWindow", "Dont have an account ?", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginWindow: public Ui_LoginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWINDOW_H
