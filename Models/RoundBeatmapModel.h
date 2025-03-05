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

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void addBeatmap(const RoundBeatmap& data);

private:
    QList<RoundBeatmap> beatmapList;
};


#endif //ROUNDBEATMAPMODEL_H
