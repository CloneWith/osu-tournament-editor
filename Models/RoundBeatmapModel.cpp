//
// Created by clonewith on 25-3-5.
//

#include "RoundBeatmapModel.h"

int RoundBeatmapModel::rowCount(const QModelIndex& parent) const
{
    return parent.isValid() ? 0 : beatmapList.size();
}

int RoundBeatmapModel::columnCount(const QModelIndex& parent) const
{
    return parent.isValid() ? 0 : 3;
}

QVariant RoundBeatmapModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();

    RoundBeatmap data = beatmapList[index.row()];

    switch (index.column())
    {
        case 0: return data.ID;
        case 1: return data.Mods;
        case 2: return data.ModIndex;
        default: return QVariant();
    }
}

QVariant RoundBeatmapModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
        return QVariant();

    switch (section) {
        case 0: return tr("Beatmap ID");
        case 1: return tr("Mod");
        case 2: return tr("Mod Index");
        default: return QVariant();
    }
}

void RoundBeatmapModel::addBeatmap(const RoundBeatmap& data)
{
    beginInsertRows(QModelIndex(), beatmapList.size(), beatmapList.size());
    beatmapList.append(data);
    endInsertRows();
}
