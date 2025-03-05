//
// Created by clonewith on 25-3-3.
//

// You may need to build the project (run Qt uic code generator) to get "ui_BasicInformationTab.h" resolved

#include "BasicInformationTab.h"
#include "ui_BasicInformationTab.h"
#include "../Models/LadderInfo.h"
#include "../Models/Rulesets.h"


BasicInformationTab::BasicInformationTab(LadderInfo *ladderInfo, QWidget *parent)
    : QWidget(parent), ui(new Ui::BasicInformationTab)
{
    ui->setupUi(this);

    this->ladder = ladderInfo;

    ui->textBoxTournamentName->setText(ladder->Name);
    ui->comboBoxRuleset->addItems({ "osu!", "osu!taiko", "osu!catch", "osu!mania" });
    ui->comboBoxRuleset->setCurrentText(ladder->Ruleset.Name);

    ui->inputChromaWidth->setValue(ladder->ChromaKeyWidth);
    ui->inputPlayersPerTeam->setValue(ladder->PlayersPerTeam);
    ui->sliderChromaWidth->setValue(ladder->ChromaKeyWidth);
    ui->sliderPlayersPerTeam->setValue(ladder->PlayersPerTeam);

    ui->switchShowUtcTime->setChecked(ladder->UseUtcTime);
    ui->switchAutoProgress->setChecked(ladder->AutoProgressScreens);
    ui->switchSplitByMods->setChecked(ladder->SplitMapPoolByMods);
    ui->switchDisplaySeeds->setChecked(ladder->DisplayTeamSeeds);

    connect(ui->comboBoxRuleset, SIGNAL(currentTextChanged(QString)), this, SLOT(updateRuleset()));
    connect(ui->sliderChromaWidth, SIGNAL(valueChanged(int)), this, SLOT(updateSliders()));
    connect(ui->sliderPlayersPerTeam, SIGNAL(valueChanged(int)), this, SLOT(updateSliders()));
    connect(ui->inputChromaWidth, SIGNAL(valueChanged(int)), this, SLOT(updateInput()));
    connect(ui->inputPlayersPerTeam, SIGNAL(valueChanged(int)), this, SLOT(updateInput()));
    connect(ui->switchShowUtcTime, SIGNAL(toggled(bool)), this, SLOT(updateSwitches()));
    connect(ui->switchAutoProgress, SIGNAL(toggled(bool)), this, SLOT(updateSwitches()));
    connect(ui->switchSplitByMods, SIGNAL(toggled(bool)), this, SLOT(updateSwitches()));
    connect(ui->switchDisplaySeeds, SIGNAL(toggled(bool)), this, SLOT(updateSwitches()));
}

void BasicInformationTab::updateForm()
{
    updateRuleset();
    updateSwitches();
    updateSliders();
    updateInput();
}

void BasicInformationTab::updateRuleset()
{
    StandardRulesets ruleset = Rulesets::FromFullName(ui->comboBoxRuleset->currentText());

    if (ruleset != Unknown)
    {
        ladder->Ruleset.Name = Rulesets::GetFullName(ruleset);
        ladder->Ruleset.ShortName = Rulesets::GetShortName(ruleset);
        ui->comboBoxRuleset->setStyleSheet("");
    }
    else
    {
        ui->comboBoxRuleset->setStyleSheet("QComboBox:editable { color: #fe9828; }");
    }
}

void BasicInformationTab::updateSwitches()
{
    ladder->UseUtcTime = ui->switchShowUtcTime->isChecked();
    ladder->AutoProgressScreens = ui->switchAutoProgress->isChecked();
    ladder->SplitMapPoolByMods = ui->switchSplitByMods->isChecked();
    ladder->DisplayTeamSeeds = ui->switchDisplaySeeds->isChecked();
}

void BasicInformationTab::updateInput()
{
    ladder->ChromaKeyWidth = ui->inputChromaWidth->value();
    ladder->PlayersPerTeam = ui->inputPlayersPerTeam->value();

    ui->sliderChromaWidth->setValue(ladder->ChromaKeyWidth);
    ui->sliderPlayersPerTeam->setValue(ladder->PlayersPerTeam);
}

void BasicInformationTab::updateSliders()
{
    ladder->ChromaKeyWidth = ui->sliderChromaWidth->value();
    ladder->PlayersPerTeam = ui->sliderPlayersPerTeam->value();

    ui->inputChromaWidth->setValue(ladder->ChromaKeyWidth);
    ui->inputPlayersPerTeam->setValue(ladder->PlayersPerTeam);
}

BasicInformationTab::~BasicInformationTab()
{
    delete ui;
}
