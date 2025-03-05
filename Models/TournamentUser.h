//
// Created by clonewith on 25-3-3.
//

#ifndef TOURNAMENTUSER_H
#define TOURNAMENTUSER_H

#ifndef QS_HAS_JSON
#define QS_HAS_JSON
#endif

#include <qstring.h>

#include "../libs/qserializer.h"

class TournamentUser : public QSerializer
{
    Q_GADGET
    QS_SERIALIZABLE

    // JSON Property: ID
    QS_FIELD(int, id)

    QS_FIELD(QString, Username)

    /// <summary>
    /// The player's country.
    /// </summary>
    /// JSON Property: country_code
    QS_FIELD(QString, country_code)

    /// <summary>
    /// The player's global rank, or 0 if not available.
    /// </summary>
    QS_FIELD(int, Rank)

public:
    TournamentUser() = default;
};


#endif //TOURNAMENTUSER_H
