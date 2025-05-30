
#include "signupwindow.h"
#include "startwindow.h"
#include "database.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if (!BusDB::initialize()) {
        return -1;
    }
    StartWindow w;
    w.show();
    return a.exec();
}

