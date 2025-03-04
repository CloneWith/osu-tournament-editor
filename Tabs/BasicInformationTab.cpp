//
// Created by clonewith on 25-3-3.
//

// You may need to build the project (run Qt uic code generator) to get "ui_BasicInformationTab.h" resolved

#include "BasicInformationTab.h"
#include "ui_BasicInformationTab.h"


BasicInformationTab::BasicInformationTab(QWidget *parent) : QWidget(parent), ui(new Ui::BasicInformationTab)
{
    ui->setupUi(this);
}

BasicInformationTab::~BasicInformationTab()
{
    delete ui;
}
