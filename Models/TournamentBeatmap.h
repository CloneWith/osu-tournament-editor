//
// Created by clonewith on 25-3-3.
//

#ifndef TOURNAMENTBEATMAP_H
#define TOURNAMENTBEATMAP_H

#ifndef QS_HAS_JSON
#define QS_HAS_JSON
#endif

#include "../libs/qserializer.h"

/// <summary>
/// A Stub class for basic implementation and JSON compatibility.
/// </summary>
class TournamentBeatmap : public QSerializer
{
    Q_GADGET
    QS_SERIALIZABLE

    QS_FIELD(int, OnlineID)

public:
    TournamentBeatmap() = default;
};


#endif //TOURNAMENTBEATMAP_H
