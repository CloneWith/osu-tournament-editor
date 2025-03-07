//
// Created by clonewith on 25-3-5.
//

#include "TournamentUserModel.h"

int TournamentUserModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : userList.size();
}

int TournamentUserModel::columnCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : 4;
}

QVariant TournamentUserModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || (role != Qt::DisplayRole && role != Qt::EditRole))
        return {};

    TournamentUser data = userList[index.row()];

    if (role == Qt::EditRole) return QVariant::fromValue(data);

    switch (index.column())
    {
        case 0: return data.id;
        case 1: return data.Username;
        case 2: return data.country_code;
        case 3: return data.Rank;
        default: return {};
    }
}

QVariant TournamentUserModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
        return {};

    switch (section)
    {
        case 0: return tr("User ID");
        case 1: return tr("Username");
        case 2: return tr("Country Code");
        case 3: return tr("Rank");
        default: return {};
    }
}

bool TournamentUserModel::setData(const QModelIndex &index, const QVariant &value, const int role)
{
    if (!index.isValid() || role != Qt::EditRole)
        return false;

    switch (index.column())
    {
        case 0:
            userList[index.row()].id = value.toString().toInt();
            break;
        case 1:
            userList[index.row()].Username = value.toString();
            break;
        case 2:
            userList[index.row()].country_code = value.toString();
            break;
        case 3:
            userList[index.row()].Rank = value.toString().toInt();
            break;
        default:
            return false;
    }

    emit dataChanged(index, index);
    emit dataUpdated();
    return true;
}

Qt::ItemFlags TournamentUserModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

void TournamentUserModel::addUser(const TournamentUser &data)
{
    beginInsertRows(QModelIndex(), userList.size(), userList.size());
    userList.append(data);
    endInsertRows();
}

bool TournamentUserModel::removeRows(int row, int count, const QModelIndex& parent)
{
    if (row < 0 || row >= userList.size() || count <= 0)
        return false;

    beginRemoveRows(parent, row, row + count - 1);
    userList.removeAt(row);
    endRemoveRows();

    emit dataUpdated();
    return true;
}

