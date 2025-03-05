//
// Created by clonewith on 25-3-3.
//

#ifndef EDITORTAB_H
#define EDITORTAB_H
#include <QFile>
#include <QTabWidget>
#include <QWidget>

#include "LadderInfo.h"
#include "../Tabs/BasicInformationTab.h"
#include "../Tabs/RoundEditorTab.h"
#include "../Tabs/TeamEditorTab.h"

QT_BEGIN_NAMESPACE

namespace Ui
{
    class EditorTab;
}

QT_END_NAMESPACE

/**
 * Represents a tab in the editor.
 */
class EditorTab : public QWidget
{
    Q_OBJECT

public:
    QString FilePath;
    LadderInfo *Ladder;

    bool Edited = false;

    explicit EditorTab(QWidget *parent = nullptr, const QString &path = "", LadderInfo *ladder = nullptr);

    ~EditorTab() override;

private:
    Ui::EditorTab *ui;

    BasicInformationTab *basicInformationTab;
    TeamEditorTab *teamEditorTab;
    RoundEditorTab *roundEditorTab;
};


#endif //EDITORTAB_H
