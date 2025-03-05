//
// Created by clonewith on 25-3-5.
//

// You may need to build the project (run Qt uic code generator) to get "ui_TeamEditorTab.h" resolved

#include "TeamEditorTab.h"
#include "ui_TeamEditorTab.h"


TeamEditorTab::TeamEditorTab(LadderInfo *ladderInfo, QWidget *parent) : QWidget(parent), ui(new Ui::TeamEditorTab)
{
    ui->setupUi(this);

    this->ladder = ladderInfo;
    this->model = new TournamentTeamModel(ladderInfo->Teams);

    ui->listTeams->setModel(model);

    connect(ui->inputTeamName, SIGNAL(textChanged(QString)), this, SLOT(updateName()));
    connect(ui->listTeams->selectionModel(), &QItemSelectionModel::currentChanged, this, &TeamEditorTab::updateContent);

}

void TeamEditorTab::updateName()
{
    if (ui->inputTeamName->text().trimmed().isEmpty()) return;

    QModelIndex index = ui->listTeams->currentIndex();
    model->setData(index, ui->inputTeamName->text(), Qt::DisplayRole);
}

void TeamEditorTab::updateContent()
{
    QModelIndex index = ui->listTeams->currentIndex();
    currentTeam = model->data(index, Qt::EditRole).value<TournamentTeam>();

    ui->inputTeamName->setText(currentTeam.FullName);
    ui->inputTeamAcronym->setText(currentTeam.Acronym);
    ui->inputFlag->setText(currentTeam.FlagName);
    ui->inputSeed->setText(currentTeam.Seed);
    ui->inputLastYearPlacing->setValue(currentTeam.LastYearPlacing);
    ui->textAverageRank->setText(QString::fromStdString(std::to_string(currentTeam.AverageRank)));

    updatePlayerList();
}

void TeamEditorTab::writeContent()
{
    QModelIndex index = ui->listTeams->currentIndex();
    model->setData(index, QVariant::fromValue(currentTeam), Qt::EditRole);
}

void TeamEditorTab::updatePlayerList()
{
    playerModel = new TournamentUserModel(currentTeam.Players);
    ui->listPlayers->setModel(playerModel);
}

TeamEditorTab::~TeamEditorTab()
{
    delete ui;
}
