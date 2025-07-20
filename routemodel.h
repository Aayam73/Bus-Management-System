#ifndef ROUTEMODEL_H
#define ROUTEMODEL_H

#pragma once
#include <QSqlQueryModel>

class RouteModel : public QSqlQueryModel
{
     Q_OBJECT
public:

     explicit RouteModel(QObject *parent = nullptr);

     QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
     QHash<int, QByteArray> roleNames() const override;

};

#endif // ROUTEMODEL_H
