//
// Created by clonewith on 25-3-2.
//

#ifndef PROJECTABOUTDIALOG_H
#define PROJECTABOUTDIALOG_H

#include <QDialog>


QT_BEGIN_NAMESPACE

namespace Ui
{
    class ProjectAboutDialog;
}

QT_END_NAMESPACE

class ProjectAboutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProjectAboutDialog(QWidget* parent = nullptr);
    ~ProjectAboutDialog() override;

private:
    Ui::ProjectAboutDialog* ui;
};


#endif //PROJECTABOUTDIALOG_H
