//
// Created by clonewith on 25-3-5.
//

#ifndef TOURNAMENTROUNDMODEL_H
#define TOURNAMENTROUNDMODEL_H
#include <qabstractitemmodel.h>

#include "TournamentRound.h"


class TournamentRoundModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit TournamentRoundModel(const QList<TournamentRound> &source, QObject *parent = nullptr) : QAbstractListModel(parent)
    {
        roundList = source;
    }

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    void addRound(const TournamentRound &round);
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

private:
    QList<TournamentRound> roundList;
};


#endif //TOURNAMENTROUNDMODEL_H
