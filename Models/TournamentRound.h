//
// Created by clonewith on 25-3-3.
//

#ifndef TOURNAMENTROUND_H
#define TOURNAMENTROUND_H

#ifndef QS_HAS_JSON
#define QS_HAS_JSON
#endif
#include <qdatetime.h>
#include <qlist.h>
#include <qstring.h>

#include "RoundBeatmap.h"
#include "TournamentUser.h"


class TournamentRound : public QSerializer
{
    Q_GADGET
    QS_SERIALIZABLE

    QS_FIELD(QString, Name)
    QS_FIELD(QString, Description)

    // Value Range: 3 - 23
    QS_FIELD(int, BestOf)

    // Value Range: 0 - 5
    QS_FIELD(int, BanCount)

    QS_COLLECTION_OBJECTS(QList, RoundBeatmap, Beatmaps)

    QS_FIELD(QDateTime, StartDate)

    QS_FIELD(bool, UseBoard)

    QS_COLLECTION_OBJECTS(QList, TournamentUser, Referees)

    // only used for serialisation
    QS_COLLECTION(QList, int, Matches)

public:
    TournamentRound()
    {
        BestOf = 9;
        BanCount = 5;
        StartDate = QDateTime::currentDateTime();
    };
};


#endif //TOURNAMENTROUND_H
