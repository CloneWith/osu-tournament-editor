//
// Created by clonewith on 25-3-6.
//

#ifndef TAB_H
#define TAB_H
#include <qstring.h>

#include <utility>

/// The base class for all tabs, making it convenient to manage them.
class Tab
{
public:
    QWidget *Content;
    QString FilePath;
    bool Editable;

    Tab(QWidget *content, QString path, bool editable) : Content(content), FilePath(std::move(path)), Editable(editable)
    {
    };
};


#endif //TAB_H
