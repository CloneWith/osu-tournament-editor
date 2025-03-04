//
// Created by clonewith on 25-3-3.
//

#ifndef RULESETINFO_H
#define RULESETINFO_H
#include <qstring.h>

#ifndef QS_HAS_JSON
#define QS_HAS_JSON
#endif

#include "../libs/qserializer.h"

class RulesetInfo : public QSerializer
{
    Q_GADGET
    QS_SERIALIZABLE

    QS_FIELD(QString, ShortName)
    QS_FIELD(int, OnlineID)
    QS_FIELD(QString, Name)
    QS_FIELD(QString, InstantiationInfo)

public:
    RulesetInfo() = default;
};


#endif //RULESETINFO_H
