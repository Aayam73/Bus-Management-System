#include "mainmenuwindow.h"
#include "ui_mainmenuwindow.h"

MainMenuWindow::MainMenuWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainMenuWindow)
{
    ui->setupUi(this);
}

MainMenuWindow::~MainMenuWindow()
{
    delete ui;
}
