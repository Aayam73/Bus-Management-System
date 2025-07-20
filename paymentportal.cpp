#include "paymentportal.h"
#include "ui_paymentportal.h"
#include <QMessageBox>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
void PaymentPortal::on_payButton_clicked()
{
    if (!validateInputs())
        return;

    ui->payButton->setEnabled(false);

    QString method = ui->radioEsewa->isChecked() ? "eSewa" : "Khalti";

    QMessageBox::information(this, "Payment Successful",
                             "Thank you, " + ui->nameLineEdit->text() +
                                 "! Your payment was successful via " + method + ".");

    // Close window or reset form instead of `accept()` since you're using QMainWindow
    this->close();  // or implement a resetInputs() function
}

PaymentPortal::PaymentPortal(QWidget *parent) :
        QMainWindow(parent),
    ui(new Ui::PaymentPortal)
{
    ui->setupUi(this);
    connect(ui->radioEsewa, &QRadioButton::toggled, this, &PaymentPortal::on_paymentMethodChanged);
    connect(ui->radioKhalti, &QRadioButton::toggled, this, &PaymentPortal::on_paymentMethodChanged);
    connect(ui->toggleEsewaMpinButton, &QPushButton::clicked, this, &PaymentPortal::toggleEsewaMpinVisibility);
    connect(ui->toggleKhaltiMpinButton, &QPushButton::clicked, this, &PaymentPortal::toggleKhaltiMpinVisibility);


}

PaymentPortal::~PaymentPortal()
{
    delete ui;
}

void PaymentPortal::on_paymentMethodChanged()
{
    if (ui->radioEsewa->isChecked()) {
        qDebug() << "eSewa selected, switching to page 2";
        ui->stackedWidget->setCurrentIndex(2);
    } else if (ui->radioKhalti->isChecked()) {
        qDebug() << "Khalti selected, switching to page 3";
        ui->stackedWidget->setCurrentIndex(0);
    }
}
void PaymentPortal::toggleEsewaMpinVisibility()
{
    if (ui->esewaMpinLineEdit->echoMode() == QLineEdit::Password)
        ui->esewaMpinLineEdit->setEchoMode(QLineEdit::Normal);
    else
        ui->esewaMpinLineEdit->setEchoMode(QLineEdit::Password);
}

void PaymentPortal::toggleKhaltiMpinVisibility()
{
    if (ui->khaltiMpinLineEdit->echoMode() == QLineEdit::Password)
        ui->khaltiMpinLineEdit->setEchoMode(QLineEdit::Normal);
    else
        ui->khaltiMpinLineEdit->setEchoMode(QLineEdit::Password);
}


bool PaymentPortal::validateInputs()
{
    if (ui->nameLineEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter your name.");
        return false;
    }
    if (ui->emailLineEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter your email.");
        return false;
    }
    QString email = ui->emailLineEdit->text().trimmed();
    QRegularExpression emailRegex(R"(^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}$)");
    if (!emailRegex.match(email).hasMatch()) {
        QMessageBox::warning(this, "Input Error", "Please enter a valid email address.");
        return false;
    }

    if (ui->phoneLineEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter your phone number.");
        return false;
    }
    QString phone = ui->phoneLineEdit->text().trimmed();
    QRegularExpression phoneRegex(R"(^(98|97)\d{8}$)");
    if (!phoneRegex.match(phone).hasMatch()) {
        QMessageBox::warning(this, "Input Error", "Please enter a valid  10 digit phone no");
        return false;
    }

    if (!ui->radioEsewa->isChecked() && !ui->radioKhalti->isChecked()) {
        QMessageBox::warning(this, "Input Error", "Please select a payment method.");
        return false;
    }
    if (ui->radioEsewa->isChecked()) {
        if (ui->esewaIdLineEdit->text().trimmed().isEmpty()) {
            QMessageBox::warning(this, "Input Error", "Please enter your eSewa Id.");
            return false;
        }
    if (ui->radioEsewa->isChecked()) {
        if (ui->esewaMpinLineEdit->text().trimmed().isEmpty()) {
            QMessageBox::warning(this, "Input Error", "Please enter your eSewa MPIN.");
            return false;
        }
        QString mpin = ui->esewaMpinLineEdit->text().trimmed();
        QRegularExpression mpinRegex(R"(^\d{4}$)");
        if (!mpinRegex.match(mpin).hasMatch()) {
            QMessageBox::warning(this, "Input Error", "Please enter a valid eSewa MPIN");
            return false;
        }

    } else if (ui->radioKhalti->isChecked()) {
        if (ui->khaltiIdLineEdit->text().trimmed().isEmpty()) {
            QMessageBox::warning(this, "Input Error", "Please enter your Khalti ID.");
            return false;
        }
        if (ui->khaltiMpinLineEdit->text().trimmed().isEmpty()) {
            QMessageBox::warning(this, "Input Error", "Please enter your Khalti MPIN.");
            return false;
        }
        QString kmpin = ui->khaltiMpinLineEdit->text().trimmed();
        QRegularExpression kmpinRegex(R"(^\d{4}$)");
        if (!kmpinRegex.match(kmpin).hasMatch()) {
            QMessageBox::warning(this, "Input Error", "Please enter a valid Khalti MPIN");
            return false;
        }
    }

    return true;
}
}

