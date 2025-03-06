#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFile>
#include <QMainWindow>
#include <QSettings>

#include "Common.h"
#include "Models/EditorTab.h"

QT_BEGIN_NAMESPACE

namespace Ui
{
    class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

    ~MainWindow() override;

    QSettings Settings = QSettings(Common::DATA_NAME, QSettings::IniFormat);

private slots:
    void createNew();
    void help();
    void about();
    void openFile();

    void save(int index, bool askNewPath);
    void saveCurrent();
    void saveAs();
    void saveAll();

    void openProject();
    void showHome();
    void showTranslationGenerator();

    void addTab(Tab *tab, const QIcon &icon, const QString &name);

    void closeCurrent();
    void closeOthers();
    void closeAll();
    void closeTab(int index);

    void updateActionState();

private:
    Ui::MainWindow* ui;
    QList<Tab*> openedTabs;
    QTabWidget* tabWidget = new QTabWidget();

    void bindActions() const;
    void bindShortcuts() const;

    void addEditorTab(const QString &path, const QString &name, LadderInfo *ladder);
};


#endif // MAINWINDOW_H
