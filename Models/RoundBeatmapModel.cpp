//
// Created by clonewith on 25-3-5.
//

#include "RoundBeatmapModel.h"

int RoundBeatmapModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : beatmapList.size();
}

int RoundBeatmapModel::columnCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : 3;
}

QVariant RoundBeatmapModel::data(const QModelIndex &index, const int role) const
{
    if (!index.isValid() || (role != Qt::DisplayRole && role != Qt::EditRole))
        return {};

    RoundBeatmap data = beatmapList[index.row()];

    if (role == Qt::EditRole) return QVariant::fromValue(data);

    switch (index.column())
    {
        case 0: return data.ID;
        case 1: return data.Mods;
        case 2: return data.ModIndex;
        default: return {};
    }
}

QVariant RoundBeatmapModel::headerData(const int section, const Qt::Orientation orientation, const int role) const
{
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
        return QVariant();

    switch (section)
    {
        case 0: return tr("Beatmap ID");
        case 1: return tr("Mod");
        case 2: return tr("Mod Index");
        default: return QVariant();
    }
}

bool RoundBeatmapModel::setData(const QModelIndex &index, const QVariant &value, const int role)
{
    if (!index.isValid() || role != Qt::EditRole)
        return false;

    switch (index.column())
    {
        case 0:
            beatmapList[index.row()].ID = value.toString().toInt();
            break;
        case 1:
            beatmapList[index.row()].Mods = value.toString();
            break;
        case 2:
            beatmapList[index.row()].ModIndex = value.toString();
            break;
        default:
            return false;
    }

    emit dataChanged(index, index);
    emit dataUpdated();
    return true;
}

Qt::ItemFlags RoundBeatmapModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

void RoundBeatmapModel::addBeatmap(const RoundBeatmap &data)
{
    beginInsertRows(QModelIndex(), beatmapList.size(), beatmapList.size());
    beatmapList.append(data);
    endInsertRows();

    emit dataUpdated();
}

bool RoundBeatmapModel::removeRows(const int row, const int count, const QModelIndex &parent)
{
    if (row < 0 || row >= beatmapList.size() || count <= 0)
        return false;

    beginRemoveRows(parent, row, row + count - 1);
    beatmapList.removeAt(row);
    endRemoveRows();

    emit dataUpdated();
    return true;
}
