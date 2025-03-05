//
// Created by clonewith on 25-3-3.
//

#include "./ui_EditorTab.h"
#include "EditorTab.h"

#include "Rulesets.h"

EditorTab::EditorTab(QWidget *parent, const QString &path, LadderInfo *ladder)
    : QWidget(parent), ui(new Ui::EditorTab)
{
    ui->setupUi(this);

    // For newly created tabs, mark as modified for saving later.
    this->Edited = ladder == nullptr;
    this->FilePath = path;
    this->Ladder = ladder == nullptr ? new LadderInfo() : ladder;

    basicInformationTab = new BasicInformationTab(ladder);
    teamEditorTab = new TeamEditorTab(ladder);
    roundEditorTab = new RoundEditorTab(ladder);

    ui->innerTabWidget->addTab(basicInformationTab,
                               QIcon::fromTheme(QIcon::ThemeIcon::HelpAbout), tr("Tournament Information"));
    ui->innerTabWidget->addTab(teamEditorTab,
                               QIcon::fromTheme(QIcon::ThemeIcon::UserAvailable), tr("Teams"));
    ui->innerTabWidget->addTab(roundEditorTab,
                               QIcon::fromTheme(QIcon::ThemeIcon::MailAttachment), tr("Rounds"));
}

EditorTab::~EditorTab()
{
    delete this->Ladder;
    delete this->basicInformationTab;
    delete this->teamEditorTab;
    delete this->roundEditorTab;
    delete ui;
}
