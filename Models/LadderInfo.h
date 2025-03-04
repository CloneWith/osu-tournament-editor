//
// Created by clonewith on 25-3-3.
//

#ifndef LADDERINFO_H
#define LADDERINFO_H

#ifndef QS_HAS_JSON
#define QS_HAS_JSON
#endif

#include <qlist.h>

#include "RulesetInfo.h"
#include "TournamentMatch.h"
#include "TournamentProgression.h"
#include "TournamentRound.h"
#include "TournamentTeam.h"
#include "../libs/qserializer.h"


class LadderInfo : public QSerializer
{
    Q_GADGET
    QS_SERIALIZABLE

    QS_OBJECT(RulesetInfo, Ruleset)
    QS_COLLECTION_OBJECTS(QList, TournamentMatch, Matches)
    QS_COLLECTION_OBJECTS(QList, TournamentRound, Rounds)
    QS_COLLECTION_OBJECTS(QList, TournamentTeam, Teams)

    QS_COLLECTION_OBJECTS(QList, TournamentProgression, Progressions)

    // Value Range: 640 - 1366
    QS_FIELD(int, ChromaKeyWidth)

    // Value Range: 3 - 4
    QS_FIELD(int, PlayersPerTeam)

    QS_FIELD(bool, UseUtcTime)
    QS_FIELD(bool, AutoProgressScreens)
    QS_FIELD(bool, SplitMapPoolByMods)
    QS_FIELD(bool, DisplayTeamSeeds)

public:
    LadderInfo()
    {
        ChromaKeyWidth = 1024;
        PlayersPerTeam = 4;

        UseUtcTime = false;
        AutoProgressScreens = true;
        SplitMapPoolByMods = true;
        DisplayTeamSeeds = false;
    };
};


#endif //LADDERINFO_H
