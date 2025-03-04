//
// Created by clonewith on 25-3-3.
//

#ifndef ROUNDBEATMAP_H
#define ROUNDBEATMAP_H

#ifndef QS_HAS_JSON
#define QS_HAS_JSON
#endif

#include <qstring.h>

#include "../libs/qserializer.h"

class RoundBeatmap : public QSerializer
{
    Q_GADGET
    QS_SERIALIZABLE

public:
    QS_FIELD(int, ID)
    QS_FIELD(QString, ModIndex)
    QS_FIELD(QString, Mods)
};


#endif //ROUNDBEATMAP_H
