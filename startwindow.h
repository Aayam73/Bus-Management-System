#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include "loginwindow.h"
#include "signupwindow.h"
#include <QObject>
#include <QQuickView>

class StartWindow : public QObject
{
    Q_OBJECT

public:
    explicit StartWindow(QObject *parent = nullptr);
    ~StartWindow();

private:
    QQuickView *m_view;
};
#endif // STARTWINDOW_H
