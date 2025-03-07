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
        return {};

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

    emit dataChanged(index, index);
    emit dataUpdated();
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

    emit dataUpdated();
}

bool TournamentTeamModel::removeRows(const int row, const int count, const QModelIndex& parent)
{
    if (row < 0 || row >= teamList.size() || count <= 0)
        return false;

    beginRemoveRows(parent, row, row + count - 1);
    teamList.removeAt(row);
    endRemoveRows();

    emit dataUpdated();
    return true;
}
