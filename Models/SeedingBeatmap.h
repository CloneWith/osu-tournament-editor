//
// Created by clonewith on 25-3-3.
//

#ifndef SEEDINGBEATMAP_H
#define SEEDINGBEATMAP_H
#include "TournamentBeatmap.h"


class SeedingBeatmap
{
public:
    int ID = 0;

    // JSON Property: BeatmapInfo
    TournamentBeatmap Beatmap = TournamentBeatmap();

    long Score = 0;

    // Value Range: 1 - 256
    int Seed = 0;

    SeedingBeatmap() = default;
};


#endif //SEEDINGBEATMAP_H
