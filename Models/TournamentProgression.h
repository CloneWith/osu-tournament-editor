//
// Created by clonewith on 25-3-3.
//

#ifndef TOURNAMENTPROGRESSION_H
#define TOURNAMENTPROGRESSION_H

#ifndef QS_HAS_JSON
#define QS_HAS_JSON
#endif

#include "../libs/qserializer.h"

class TournamentProgression : public QSerializer
{
    Q_GADGET
    QS_SERIALIZABLE

    QS_FIELD(int, SourceID)
    QS_FIELD(int, TargetID)

    QS_FIELD(bool, Losers)

public:
    TournamentProgression(int sourceID = 0, int targetID = 0, bool losers = false);
};


#endif //TOURNAMENTPROGRESSION_H
