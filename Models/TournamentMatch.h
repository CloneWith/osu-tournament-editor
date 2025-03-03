//
// Created by clonewith on 25-3-3.
//

#ifndef TOURNAMENTMATCH_H
#define TOURNAMENTMATCH_H
#include <qlist.h>
#include <qpoint.h>
#include <qstring.h>

#include "BeatmapChoice.h"
#include "ConditionalTournamentMatch.h"
#include "TeamColour.h"
#include "TournamentRound.h"
#include "TournamentTeam.h"


class TournamentMatch
{
public:
    int ID = -1;

    [[nodiscard]] QList<QString> Acronyms() const;

    TournamentTeam Team1 = TournamentTeam();
    QString Team1Acronym;
    int Team1Score = 0;

    TournamentTeam Team2 = TournamentTeam();
    QString Team2Acronym;
    int Team2Score = 0;

    bool Completed = false;
    bool Losers = false;

    QSet<BeatmapChoice> PicksBans = {};

    TournamentRound Round = TournamentRound();

    /// <summary>
    /// Should not be set directly. Use LadderInfo.CurrentMatch.Value = this instead.
    /// </summary>
    bool Current = false;

    QDateTime Date = QDateTime::currentDateTime();

    QList<ConditionalTournamentMatch> ConditionalMatches = {};

    QPoint Position;

    [[nodiscard]] TeamColour Winner() const;
    [[nodiscard]] TeamColour Loser() const;

    [[nodiscard]] int PointsToWin() const;

    TournamentMatch() = default;
    TournamentMatch(TournamentTeam team1, TournamentTeam team2);
};


#endif //TOURNAMENTMATCH_H
