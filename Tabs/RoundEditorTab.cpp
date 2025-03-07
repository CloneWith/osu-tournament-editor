//
// Created by clonewith on 25-3-5.
//

// You may need to build the project (run Qt uic code generator) to get "ui_RoundEditorTab.h" resolved

#include "RoundEditorTab.h"
#include "ui_RoundEditorTab.h"
#include "../Models/TournamentRoundModel.h"


RoundEditorTab::RoundEditorTab(LadderInfo *ladderInfo, QWidget *parent) : QWidget(parent),
    ui(new Ui::RoundEditorTab)
{
    ui->setupUi(this);

    this->ladder = ladderInfo;
    this->model = new TournamentRoundModel(ladder->Rounds);

    ui->listRounds->setModel(model);

    connect(ui->inputRoundName, SIGNAL(textChanged(QString)), this, SLOT(updateName()));
    connect(ui->listRounds->selectionModel(), &QItemSelectionModel::currentChanged, this, &RoundEditorTab::updateContent);

    connect(ui->buttonAddRound, SIGNAL(clicked()), this, SLOT(addRound()));
    connect(ui->buttonRemoveRound, SIGNAL(clicked()), this, SLOT(removeRound()));
    connect(ui->buttonAddBeatmap, SIGNAL(clicked()), this, SLOT(addBeatmap()));
    connect(ui->buttonRemoveBeatmap, SIGNAL(clicked()), this, SLOT(removeBeatmap()));
    connect(ui->buttonAddReferee, SIGNAL(clicked()), this, SLOT(addReferee()));
    connect(ui->buttonRemoveReferee, SIGNAL(clicked()), this, SLOT(removeReferee()));

    connect(ui->inputRoundName, SIGNAL(editingFinished()), this, SLOT(commitRoundChanges()));
    connect(ui->inputRoundDescription, SIGNAL(editingFinished()), this, SLOT(commitRoundChanges()));
    connect(ui->inputDate, SIGNAL(editingFinished()), this, SLOT(commitRoundChanges()));
    connect(ui->inputBanCount, SIGNAL(editingFinished()), this, SLOT(commitRoundChanges()));
    connect(ui->inputBestOf, SIGNAL(editingFinished()), this, SLOT(commitRoundChanges()));
    connect(ui->checkBoxUseBoard, SIGNAL(toggled(bool)), this, SLOT(commitRoundChanges()));
}

void RoundEditorTab::updateName()
{
    if (ui->inputRoundName->text().trimmed().isEmpty()) return;

    QModelIndex index = ui->listRounds->currentIndex();
    model->setData(index, ui->inputRoundName->text(), Qt::DisplayRole);
}

void RoundEditorTab::updateWidgetState()
{
    const bool roundSelectionValid = ui->listRounds->selectionModel()->currentIndex().isValid();

    ui->inputRoundName->setEnabled(roundSelectionValid);
    ui->inputRoundDescription->setEnabled(roundSelectionValid);
    ui->inputDate->setEnabled(roundSelectionValid);
    ui->inputBestOf->setEnabled(roundSelectionValid);
    ui->inputBanCount->setEnabled(roundSelectionValid);
    ui->checkBoxUseBoard->setEnabled(roundSelectionValid);

    ui->buttonRemoveRound->setEnabled(roundSelectionValid);
    ui->buttonAddBeatmap->setEnabled(roundSelectionValid);
    ui->buttonAddReferee->setEnabled(roundSelectionValid);
    ui->buttonRemoveBeatmap->setEnabled(roundSelectionValid && ui->listBeatmaps->selectionModel()->currentIndex().isValid());
    ui->buttonRemoveReferee->setEnabled(roundSelectionValid && ui->listReferees->selectionModel()->currentIndex().isValid());
}


void RoundEditorTab::updateContent()
{
    const QModelIndex index = ui->listRounds->currentIndex();
    currentRound = model->data(index, Qt::EditRole).value<TournamentRound>();

    ui->inputRoundName->setText(currentRound.Name);
    ui->inputRoundDescription->setText(currentRound.Description);
    ui->inputDate->setDateTime(currentRound.StartDate);
    ui->inputBestOf->setValue(currentRound.BestOf);
    ui->inputBanCount->setValue(currentRound.BanCount);
    ui->checkBoxUseBoard->setChecked(currentRound.UseBoard);

    updateRightList();
    updateWidgetState();
}

void RoundEditorTab::addRound()
{
    ladder->Rounds.append(TournamentRound());
    model->addRound(TournamentRound());
}

void RoundEditorTab::removeRound()
{
    const auto index = ui->listRounds->currentIndex();

    if (!index.isValid() || index.row() >= model->rowCount()) return;

    ladder->Rounds.removeAt(index.row());
    model->removeRows(index.row(), 1);
}

void RoundEditorTab::addBeatmap()
{
    ladder->Rounds[ui->listRounds->currentIndex().row()].Beatmaps.append(RoundBeatmap());
    currentRound.Beatmaps.append(RoundBeatmap());
    mapModel->addBeatmap(RoundBeatmap());
}

void RoundEditorTab::removeBeatmap()
{
    const QModelIndex index = ui->listBeatmaps->currentIndex();

    if (!index.isValid()) return;

    ladder->Rounds[ui->listRounds->currentIndex().row()].Beatmaps.removeAt(index.row());
    currentRound.Beatmaps.removeAt(index.row());
    mapModel->removeRows(index.row(), 1);
}

void RoundEditorTab::addReferee()
{
    ladder->Rounds[ui->listRounds->currentIndex().row()].Referees.append(TournamentUser());
    currentRound.Referees.append(TournamentUser());
    refereeModel->addUser(TournamentUser());
}

void RoundEditorTab::removeReferee()
{
    const QModelIndex index = ui->listReferees->currentIndex();

    if (!index.isValid()) return;

    ladder->Rounds[ui->listRounds->currentIndex().row()].Referees.removeAt(index.row());
    currentRound.Referees.removeAt(index.row());
    refereeModel->removeRows(index.row(), 1);
}

void RoundEditorTab::commitRoundChanges()
{
    commitRoundToModel();
    syncRoundToLadder();
}

void RoundEditorTab::commitRoundToModel()
{
    // Step 1: Update currentRound with input values
    // The lists are fetched directly from the model, and wouldn't be affected.
    currentRound.Name = ui->inputRoundName->text();
    currentRound.Description = ui->inputRoundDescription->text();
    currentRound.StartDate = ui->inputDate->dateTime();
    currentRound.BestOf = ui->inputBestOf->value();
    currentRound.BanCount = ui->inputBanCount->value();
    currentRound.UseBoard = ui->checkBoxUseBoard->isChecked();

    // Step 2: Commit new round data to model
    model->setData(ui->listRounds->currentIndex(), QVariant::fromValue(currentRound), Qt::EditRole);
}

void RoundEditorTab::syncRoundToLadder()
{
    // Step 1: Get updated round from model (should have been updated by commitRoundToModel)
    const auto index = ui->listRounds->currentIndex();
    model->setData(index, QVariant::fromValue(currentRound), Qt::EditRole);
    const auto newRoundData = model->GetRoundAt(index.row());

    // Step 2: Update normal fields without breaking the reference to inner lists
    ladder->Rounds[index.row()].Name = newRoundData.Name;
    ladder->Rounds[index.row()].Description = newRoundData.Description;
    ladder->Rounds[index.row()].StartDate = newRoundData.StartDate;
    ladder->Rounds[index.row()].BestOf = newRoundData.BestOf;
    ladder->Rounds[index.row()].BanCount = newRoundData.BanCount;
    ladder->Rounds[index.row()].UseBoard = newRoundData.UseBoard;
}

// Beatmap data changes come from the model.
void RoundEditorTab::commitBeatmapChanges()
{
    // Step 1: Get index and detect
    // We only change one grid once, so there shouldn't be much problem...
    const auto index = ui->listBeatmaps->currentIndex();

    // If none selected, don't update
    if (!index.isValid()) return;

    // Step 2: Get corresponding beatmap data from currentRound
    const auto newBeatmapData = mapModel->data(index, Qt::EditRole).value<RoundBeatmap>();

    // Step 3: Commit back to currentRound and parent model, and forward to ladder
    currentRound.Beatmaps[index.row()] = newBeatmapData;
    commitRoundChanges();
    ladder->Rounds[ui->listRounds->currentIndex().row()].Beatmaps[index.row()] = newBeatmapData;
}

// Referee data changes come from the model.
void RoundEditorTab::commitRefereeChanges()
{
    // Step 1: Get index and detect
    // We only change one grid once, so there shouldn't be much problem...
    const auto index = ui->listReferees->currentIndex();

    // If none selected, don't update
    if (!index.isValid()) return;

    // Step 2: Get corresponding referee data from currentRound
    const auto newRefereeData = refereeModel->data(index, Qt::EditRole).value<TournamentUser>();

    // Step 3: Commit back to currentRound and parent model, and forward to ladder
    currentRound.Referees[index.row()] = newRefereeData;
    commitRoundChanges();
    ladder->Rounds[ui->listRounds->currentIndex().row()].Referees[index.row()] = newRefereeData;
}

void RoundEditorTab::updateRightList()
{
    if (mapModel != nullptr)
        disconnect(mapModel, SIGNAL(dataUpdated()), this, SLOT(commitBeatmapChanges()));

    if (refereeModel != nullptr)
        disconnect(refereeModel, SIGNAL(dataUpdated()), this, SLOT(commitRefereeChanges()));

    mapModel = new RoundBeatmapModel(currentRound.Beatmaps);
    refereeModel = new TournamentUserModel(currentRound.Referees);
    ui->listBeatmaps->setModel(mapModel);
    ui->listReferees->setModel(refereeModel);

    connect(mapModel, SIGNAL(dataUpdated()), this, SLOT(commitBeatmapChanges()));
    connect(ui->listBeatmaps->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
        this, SLOT(updateWidgetState()));

    connect(refereeModel, SIGNAL(dataUpdated()), this, SLOT(commitRefereeChanges()));
    connect(ui->listReferees->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
        this, SLOT(updateWidgetState()));
}

RoundEditorTab::~RoundEditorTab()
{
    delete ui;
}
