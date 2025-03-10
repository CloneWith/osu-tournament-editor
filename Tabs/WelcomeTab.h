//
// Created by clonewith on 25-3-3.
//

#ifndef WELCOMETAB_H
#define WELCOMETAB_H

#include <qlistwidget.h>
#include <QSettings>
#include <QWidget>

#include "../Common.h"
#include "../Models/Tab.h"

QT_BEGIN_NAMESPACE

namespace Ui
{
    class WelcomeTab;
}

QT_END_NAMESPACE

class WelcomeTab final : public QWidget, public Tab
{
    Q_OBJECT

public:
    explicit WelcomeTab(QWidget *parent = nullptr);

    ~WelcomeTab() override;

    QSettings Settings = QSettings(Common::CONFIG_NAME, QSettings::IniFormat);

private slots:
    void callNew();
    void callOpen();
    void callOpenProject();
    void callHelp();
    void updateRecent();
    void clearRecent();
    void changeHomeStartupDisplay(bool hideTab);

    void requestOpen(QListWidgetItem *item);

private:
    Ui::WelcomeTab *ui;

signals:
    void signalNew();
    void signalOpen();
    void signalOpenProject();
    void signalHelp();
    void signalOpenRequest(const QString &fileName);
};


#endif //WELCOMETAB_H
