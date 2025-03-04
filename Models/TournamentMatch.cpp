//
// Created by clonewith on 25-3-3.
//

#include "TournamentMatch.h"

#include <utility>

int TournamentMatch::GetPointsToWin() const
{
    return Round.BestOf / 2 + 1;
}

TournamentMatch::TournamentMatch(TournamentTeam team1, TournamentTeam team2)
{
    Team1 = std::move(team1);
    Team2 = std::move(team2);
}

TeamColour TournamentMatch::GetWinner() const
{
    if (!Completed) return TeamColour::None;
    return Team1Score > Team2Score ? Red : Blue;
}

TeamColour TournamentMatch::GetLoser() const
{
    if (!Completed) return TeamColour::None;
    return Team1Score < Team2Score ? Red : Blue;
}
