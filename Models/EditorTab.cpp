//
// Created by clonewith on 25-3-3.
//

#include "EditorTab.h"

EditorTab::EditorTab() = default;

EditorTab::EditorTab(QFile *file, const bool isNewDocument)
{
    this->File = file;

    // For newly created tabs, mark as modified for saving later.
    this->Edited = isNewDocument;
}

EditorTab::~EditorTab()
{
    delete this->File;
}

