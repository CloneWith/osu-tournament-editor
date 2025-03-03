//
// Created by clonewith on 25-3-3.
//

#ifndef TOURNAMENTPROGRESSION_H
#define TOURNAMENTPROGRESSION_H


class TournamentProgression
{
public:
    int SourceID;
    int TargetID;

    bool Losers;

    TournamentProgression(int sourceID, int targetID, bool losers = false);
};


#endif //TOURNAMENTPROGRESSION_H
