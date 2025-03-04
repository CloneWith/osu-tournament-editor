//
// Created by clonewith on 25-3-3.
//

#ifndef SEEDINGRESULT_H
#define SEEDINGRESULT_H
#include "SeedingBeatmap.h"

#ifndef QS_HAS_JSON
#define QS_HAS_JSON
#endif

#include "../libs/qserializer.h"

class SeedingResult : public QSerializer
{
    Q_GADGET
    QS_SERIALIZABLE

    QS_COLLECTION_OBJECTS(QList, SeedingBeatmap, Beatmaps)

    QS_FIELD(QString, Mod)

    // Value Range: 1 - 256
    QS_FIELD(int, Seed)

public:
    SeedingResult() = default;
};


#endif //SEEDINGRESULT_H
