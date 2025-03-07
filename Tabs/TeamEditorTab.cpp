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

    connect(ui->listTeams->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
        this, SLOT(updateWidgetState()));

    connect(ui->buttonAddTeam, SIGNAL(clicked()), this, SLOT(addTeam()));
    connect(ui->buttonRemoveTeam, SIGNAL(clicked()), this, SLOT(removeTeam()));
    connect(ui->buttonAddPlayer, SIGNAL(clicked()), this, SLOT(addPlayer()));
    connect(ui->buttonRemovePlayer, SIGNAL(clicked()), this, SLOT(removePlayer()));

    connect(ui->inputTeamName, SIGNAL(textChanged(QString)), this, SLOT(updateName()));
    connect(ui->listTeams->selectionModel(), &QItemSelectionModel::currentChanged, this, &TeamEditorTab::updateContent);

    connect(ui->inputTeamName, SIGNAL(editingFinished()), this, SLOT(commitTeamChanges()));
    connect(ui->inputTeamAcronym, SIGNAL(editingFinished()), this, SLOT(commitTeamChanges()));
    connect(ui->inputFlag, SIGNAL(editingFinished()), this, SLOT(commitTeamChanges()));
    connect(ui->inputSeed, SIGNAL(editingFinished()), this, SLOT(commitTeamChanges()));
    connect(ui->inputLastYearPlacing, SIGNAL(editingFinished()), this, SLOT(commitTeamChanges()));
}

void TeamEditorTab::updateName()
{
    if (ui->inputTeamName->text().trimmed().isEmpty()) return;

    const QModelIndex index = ui->listTeams->currentIndex();
    model->setData(index, ui->inputTeamName->text(), Qt::DisplayRole);
}

void TeamEditorTab::updateWidgetState()
{
    const bool teamSelectionValid = ui->listTeams->selectionModel()->currentIndex().isValid();

    ui->inputTeamName->setEnabled(teamSelectionValid);
    ui->inputTeamAcronym->setEnabled(teamSelectionValid);
    ui->inputFlag->setEnabled(teamSelectionValid);
    ui->inputSeed->setEnabled(teamSelectionValid);
    ui->inputLastYearPlacing->setEnabled(teamSelectionValid);

    ui->buttonRemoveTeam->setEnabled(teamSelectionValid);
    ui->buttonAddPlayer->setEnabled(teamSelectionValid);

    ui->buttonRemovePlayer->setEnabled(teamSelectionValid && ui->listPlayers->selectionModel()->currentIndex().isValid());
}

void TeamEditorTab::updateContent()
{
    const QModelIndex index = ui->listTeams->currentIndex();
    currentTeamIndex = index.row();

    currentTeam = index.isValid() ? model->data(index, Qt::EditRole).value<TournamentTeam>() : TournamentTeam();

    ui->inputTeamName->setText(currentTeam.FullName);
    ui->inputTeamAcronym->setText(currentTeam.Acronym);
    ui->inputFlag->setText(currentTeam.FlagName);
    ui->inputSeed->setText(currentTeam.Seed);
    ui->inputLastYearPlacing->setValue(currentTeam.LastYearPlacing);
    ui->textAverageRank->setText(QString::fromStdString(std::to_string(currentTeam.AverageRank)));

    updatePlayerList();
    updateWidgetState();
}

void TeamEditorTab::addTeam()
{
    ladder->Teams.append(TournamentTeam());
    model->addTeam(TournamentTeam());
}

void TeamEditorTab::removeTeam()
{
    // TODO: Support removing one line once only for now. May implement multiple line management?
    ladder->Teams.removeAt(currentTeamIndex);
    model->removeRows(currentTeamIndex, 1);
}

void TeamEditorTab::addPlayer()
{
    ladder->Teams[currentTeamIndex].Players.append(TournamentUser());
    currentTeam.Players.append(TournamentUser());
    playerModel->addUser(TournamentUser());
}

void TeamEditorTab::removePlayer()
{
    const QModelIndex index = ui->listPlayers->currentIndex();
    ladder->Teams[currentTeamIndex].Players.removeAt(index.row());
    currentTeam.Players.removeAt(index.row());
    playerModel->removeRows(index.row(), 1);
}

void TeamEditorTab::commitTeamChanges()
{
    commitTeamToModel();
    syncTeamToLadder();
}

void TeamEditorTab::commitTeamToModel()
{
    // Step 1: Update currentTeam with input values
    // The player list is fetched directly from the model, and wouldn't be affected.
    currentTeam.FullName = ui->inputTeamName->text();
    currentTeam.Acronym = ui->inputTeamAcronym->text();
    currentTeam.FlagName = ui->inputFlag->text();
    currentTeam.Seed = ui->inputSeed->text();
    currentTeam.LastYearPlacing = ui->inputLastYearPlacing->value();

    // Step 2: Commit new team data to model
    model->setData(ui->listTeams->currentIndex(), QVariant::fromValue(currentTeam), Qt::EditRole);
}

void TeamEditorTab::syncTeamToLadder()
{
    // Step 1: Get updated team from model (should have been updated by commitTeamToModel)
    const auto index = ui->listTeams->currentIndex();
    currentTeamIndex = index.row();
    model->setData(index, QVariant::fromValue(currentTeam), Qt::EditRole);
    const auto newTeamData = model->GetTeamAt(currentTeamIndex);

    // Step 2: Update normal fields without breaking the reference to inner lists
    ladder->Teams[currentTeamIndex].FullName = newTeamData.FullName;
    ladder->Teams[currentTeamIndex].Acronym = newTeamData.Acronym;
    ladder->Teams[currentTeamIndex].FlagName = newTeamData.FlagName;
    ladder->Teams[currentTeamIndex].Seed = newTeamData.Seed;
    ladder->Teams[currentTeamIndex].LastYearPlacing = newTeamData.LastYearPlacing;
}

// Player data changes come from the model.
void TeamEditorTab::commitPlayerChanges()
{
    // Step 1: Get index and detect
    // We only change one grid once, so there shouldn't be much problem...
    const auto index = ui->listPlayers->currentIndex();

    // If none selected, don't update
    if (!index.isValid()) return;

    // Step 2: Get corresponding player data from currentTeam
    const auto newPlayerData = playerModel->data(index, Qt::EditRole).value<TournamentUser>();

    // Step 3: Commit back to currentTeam and parent model, and forward to ladder
    currentTeam.Players[index.row()] = newPlayerData;
    commitTeamToModel();
    ladder->Teams[currentTeamIndex].Players[index.row()] = newPlayerData;
}

void TeamEditorTab::updatePlayerList()
{
    if (playerModel != nullptr)
        disconnect(playerModel, SIGNAL(dataUpdated()), this, SLOT(commitPlayerChanges()));

    playerModel = new TournamentUserModel(currentTeam.Players);
    ui->listPlayers->setModel(playerModel);

    connect(playerModel, SIGNAL(dataUpdated()), this, SLOT(commitPlayerChanges()));
    connect(ui->listPlayers->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
        this, SLOT(updateWidgetState()));
}

TeamEditorTab::~TeamEditorTab()
{
    delete ui;
}
