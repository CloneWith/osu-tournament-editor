//
// Created by clonewith on 25-3-3.
//

#ifndef EDITORTAB_H
#define EDITORTAB_H
#include <QFile>

/**
 * Represents a tab in the editor.
 */
class EditorTab
{
public:
    QFile *File = nullptr;

    bool Edited = false;

    EditorTab();
    explicit EditorTab(QFile *file, bool isNewDocument);

    ~EditorTab();
};


#endif //EDITORTAB_H
