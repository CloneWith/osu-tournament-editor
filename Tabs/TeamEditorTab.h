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
    void updateContent();
    void writeContent();
    void updatePlayerList();

private:
    Ui::TeamEditorTab *ui;
    LadderInfo *ladder;
    TournamentTeam currentTeam;
    TournamentTeamModel *model;
    TournamentUserModel *playerModel;
};


#endif //TEAMEDITORTAB_H
