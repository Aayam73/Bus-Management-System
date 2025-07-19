#include "confirmationwindow.h"
#include "ui_confirmationwindow.h"
#include "accountwindow.h"
#include <QQuickView>

ConfirmationWindow::ConfirmationWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ConfirmationWindow)
{
    ui->setupUi(this);
}

ConfirmationWindow::~ConfirmationWindow()
{
    delete ui;
}

void ConfirmationWindow::on_buttonBox_accepted()
{
    QQuickView *view = new QQuickView();
    view->setResizeMode(QQuickView::SizeRootObjectToView);
    view->setSource(QUrl::fromLocalFile("StartPage.qml"));
    view->show();

    this->close();
}


void ConfirmationWindow::on_buttonBox_rejected()
{
    AccountWindow *account = new AccountWindow;
    this->close();
    account->show();
}

