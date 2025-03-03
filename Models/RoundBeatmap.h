//
// Created by clonewith on 25-3-3.
//

#ifndef ROUNDBEATMAP_H
#define ROUNDBEATMAP_H
#include <qstring.h>

#include "TournamentBeatmap.h"


class RoundBeatmap {
public:
    int ID = 0;
    QString ModIndex = "";
    QString Mods = "";

    // JSON Property: BeatmapInfo
    TournamentBeatmap Beatmap;
};



#endif //ROUNDBEATMAP_H
