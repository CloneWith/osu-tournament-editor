//
// Created by clonewith on 25-3-3.
//

#ifndef TOURNAMENTTEAM_H
#define TOURNAMENTTEAM_H
#include <qlist.h>
#include <qstring.h>

#include "SeedingResult.h"
#include "TournamentUser.h"


class TournamentTeam
{
public:
    TournamentTeam() = default;

    /// <summary>
    /// The name of this team.
    /// </summary>
    QString FullName = "";

    /// <summary>
    /// Name of the file containing the flag.
    /// </summary>
    QString FlagName = "";

    /// <summary>
    /// Short acronym which appears in the group boxes post-selection.
    /// </summary>
    QString Acronym = "";

    QList<SeedingResult> SeedingResults = {};

    [[nodiscard]] double AverageRank() const;

    QString Seed = "";

    // Value Range: 0 - 256
    int LastYearPlacing = 0;

    QList<TournamentUser> Players = {};

    QString ToString();
};


#endif //TOURNAMENTTEAM_H
