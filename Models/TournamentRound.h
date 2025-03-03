//
// Created by clonewith on 25-3-3.
//

#ifndef TOURNAMENTROUND_H
#define TOURNAMENTROUND_H
#include <qdatetime.h>
#include <qlist.h>
#include <qstring.h>

#include "RoundBeatmap.h"
#include "TournamentUser.h"


class TournamentRound
{
public:
    QString Name = "";
    QString Description = "";

    // Value Range: 3 - 23
    int BestOf = 9;

    // Value Range: 0 - 5
    int BanCount = 5;

    QList<RoundBeatmap> Beatmaps = {};

    QDateTime StartDate = QDateTime::currentDateTime();

    bool UseBoard = false;

    QList<TournamentUser> Referees = {};

    // only used for serialisation
    QList<int> Matches = {};

    TournamentRound() = default;
};


#endif //TOURNAMENTROUND_H
