#include "routemodel.h"

RouteModel::RouteModel(QObject *parent) : QSqlQueryModel(parent) {}

QVariant RouteModel::data(const QModelIndex &index, int role) const {
    if (role < Qt::UserRole)
        return QSqlQueryModel::data(index, role);

    int column = role - Qt::UserRole;
    return QSqlQueryModel::data(this->index(index.row(), column), Qt::DisplayRole);
}

QHash<int, QByteArray> RouteModel::roleNames() const {
    QHash<int, QByteArray> roles;
    for (int i = 0; i < this->columnCount(); ++i) {
        roles[Qt::UserRole + i] = this->headerData(i, Qt::Horizontal).toByteArray();
    }
    return roles;
}
