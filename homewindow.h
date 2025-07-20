#ifndef HOMEWINDOW_H
#define HOMEWINDOW_H

#include <QObject>
#include <QQuickView>
#include <QSqlQueryModel>
#include <routemodel.h>

class HomeWindow : public QObject
{
    Q_OBJECT
    Q_PROPERTY(RouteModel* model READ model CONSTANT)

public:
    explicit HomeWindow(QObject *parent = nullptr);
    ~HomeWindow();

    RouteModel* model() const;
    Q_INVOKABLE void searchRoute(const QString &from, const QString &to);
    Q_INVOKABLE QStringList getDistricts() const;

    void show();

private:
    RouteModel *m_model;

    QQuickView *m_view;

};

#endif // HOMEWINDOW_H
