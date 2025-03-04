#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFile>
#include <QMainWindow>
#include <QSettings>

#include "Common.h"

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
    void openProject();
    void showHome();

    static void showTranslationGenerator();

    void closeTab();
    void closeTab(int index);

private:
    Ui::MainWindow* ui;
    QList<QFile> openedFiles;
    QTabWidget* tabWidget = new QTabWidget();

    void bindActions() const;
    void bindShortcuts() const;
};


#endif // MAINWINDOW_H
