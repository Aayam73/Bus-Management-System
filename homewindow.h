#ifndef HOMEWINDOW_H
#define HOMEWINDOW_H

#include "bookingwindow.h"
#include <QObject>
#include <QQuickView>
#include <QStringListModel>
#include <QVariantList>

class HomeWindow : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QAbstractListModel* districtModel READ districtModel CONSTANT)
    Q_PROPERTY(QVariantList routes READ routes NOTIFY searchResultsReady)

public:
    explicit HomeWindow(QObject *parent = nullptr);
    ~HomeWindow();

    QAbstractListModel* districtModel() const { return m_districtModel; }
    Q_INVOKABLE void searchRoute(const QString &from, const QString &to);
    Q_INVOKABLE QStringList getDistricts() const;
    Q_INVOKABLE void openBookingPage(
        const QString &routeId,
        const QString &from,
        const QString &to,
        const QString &departure,
        const QString &arrival,
        const QString &price,
        const QString &bus,
        const QString &driver,
        const QString &phone,
        const QString &seats
        );
    QVariantList routes() const { return m_routes; }
    void show();
    QQuickView* view() const;

signals:
    void searchResultsReady(const QVariantList &routes);
    void bookingPageOpened();

private:
    QStringListModel* m_districtModel = nullptr;
    QQuickView *m_view = nullptr;
    QVariantList m_routes;
    BookingWindow* m_bookingWindow = nullptr;
};

#endif // HOMEWINDOW_H
