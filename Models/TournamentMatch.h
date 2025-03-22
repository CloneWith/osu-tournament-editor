//
// Created by clonewith on 25-3-3.
//

#ifndef TOURNAMENTMATCH_H
#define TOURNAMENTMATCH_H

#ifndef QS_HAS_JSON
#define QS_HAS_JSON
#endif

#include <qlist.h>
#include <qpoint.h>
#include <qstring.h>

#include "Point.h"
#include "BeatmapChoice.h"
#include "TeamColour.h"
#include "TournamentRound.h"
#include "TournamentTeam.h"


class TournamentMatch : public QSerializer
{
    Q_GADGET
    QS_SERIALIZABLE

    QS_FIELD(int, ID)

    QS_OBJECT(TournamentTeam, Team1)
    QS_FIELD(QString, Team1Acronym)
    QS_FIELD(int, Team1Score)

    QS_OBJECT(TournamentTeam, Team2)
    QS_FIELD(QString, Team2Acronym)
    QS_FIELD(int, Team2Score)

    QS_FIELD(bool, Completed)
    QS_FIELD(bool, Losers)

    QS_COLLECTION_OBJECTS(QList, BeatmapChoice, PicksBans)

    QS_OBJECT(TournamentRound, Round)

    /// <summary>
    /// Should not be set directly. Use LadderInfo.CurrentMatch.Value = this instead.
    /// </summary>
    QS_FIELD(bool, Current)

    QS_FIELD(QDateTime, Date)

    QS_OBJECT(Point, Position)

    QS_FIELD(TeamColour, Winner)
    QS_FIELD(TeamColour, Loser)
    QS_FIELD(int, PointsToWin)

    [[nodiscard]] TeamColour GetWinner() const;
    [[nodiscard]] TeamColour GetLoser() const;

    [[nodiscard]] int GetPointsToWin() const;

public:
    TournamentMatch()
    {
        ID = -1;
        Date = QDateTime::currentDateTime();
    }
    TournamentMatch(TournamentTeam team1, TournamentTeam team2);
};


#endif //TOURNAMENTMATCH_H
