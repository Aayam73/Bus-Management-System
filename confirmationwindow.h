#ifndef CONFIRMATIONWINDOW_H
#define CONFIRMATIONWINDOW_H

#include <QDialog>

namespace Ui {
class ConfirmationWindow;
}

class ConfirmationWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ConfirmationWindow(QWidget *parent = nullptr);
    ~ConfirmationWindow();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::ConfirmationWindow *ui;
};

#endif // CONFIRMATIONWINDOW_H
