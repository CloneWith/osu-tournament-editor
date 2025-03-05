//
// Created by clonewith on 25-3-5.
//

#ifndef TOURNAMENTTEAMMODEL_H
#define TOURNAMENTTEAMMODEL_H
#include "TournamentRoundModel.h"
#include "TournamentTeam.h"


class TournamentTeamModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit TournamentTeamModel(const QList<TournamentTeam> &source, QObject* parent = nullptr) : QAbstractListModel(parent)
    {
        teamList = source;
    }

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role) override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;

    void addTeam(const TournamentTeam& data);
    bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;

private:
    QList<TournamentTeam> teamList;
};


#endif //TOURNAMENTTEAMMODEL_H
