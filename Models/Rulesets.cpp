//
// Created by clonewith on 25-3-4.
//

#include "Rulesets.h"

/// Get the corresponding short name of specified ruleset.
/// @param ruleset the element from @code StandardRulesets@endcode
/// @return the short name of the ruleset. If is @code Unknown@endcode, returns an empty string
QString Rulesets::GetShortName(StandardRulesets ruleset)
{
    switch (ruleset)
    {
        case Standard:
            return "osu";
        case Taiko:
            return "taiko";
        case Catch:
            return "fruits";
        case Mania:
            return "mania";
        default:
            return "";
    }
}

/// Get the corresponding full name of specified ruleset.
/// @param ruleset the element from @code StandardRulesets@endcode
/// @return the full name of the ruleset. If is @code Unknown@endcode, returns an empty string
QString Rulesets::GetFullName(StandardRulesets ruleset)
{
    switch (ruleset)
    {
        case Standard:
            return "osu!";
        case Taiko:
            return "osu!taiko";
        case Catch:
            return "osu!catch";
        case Mania:
            return "osu!mania";
        default:
            return "";
    }
}

/// Get the corresponding short name of specified ruleset.
/// @param name the short name string
/// @return an element of @code StandardRulesets@endcode if an available one is found
StandardRulesets Rulesets::FromShortName(const QString &name)
{
    const QString lowerName = name.toLower();

    if (lowerName == "osu") return Standard;
    if (lowerName == "taiko") return Taiko;
    if (lowerName == "fruits") return Catch;
    if (lowerName == "mania") return Mania;
    return Unknown;
}

/// Get the corresponding full name of specified ruleset.
/// @param name the full name string
/// @return an element of @code StandardRulesets@endcode if an available one is found
StandardRulesets Rulesets::FromFullName(const QString &name)
{
    const QString lowerName = name.toLower();

    if (lowerName == "osu!") return Standard;
    if (lowerName == "osu!taiko") return Taiko;
    if (lowerName == "osu!catch") return Catch;
    if (lowerName == "osu!mania") return Mania;
    return Unknown;
}
