//
// Created by clonewith on 25-3-3.
//

#ifndef TOURNAMENTTEAM_H
#define TOURNAMENTTEAM_H

#ifndef QS_HAS_JSON
#define QS_HAS_JSON
#endif

#include <qlist.h>
#include <qstring.h>

#include "SeedingResult.h"
#include "TournamentUser.h"
#include "../libs/qserializer.h"

class TournamentTeam : public QSerializer
{
    Q_GADGET
    QS_SERIALIZABLE

public:
    TournamentTeam() = default;

    /// <summary>
    /// The name of this team.
    /// </summary>
    QS_FIELD(QString, FullName)

    /// <summary>
    /// Name of the file containing the flag.
    /// </summary>
    QS_FIELD(QString, FlagName)

    /// <summary>
    /// Short acronym which appears in the group boxes post-selection.
    /// </summary>
    QS_FIELD(QString, Acronym)

    QS_COLLECTION_OBJECTS(QList, SeedingResult, SeedingResults)

    QS_FIELD(double, AverageRank)

    [[nodiscard]] double GetAverageRank() const;

    QS_FIELD(QString, Seed)

    // Value Range: 0 - 256
    QS_FIELD(int, LastYearPlacing)

    QS_COLLECTION_OBJECTS(QList, TournamentUser, Players)

    QString ToString();
};


#endif //TOURNAMENTTEAM_H
