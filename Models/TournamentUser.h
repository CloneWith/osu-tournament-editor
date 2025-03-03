//
// Created by clonewith on 25-3-3.
//

#ifndef TOURNAMENTUSER_H
#define TOURNAMENTUSER_H
#include <qstring.h>


class TournamentUser
{
public:
    TournamentUser() = default;

    // JSON Property: ID
    int OnlineID = 0;

    QString Username = "";

    /// <summary>
    /// The player's country.
    /// </summary>
    /// JSON Property: country_code
    QString CountryCode = "";

    /// <summary>
    /// The player's global rank, or 0 if not available.
    /// </summary>
    int Rank = 0;
};


#endif //TOURNAMENTUSER_H
