#include <QAbstractListModel>
#include <QVariantMap>
#include "sessionmanager.h"

class ReservationPanel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum ReservationRoles {
        FromDistrictRole = Qt::UserRole + 1,
        ToDistrictRole,
        TravelDateRole,
        AmountRole,
        DepartureTimeRole,
        ArrivalTimeRole,
        BusNoRole
    };

    explicit ReservationPanel(SessionManager *sessionManager, QObject *parent = nullptr);

    // QAbstractListModel overrides
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void fetchReservations();

private:
    SessionManager *m_sessionManager;
    QList<QVariantMap> m_reservations;
};
