#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QWidget>

namespace Ui {
class StartWindow;
}

class StartWindow : public QWidget
{
    Q_OBJECT

public:
    explicit StartWindow(QWidget *parent = nullptr);
    ~StartWindow();

private slots:
    void on_btnLogin_clicked();
    void on_btnSignup_clicked();


private:
    Ui::StartWindow *ui;
};

#endif // STARTWINDOW_H
