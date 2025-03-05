//
// Created by clonewith on 25-3-3.
//

#ifndef BASICINFORMATIONTAB_H
#define BASICINFORMATIONTAB_H

#include <QWidget>


class LadderInfo;
QT_BEGIN_NAMESPACE

namespace Ui
{
    class BasicInformationTab;
}

QT_END_NAMESPACE

class BasicInformationTab : public QWidget
{
    Q_OBJECT

public:
    explicit BasicInformationTab(LadderInfo *ladderInfo, QWidget *parent = nullptr);

    ~BasicInformationTab() override;

private slots:
    void updateForm();
    void updateRuleset();
    void updateSwitches();
    void updateInput();
    void updateSliders();

private:
    Ui::BasicInformationTab *ui;
    LadderInfo *ladder;
};


#endif //BASICINFORMATIONTAB_H
