//
// Created by clonewith on 25-3-3.
//

#ifndef SEEDINGBEATMAP_H
#define SEEDINGBEATMAP_H
#include "TournamentBeatmap.h"

#ifndef QS_HAS_JSON
#define QS_HAS_JSON
#endif

#include "../libs/qserializer.h"

class SeedingBeatmap : public QSerializer
{
    Q_GADGET
    QS_SERIALIZABLE

    QS_FIELD(int, ID)

    // JSON Property: BeatmapInfo
    QS_OBJECT(TournamentBeatmap, Beatmap)

    long Score = 0;

    // Value Range: 1 - 256
    int Seed = 0;

public:
    SeedingBeatmap() = default;
};


#endif //SEEDINGBEATMAP_H
