/********************************************************************************
** Form generated from reading UI file 'signupwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNUPWINDOW_H
#define UI_SIGNUPWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SignupWindow
{
public:
    QPushButton *btnCancel;
    QPushButton *btnConfirm;
    QPushButton *btnLogin;
    QLineEdit *txtUsername;
    QLabel *username;
    QLabel *password;
    QLabel *cpassword;
    QLineEdit *txtPass;
    QLineEdit *txtCPass;
    QLineEdit *lineEdit_4;

    void setupUi(QWidget *SignupWindow)
    {
        if (SignupWindow->objectName().isEmpty())
            SignupWindow->setObjectName("SignupWindow");
        SignupWindow->resize(668, 357);
        btnCancel = new QPushButton(SignupWindow);
        btnCancel->setObjectName("btnCancel");
        btnCancel->setGeometry(QRect(200, 170, 80, 24));
        btnConfirm = new QPushButton(SignupWindow);
        btnConfirm->setObjectName("btnConfirm");
        btnConfirm->setGeometry(QRect(320, 170, 80, 24));
        btnLogin = new QPushButton(SignupWindow);
        btnLogin->setObjectName("btnLogin");
        btnLogin->setGeometry(QRect(320, 220, 80, 24));
        txtUsername = new QLineEdit(SignupWindow);
        txtUsername->setObjectName("txtUsername");
        txtUsername->setGeometry(QRect(290, 50, 113, 24));
        username = new QLabel(SignupWindow);
        username->setObjectName("username");
        username->setGeometry(QRect(150, 60, 71, 16));
        password = new QLabel(SignupWindow);
        password->setObjectName("password");
        password->setGeometry(QRect(150, 90, 51, 16));
        cpassword = new QLabel(SignupWindow);
        cpassword->setObjectName("cpassword");
        cpassword->setGeometry(QRect(150, 120, 101, 16));
        txtPass = new QLineEdit(SignupWindow);
        txtPass->setObjectName("txtPass");
        txtPass->setGeometry(QRect(290, 80, 113, 24));
        txtCPass = new QLineEdit(SignupWindow);
        txtCPass->setObjectName("txtCPass");
        txtCPass->setGeometry(QRect(290, 110, 113, 24));
        lineEdit_4 = new QLineEdit(SignupWindow);
        lineEdit_4->setObjectName("lineEdit_4");
        lineEdit_4->setGeometry(QRect(170, 220, 151, 24));
        lineEdit_4->setReadOnly(true);

        retranslateUi(SignupWindow);

        btnConfirm->setDefault(true);


        QMetaObject::connectSlotsByName(SignupWindow);
    } // setupUi

    void retranslateUi(QWidget *SignupWindow)
    {
        SignupWindow->setWindowTitle(QCoreApplication::translate("SignupWindow", "Form", nullptr));
        btnCancel->setText(QCoreApplication::translate("SignupWindow", "Cancel", nullptr));
        btnConfirm->setText(QCoreApplication::translate("SignupWindow", "Confirm", nullptr));
        btnLogin->setText(QCoreApplication::translate("SignupWindow", "Login", nullptr));
        username->setText(QCoreApplication::translate("SignupWindow", "Username", nullptr));
        password->setText(QCoreApplication::translate("SignupWindow", "Password", nullptr));
        cpassword->setText(QCoreApplication::translate("SignupWindow", "Confirm Password", nullptr));
        lineEdit_4->setText(QCoreApplication::translate("SignupWindow", "Already have an account?", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SignupWindow: public Ui_SignupWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNUPWINDOW_H
