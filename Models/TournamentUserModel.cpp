//
// Created by clonewith on 25-3-5.
//

#include "TournamentUserModel.h"

int TournamentUserModel::rowCount(const QModelIndex& parent) const
{
    return parent.isValid() ? 0 : userList.size();
}

int TournamentUserModel::columnCount(const QModelIndex& parent) const
{
    return parent.isValid() ? 0 : 4;
}

QVariant TournamentUserModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();

    TournamentUser data = userList[index.row()];

    switch (index.column())
    {
        case 0: return data.id;
        case 1: return data.Username;
        case 2: return data.country_code;
        case 3: return data.Rank;
        default: return QVariant();
    }
}

QVariant TournamentUserModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
        return QVariant();

    switch (section) {
        case 0: return tr("User ID");
        case 1: return tr("Username");
        case 2: return tr("Country Code");
        case 3: return tr("Rank");
        default: return QVariant();
    }
}

void TournamentUserModel::addUser(const TournamentUser& data)
{
    beginInsertRows(QModelIndex(), userList.size(), userList.size());
    userList.append(data);
    endInsertRows();
}
