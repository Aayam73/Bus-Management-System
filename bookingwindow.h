#ifndef BOOKINGWINDOW_H
#define BOOKINGWINDOW_H

#include <QWidget>

namespace Ui {
class BookingWindow;
}

class BookingWindow : public QWidget
{
    Q_OBJECT

public:
    explicit BookingWindow(QWidget *parent = nullptr);
    ~BookingWindow();
    void setRouteData(const QString &routeId, const QString &from, const QString &to, const QString &departure);

private slots:
    void on_pushButton_clicked();

    void on_btnReturn_clicked();

private:
    Ui::BookingWindow *ui;
};

#endif // BOOKINGWINDOW_H
