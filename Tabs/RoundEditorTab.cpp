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
    this->model = new TournamentRoundModel(ladderInfo->Rounds);

    ui->listRounds->setModel(model);

    connect(ui->inputRoundName, SIGNAL(textChanged(QString)), this, SLOT(updateName()));
    connect(ui->listRounds->selectionModel(), &QItemSelectionModel::currentChanged, this, &RoundEditorTab::updateContent);
}

void RoundEditorTab::updateName()
{
    if (ui->inputRoundName->text().trimmed().isEmpty()) return;

    QModelIndex index = ui->listRounds->currentIndex();
    model->setData(index, ui->inputRoundName->text(), Qt::DisplayRole);
}

void RoundEditorTab::updateContent()
{
    QModelIndex index = ui->listRounds->currentIndex();
    currentRound = model->data(index, Qt::EditRole).value<TournamentRound>();

    ui->inputRoundName->setText(currentRound.Name);
    ui->inputRoundDescription->setText(currentRound.Description);
    ui->inputDate->setDateTime(currentRound.StartDate);
    ui->inputBestOf->setValue(currentRound.BestOf);
    ui->inputBanCount->setValue(currentRound.BanCount);
    ui->checkBoxUseBoard->setChecked(currentRound.UseBoard);

    updateRightList();
}

void RoundEditorTab::writeContent()
{
    QModelIndex index = ui->listRounds->currentIndex();
    model->setData(index, QVariant::fromValue(currentRound), Qt::EditRole);
}

void RoundEditorTab::updateRightList()
{
    // Causing SIGSEGV, do we need to delete the object manually?
    // if (mapModel != nullptr) delete mapModel;
    mapModel = new RoundBeatmapModel(currentRound.Beatmaps);
    refereeModel = new TournamentUserModel(currentRound.Referees);
    ui->listBeatmaps->setModel(mapModel);
    ui->listReferees->setModel(refereeModel);
}

RoundEditorTab::~RoundEditorTab()
{
    delete ui;
}
