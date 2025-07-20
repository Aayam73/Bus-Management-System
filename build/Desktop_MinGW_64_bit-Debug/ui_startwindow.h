/********************************************************************************
** Form generated from reading UI file 'startwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTWINDOW_H
#define UI_STARTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StartWindow
{
public:
    QPushButton *btnLogin;
    QPushButton *btnSignup;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QWidget *StartWindow)
    {
        if (StartWindow->objectName().isEmpty())
            StartWindow->setObjectName("StartWindow");
        StartWindow->resize(663, 354);
        btnLogin = new QPushButton(StartWindow);
        btnLogin->setObjectName("btnLogin");
        btnLogin->setGeometry(QRect(170, 190, 80, 24));
        btnSignup = new QPushButton(StartWindow);
        btnSignup->setObjectName("btnSignup");
        btnSignup->setGeometry(QRect(390, 190, 80, 24));
        label = new QLabel(StartWindow);
        label->setObjectName("label");
        label->setGeometry(QRect(220, 20, 241, 41));
        label_2 = new QLabel(StartWindow);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(300, 90, 91, 41));

        retranslateUi(StartWindow);

        QMetaObject::connectSlotsByName(StartWindow);
    } // setupUi

    void retranslateUi(QWidget *StartWindow)
    {
        StartWindow->setWindowTitle(QCoreApplication::translate("StartWindow", "Form", nullptr));
        btnLogin->setText(QCoreApplication::translate("StartWindow", "Login", nullptr));
        btnSignup->setText(QCoreApplication::translate("StartWindow", "Signup", nullptr));
        label->setText(QCoreApplication::translate("StartWindow", "PROJECT - 1 : BUS MANAGEMENT SYSTEM", nullptr));
        label_2->setText(QCoreApplication::translate("StartWindow", "WELCOME", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StartWindow: public Ui_StartWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTWINDOW_H
