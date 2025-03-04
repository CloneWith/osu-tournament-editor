//
// Created by clonewith on 25-3-3.
//

#ifndef BASICINFORMATIONTAB_H
#define BASICINFORMATIONTAB_H

#include <QWidget>


QT_BEGIN_NAMESPACE

namespace Ui
{
    class BasicInformationTab;
}

QT_END_NAMESPACE

class BasicInformationTab : public QWidget
{
    Q_OBJECT

public:
    explicit BasicInformationTab(QWidget *parent = nullptr);

    ~BasicInformationTab() override;

private:
    Ui::BasicInformationTab *ui;
};


#endif //BASICINFORMATIONTAB_H
