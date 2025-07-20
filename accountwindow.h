#ifndef ACCOUNTWINDOW_H
#define ACCOUNTWINDOW_H

#include <QWidget>

namespace Ui {
class AccountWindow;
}

class AccountWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AccountWindow(QWidget *parent = nullptr);
    ~AccountWindow();

private slots:
    void on_btnReturn_clicked();

    void on_btnLogout_clicked();

private:
    Ui::AccountWindow *ui;
};

#endif // ACCOUNTWINDOW_H
