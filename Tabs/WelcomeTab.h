//
// Created by clonewith on 25-3-3.
//

#ifndef WELCOMETAB_H
#define WELCOMETAB_H

#include <QSettings>
#include <QWidget>

#include "../Common.h"

QT_BEGIN_NAMESPACE

namespace Ui
{
    class WelcomeTab;
}

QT_END_NAMESPACE

class WelcomeTab : public QWidget
{
    Q_OBJECT

public:
    explicit WelcomeTab(QWidget *parent = nullptr);

    ~WelcomeTab() override;

    QSettings Settings = QSettings(Common::DATA_NAME, QSettings::IniFormat);

private slots:
    void callNew();
    void callOpen();
    void callOpenProject();
    void callHelp();
    void changeHomeStartupDisplay(bool hideTab);

private:
    Ui::WelcomeTab *ui;

signals:
    void signalNew();
    void signalOpen();
    void signalOpenProject();
    void signalHelp();
};


#endif //WELCOMETAB_H
