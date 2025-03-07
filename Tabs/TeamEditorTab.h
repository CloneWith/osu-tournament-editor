//
// Created by clonewith on 25-3-5.
//

#ifndef TEAMEDITORTAB_H
#define TEAMEDITORTAB_H

#include <QWidget>

#include "../Models/LadderInfo.h"
#include "../Models/TournamentTeamModel.h"
#include "../Models/TournamentUserModel.h"


QT_BEGIN_NAMESPACE

namespace Ui
{
    class TeamEditorTab;
}

QT_END_NAMESPACE

class TeamEditorTab : public QWidget
{
    Q_OBJECT

public:
    explicit TeamEditorTab(LadderInfo *ladderInfo, QWidget *parent = nullptr);
    ~TeamEditorTab() override;

private slots:
    void updateName();
    void updateWidgetState();
    void updateContent();

    void addTeam();
    void removeTeam();

    void addPlayer();
    void removePlayer();

    void commitTeamChanges();
    void commitTeamToModel();
    void syncTeamToLadder();
    void commitPlayerChanges();

    void updatePlayerList();

private:
    Ui::TeamEditorTab *ui;
    LadderInfo *ladder;
    int currentTeamIndex = -1;
    TournamentTeam currentTeam;
    TournamentTeamModel *model;
    TournamentUserModel *playerModel = nullptr;
};


#endif //TEAMEDITORTAB_H
