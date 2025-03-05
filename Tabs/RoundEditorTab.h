//
// Created by clonewith on 25-3-5.
//

#ifndef ROUNDEDITORTAB_H
#define ROUNDEDITORTAB_H

#include <QWidget>

#include "../Models/LadderInfo.h"
#include "../Models/RoundBeatmapModel.h"
#include "../Models/TournamentRoundModel.h"
#include "../Models/TournamentUserModel.h"


QT_BEGIN_NAMESPACE

namespace Ui
{
    class RoundEditorTab;
}

QT_END_NAMESPACE

class RoundEditorTab : public QWidget
{
    Q_OBJECT

public:
    explicit RoundEditorTab(LadderInfo *ladderInfo, QWidget *parent = nullptr);
    ~RoundEditorTab() override;

private slots:
    void updateName();
    void updateContent();
    void writeContent();
    void updateRightList();

private:
    Ui::RoundEditorTab *ui;
    LadderInfo *ladder;
    TournamentRound currentRound;
    TournamentRoundModel *model;
    RoundBeatmapModel *mapModel;
    TournamentUserModel *refereeModel;
};


#endif //ROUNDEDITORTAB_H
