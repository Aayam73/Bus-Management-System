#ifndef SIGNUPWINDOW_H
#define SIGNUPWINDOW_H

#include <QWidget>

namespace Ui {
class SignupWindow;
}

class SignupWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SignupWindow(QWidget *parent = nullptr);
    ~SignupWindow();

private slots:
    void on_btnConfirm_clicked();
    void on_btnCancel_clicked();
    void on_btnLogin_clicked();


private:
    Ui::SignupWindow *ui;
    bool usernameExists(const QString &username);
    void saveUser(const QString &username, const QString &password);
};

#endif // SIGNUPWINDOW_H
