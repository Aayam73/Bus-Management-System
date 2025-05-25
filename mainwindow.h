#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QTimeEdit>
#include <QPushButton>
#include <QTableView>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private:
    QLineEdit *startEdit;
    QLineEdit *endEdit;
    QTimeEdit *timeEdit;
    QPushButton *searchButton;
    QTableView *tableView;
};

#endif // MAINWINDOW_H
