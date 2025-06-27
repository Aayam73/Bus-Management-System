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

private:
    Ui::AccountWindow *ui;
};

#endif // ACCOUNTWINDOW_H
