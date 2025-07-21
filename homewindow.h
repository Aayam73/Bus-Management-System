#ifndef HOMEWINDOW_H
#define HOMEWINDOW_H

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
    QVariantList routes() const { return m_routes; }
    void show();

signals:
    void searchResultsReady(const QVariantList &routes);  // ✅ Send search results to QML

private:
    QStringListModel* m_districtModel = nullptr;
    QQuickView *m_view = nullptr;
    QVariantList m_routes;  // ✅ Store route data
};

#endif // HOMEWINDOW_H
