#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFile>
#include <QLabel>
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

    QSettings Settings = QSettings(Common::CONFIG_NAME, QSettings::IniFormat);

private slots:
    void createNew();
    void help();
    void about();
    void askOpenFile();

    void save(int index, bool askNewPath);
    void saveCurrent();
    void saveAs();
    void saveAll();

    void openProject();

    void showHome();
    void showTranslationGenerator();

    void addTab(Tab *tab, const QIcon &icon, const QString &name);
    void openFile(const QString &fileName);

    void closeCurrent();
    void closeOthers();
    void closeAll();
    void closeTab(int index);

    void updateActionState();

private:
    Ui::MainWindow* ui;
    QList<Tab*> openedTabs;
    QLabel* versionInfo = new QLabel(Common::PROJECT_NAME + " v" + Common::VERSION);
    QTabWidget* tabWidget = new QTabWidget();

    void bindActions() const;
    void bindShortcuts() const;

    void recordToRecent(const QString &fileName);
    void addEditorTab(const QString &path, const QString &name, LadderInfo *ladder);

signals:
    void recentUpdated();
};


#endif // MAINWINDOW_H
