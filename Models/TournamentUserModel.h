//
// Created by clonewith on 25-3-5.
//

#ifndef TOURNAMENTUSERMODEL_H
#define TOURNAMENTUSERMODEL_H
#include <qabstractitemmodel.h>
#include "TournamentUser.h"


class TournamentUserModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit TournamentUserModel(const QList<TournamentUser> &source, QObject *parent = nullptr) : QAbstractTableModel(parent)
    {
        userList = source;
    }

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void addUser(const TournamentUser& data);

private:
    QList<TournamentUser> userList;
};


#endif //TOURNAMENTUSERMODEL_H
