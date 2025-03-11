//
// Created by clonewith on 25-3-2.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ProjectAboutDialog.h" resolved

#include "ProjectAboutDialog.h"

#include <QDesktopServices>

#include "Common.h"
#include "ui_ProjectAboutDialog.h"


ProjectAboutDialog::ProjectAboutDialog(QWidget* parent) :
    QDialog(parent), ui(new Ui::ProjectAboutDialog)
{
    ui->setupUi(this);

    setFixedSize(400, 250);
    connect(ui->repoButton, SIGNAL(clicked()), this, SLOT(openRepo()));
}

void ProjectAboutDialog::openRepo()
{
    QDesktopServices::openUrl(QUrl(Common::PROJECT_LINK));
}

ProjectAboutDialog::~ProjectAboutDialog()
{
    delete ui;
}
