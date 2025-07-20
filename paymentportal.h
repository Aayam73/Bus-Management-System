#ifndef PAYMENTPORTAL_H
#define PAYMENTPORTAL_H

#include <QMainWindow>


namespace Ui {
class PaymentPortal;
}

class PaymentPortal : public QMainWindow
{
    Q_OBJECT

public:
    explicit PaymentPortal(QWidget *parent = nullptr);
    ~PaymentPortal();

private slots:
    void on_payButton_clicked();
    void on_paymentMethodChanged();
    void toggleEsewaMpinVisibility();
    void toggleKhaltiMpinVisibility();



private:
    Ui::PaymentPortal *ui;
    bool validateInputs();
};

#endif // PAYMENTPORTAL_H
