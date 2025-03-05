//
// Created by clonewith on 25-3-5.
//

#include "TournamentRoundModel.h"

#include "TournamentTeamModel.h"

int TournamentRoundModel::rowCount(const QModelIndex& parent) const
{
    return parent.isValid() ? 0 : roundList.size();
}

QVariant TournamentRoundModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    if (role == Qt::DisplayRole) return roundList[index.row()].Name;
    return QVariant::fromValue(roundList[index.row()]);
}

bool TournamentRoundModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (!index.isValid() || (role != Qt::EditRole && role != Qt::DisplayRole))
        return false;

    if (role == Qt::DisplayRole)
    {
        roundList[index.row()].Name = value.toString();
    }
    else
    {
        roundList[index.row()] = value.value<TournamentRound>();
    }

    emit dataChanged(index, index);
    return true;
}

Qt::ItemFlags TournamentRoundModel::flags(const QModelIndex& index) const
{
    return QAbstractListModel::flags(index) | Qt::ItemIsEditable;
}

void TournamentRoundModel::addRound(const TournamentRound& data)
{
    beginInsertRows(QModelIndex(), roundList.size(), roundList.size());
    roundList.append(data);
    endInsertRows();
}

bool TournamentRoundModel::removeRows(int row, int count, const QModelIndex& parent)
{
    if (row < 0 || row >= roundList.size() || count <= 0)
        return false;

    beginRemoveRows(parent, row, row + count - 1);
    roundList.removeAt(row);
    endRemoveRows();
    return true;
}
