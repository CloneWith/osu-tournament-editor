//
// Created by clonewith on 25-3-3.
//

#ifndef SEEDINGRESULT_H
#define SEEDINGRESULT_H
#include "SeedingBeatmap.h"


class SeedingResult
{
public:
    QList<SeedingBeatmap> Beatmaps = {};

    QString Mod = "";

    // Value Range: 1 - 256
    int Seed = 0;

    SeedingResult() = default;
};


#endif //SEEDINGRESULT_H
