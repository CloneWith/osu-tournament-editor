//
// Created by clonewith on 25-3-3.
//

#include "TournamentMatch.h"

#include <utility>

int TournamentMatch::PointsToWin() const
{
    return Round.BestOf / 2 + 1;
}

TournamentMatch::TournamentMatch(TournamentTeam team1, TournamentTeam team2)
{
    Team1 = std::move(team1);
    Team2 = std::move(team2);
}

QList<QString> TournamentMatch::Acronyms() const
{
    QList<QString> acronyms;

    if (Team1Acronym != "") acronyms.append(Team1Acronym);
    if (Team2Acronym != "") acronyms.append(Team2Acronym);

    return acronyms;
}

TeamColour TournamentMatch::Winner() const
{
    if (!Completed) return Neutral;
    return Team1Score > Team2Score ? Red : Blue;
}

TeamColour TournamentMatch::Loser() const
{
    if (!Completed) return Neutral;
    return Team1Score < Team2Score ? Red : Blue;
}
