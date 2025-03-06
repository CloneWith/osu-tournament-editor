//
// Created by clonewith on 25-3-6.
//

#ifndef TAB_H
#define TAB_H
#include <qstring.h>

#include <utility>
#include "LadderInfo.h"

/// The base class for all tabs, making it convenient to manage them.
class Tab
{
protected:
    ~Tab() = default;

public:
    QWidget *Content;
    QString FilePath;
    bool Editable;

    Tab(QWidget *content, QString path, const bool editable)
        : Content(content), FilePath(std::move(path)), Editable(editable)
    {
    }

    virtual LadderInfo* GetLadderInfo()
    {
        return nullptr;
    }
};


#endif //TAB_H
