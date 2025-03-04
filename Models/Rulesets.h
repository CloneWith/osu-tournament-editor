//
// Created by clonewith on 25-3-4.
//

#ifndef RULESETS_H
#define RULESETS_H
#include <qstring.h>

/// A list of built-in rulesets in osu!lazer.
enum StandardRulesets
{
    /// An unknown ruleset, or not detected
    Unknown,

    /// osu!standard
    Standard,

    /// osu!taiko
    Taiko,

    /// osu!catch
    Catch,

    /// osu!mania
    Mania,
};

/// Static conversion class for string enum compatibility.
class Rulesets
{
public:
    static QString GetShortName(StandardRulesets ruleset);
    static QString GetFullName(StandardRulesets ruleset);
    static StandardRulesets FromShortName(const QString &name);
    static StandardRulesets FromFullName(const QString &name);
};


#endif //RULESETS_H
