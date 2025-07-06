#ifndef HOMEWINDOW_H
#define HOMEWINDOW_H

#include <QWidget>

namespace Ui {
class HomeWindow;
}

class HomeWindow : public QWidget
{
    Q_OBJECT

public:
    explicit HomeWindow(QWidget *parent = nullptr);
    ~HomeWindow();

private slots:
    void on_btnSearch_clicked();

    void on_btnAccount_clicked();

private:
    Ui::HomeWindow *ui;
};

#endif // HOMEWINDOW_H
