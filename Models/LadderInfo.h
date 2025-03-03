//
// Created by clonewith on 25-3-3.
//

#ifndef LADDERINFO_H
#define LADDERINFO_H
#include <qlist.h>

#include "RulesetInfo.h"
#include "TournamentMatch.h"
#include "TournamentProgression.h"
#include "TournamentRound.h"
#include "TournamentTeam.h"


class LadderInfo
{
public:
    RulesetInfo Ruleset;

    QList<TournamentMatch> Matches = {};
    QList<TournamentRound> Rounds = {};
    QList<TournamentTeam> Teams = {};

    // only used for serialisation
    QList<TournamentProgression> Progressions = {};

    // Value Range: 640 - 1366
    int ChromaKeyWidth = 1024;

    // Value Range: 3 - 4
    int PlayersPerTeam = 4;

    bool UseUtcTime = false;
    bool AutoProgressScreens = true;
    bool SplitMapPoolByMods = true;
    bool DisplayTeamSeeds = false;

    LadderInfo() = default;
};


#endif //LADDERINFO_H
