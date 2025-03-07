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

    [[nodiscard]] int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    [[nodiscard]] int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    [[nodiscard]] QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    [[nodiscard]] QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    [[nodiscard]] Qt::ItemFlags flags(const QModelIndex &index) const override;

    [[nodiscard]] QList<TournamentUser> GetUserList() const
    {
        return userList;
    }

    [[nodiscard]] TournamentUser GetUserAt(const int index)
    {
        return userList[index];
    }

    void addUser(const TournamentUser& data);
    bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;

private:
    QList<TournamentUser> userList;

signals:
    void dataUpdated();
};


#endif //TOURNAMENTUSERMODEL_H
