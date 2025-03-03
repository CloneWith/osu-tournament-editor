//
// Created by clonewith on 25-3-3.
//

#ifndef RULESETINFO_H
#define RULESETINFO_H
#include <qstring.h>


class RulesetInfo
{
public:
    QString ShortName = "";
    int OnlineID = -1;

    QString Name = "";
    QString InstantiationInfo = "";

    RulesetInfo() = default;
};


#endif //RULESETINFO_H
