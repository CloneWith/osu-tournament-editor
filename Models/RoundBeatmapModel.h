//
// Created by clonewith on 25-3-5.
//

#ifndef ROUNDBEATMAPMODEL_H
#define ROUNDBEATMAPMODEL_H
#include <qabstractitemmodel.h>

#include "RoundBeatmap.h"


class RoundBeatmapModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit RoundBeatmapModel(const QList<RoundBeatmap> &source, QObject* parent = nullptr) : QAbstractTableModel(parent)
    {
        beatmapList = source;
    }

    [[nodiscard]] int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    [[nodiscard]] QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    [[nodiscard]] Qt::ItemFlags flags(const QModelIndex &index) const override;

    void addBeatmap(const RoundBeatmap& data);
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    [[nodiscard]] RoundBeatmap GetBeatmapAt(const int &index) const
    {
        return beatmapList.at(index);
    }

private:
    QList<RoundBeatmap> beatmapList;

signals:
    void dataUpdated();
};


#endif //ROUNDBEATMAPMODEL_H
