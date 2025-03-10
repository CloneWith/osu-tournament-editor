//
// Created by clonewith on 25-3-3.
//

// You may need to build the project (run Qt uic code generator) to get "ui_WelcomeTab.h" resolved

#include "WelcomeTab.h"
#include "ui_WelcomeTab.h"


WelcomeTab::WelcomeTab(QWidget *parent) : QWidget(parent), ui(new Ui::WelcomeTab), Tab(this, "", false)
{
    ui->setupUi(this);

    connect(ui->commandButton1, &QCommandLinkButton::clicked, this, &WelcomeTab::callNew);
    connect(ui->commandButton2, &QCommandLinkButton::clicked, this, &WelcomeTab::callOpenProject);
    connect(ui->commandButton3, &QCommandLinkButton::clicked, this, &WelcomeTab::callOpen);
    connect(ui->commandButton4, &QCommandLinkButton::clicked, this, &WelcomeTab::callHelp);

    updateRecent();
    connect(ui->recentListWidget, SIGNAL(itemActivated(QListWidgetItem*)), this, SLOT(requestOpen(QListWidgetItem*)));

    connect(ui->dismissCheckBox, SIGNAL(toggled(bool)), this, SLOT(changeHomeStartupDisplay(bool)));
}

WelcomeTab::~WelcomeTab()
{
    delete ui;
}

void WelcomeTab::updateRecent()
{
    const auto recentFiles = Settings.value("recent_files").toStringList();
    ui->recentListWidget->clear();
    ui->recentListWidget->addItems(recentFiles);
}

void WelcomeTab::clearRecent()
{
    ui->recentListWidget->clear();
    Settings.setValue("recent_files", {});
}

void WelcomeTab::changeHomeStartupDisplay(bool hideTab)
{
    Settings.setValue("hide_startup_home_tab", hideTab);
}

void WelcomeTab::requestOpen(QListWidgetItem *item)
{
    emit signalOpenRequest(item->text());
}

void WelcomeTab::callNew()
{
    emit signalNew();
}

void WelcomeTab::callOpen()
{
    emit signalOpen();
}

void WelcomeTab::callOpenProject()
{
    emit signalOpenProject();
}

void WelcomeTab::callHelp()
{
    emit signalHelp();
}
