//
// Created by clonewith on 25-3-2.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ProjectAboutDialog.h" resolved

#include "ProjectAboutDialog.h"
#include "ui_ProjectAboutDialog.h"


ProjectAboutDialog::ProjectAboutDialog(QWidget* parent) :
    QDialog(parent), ui(new Ui::ProjectAboutDialog)
{
    ui->setupUi(this);
}

ProjectAboutDialog::~ProjectAboutDialog()
{
    delete ui;
}
