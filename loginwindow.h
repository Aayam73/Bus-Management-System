#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class LoginWindow;
}
QT_END_NAMESPACE

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void handlelogin();
    void on_btnSignup_clicked();

private:
    Ui::LoginWindow *ui;
    bool authenticateUser(const QString &username, const QString &password);

};
#endif // LOGINWINDOW_H
