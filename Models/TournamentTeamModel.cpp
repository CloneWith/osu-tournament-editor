//
// Created by clonewith on 25-3-5.
//

#include "TournamentTeamModel.h"

int TournamentTeamModel::rowCount(const QModelIndex& parent) const
{
    return parent.isValid() ? 0 : teamList.size();
}

QVariant TournamentTeamModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    if (role == Qt::DisplayRole) return teamList[index.row()].FullName;
    return QVariant::fromValue(teamList[index.row()]);
}

bool TournamentTeamModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (!index.isValid() || (role != Qt::EditRole && role != Qt::DisplayRole))
        return false;

    if (role == Qt::DisplayRole)
    {
        teamList[index.row()].FullName = value.toString();
    }
    else
    {
        teamList[index.row()] = value.value<TournamentTeam>();
    }
    return true;
}

Qt::ItemFlags TournamentTeamModel::flags(const QModelIndex& index) const
{
    return QAbstractListModel::flags(index) | Qt::ItemIsEditable;
}

void TournamentTeamModel::addTeam(const TournamentTeam& data)
{
    beginInsertRows(QModelIndex(), teamList.size(), teamList.size());
    teamList.append(data);
    endInsertRows();
}

bool TournamentTeamModel::removeRows(int row, int count, const QModelIndex& parent)
{
    if (row < 0 || row >= teamList.size() || count <= 0)
        return false;

    beginRemoveRows(parent, row, row + count - 1);
    teamList.removeAt(row);
    endRemoveRows();
    return true;
}
