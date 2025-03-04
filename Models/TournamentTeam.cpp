//
// Created by clonewith on 25-3-3.
//

#include "TournamentTeam.h"

QString TournamentTeam::ToString()
{
    return FullName != "" ? FullName : Acronym;
}

double TournamentTeam::GetAverageRank() const
{
    QList<int> ranks = {};
    double sum = 0;

    for (const TournamentUser& user : Players)
    {
        if (user.Rank != 0) ranks.append(user.Rank);
        sum += user.Rank;
    }

    if (ranks.isEmpty()) return 0;
    return sum / ranks.length();
}
