//
// Created by clonewith on 25-3-3.
//

#ifndef BEATMAPCHOICE_H
#define BEATMAPCHOICE_H

#ifndef QS_HAS_JSON
#define QS_HAS_JSON
#endif
#include "ChoiceType.h"
#include "TeamColour.h"
#include "../libs/qserializer.h"

class BeatmapChoice : public QSerializer
{
    Q_GADGET
    QS_SERIALIZABLE

    QS_FIELD(TeamColour, Team)
    QS_FIELD(ChoiceType, Type)
    QS_FIELD(int, BeatmapID)

public:
    BeatmapChoice() = default;
};


#endif //BEATMAPCHOICE_H
