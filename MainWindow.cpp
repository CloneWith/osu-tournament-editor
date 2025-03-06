#include "MainWindow.h"

#include "./ui_MainWindow.h"
#include "ProjectAboutDialog.h"

#include <QFileDialog>
#include <QMessageBox>

#include "TranslationGeneratorWindow.h"
#include "Models/LadderInfo.h"
#include "Tabs/WelcomeTab.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    bindActions();
    bindShortcuts();

    // Override the central widget layout
    tabWidget->setObjectName("mainTabWidget");
    tabWidget->setUsesScrollButtons(true);
    tabWidget->setTabsClosable(true);
    setCentralWidget(tabWidget);

    if (!Settings.value("hide_startup_home_tab").toBool())
        showHome();
}

void MainWindow::help()
{
}

void MainWindow::about()
{
    ProjectAboutDialog aboutDialog(this);
    aboutDialog.exec();
}

void MainWindow::createNew()
{
    addEditorTab("", tr("New Tournament"), new LadderInfo);
}

void MainWindow::openProject()
{
    QMessageBox::information(this, tr("Information"), tr("This feature is working in progress."));
}

void MainWindow::openFile()
{
    QFileDialog fileDialog(this);

    fileDialog.setWindowTitle(tr("Select a tournament bracket file"));
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setFileMode(QFileDialog::ExistingFiles);
    fileDialog.setNameFilter(tr("Tournament Bracket File (*.json)"));

    // exec() would wait until user action finished.
    if (fileDialog.exec())
    {
        QStringList files = fileDialog.selectedFiles();

        for (const auto &fileName: files)
        {
            // Look for existing tabs with the same file
            if (std::any_of(openedTabs.begin(), openedTabs.end(), [fileName](const Tab *tab)
            {
                return tab->FilePath == fileName;
            }))
                continue;

            QFile file(fileName);
            if (file.open(QFile::ReadOnly))
            {
                QJsonDocument jsonDocument = QJsonDocument::fromJson(file.readAll());
                QJsonObject jsonObject = jsonDocument.object();

                auto *testLadder = new LadderInfo();
                testLadder->fromJson(jsonObject);

                QString tabName = QString::fromUtf8(file.filesystemFileName().filename().stem().string());
                testLadder->Name = tabName;
                addEditorTab(fileName, tabName, testLadder);
            } else
            {
                QMessageBox::critical(this, tr("Error"), file.errorString());
            }
        }
    }
}

void MainWindow::addEditorTab(const QString &path, const QString &name, LadderInfo *ladder)
{
    auto *tab = new EditorTab(nullptr, path, ladder);
    addTab(tab, QIcon::fromTheme(QIcon::ThemeIcon::Computer), name);
}

/// <summary>
/// Shows the "Get Started" welcome tab.
/// </summary>
void MainWindow::showHome()
{
    auto *homeTab = new WelcomeTab();
    connect(homeTab, SIGNAL(signalNew()), this, SLOT(createNew()));
    connect(homeTab, SIGNAL(signalOpen()), this, SLOT(openFile()));
    connect(homeTab, SIGNAL(signalOpenProject()), this, SLOT(openProject()));
    connect(homeTab, SIGNAL(signalHelp()), this, SLOT(help()));

    addTab(homeTab, QIcon::fromTheme(QIcon::ThemeIcon::GoHome), "Welcome");
}

void MainWindow::showTranslationGenerator()
{
    QMessageBox::information(this, tr("Information"),
        tr("This feature is going to be implemented in the future."));
    auto *translationWindow = new TranslationGeneratorWindow();
    translationWindow->show();
}

void MainWindow::addTab(Tab *tab, const QIcon &icon, const QString &name)
{
    if (openedTabs.contains(tab))
    {
        qDebug() << "The tab " << tab->FilePath << " was already opened, skipping.";
        return;
    }

    openedTabs.append(tab);
    tabWidget->addTab(tab->Content, icon, name);
}

/// Closes the currently selected tab in the tab widget.
void MainWindow::closeTab()
{
    closeTab(tabWidget->currentIndex());
}

/// Closes the tab with specific index in the tab widget.
/// @param index the index of the tab
void MainWindow::closeTab(const int index)
{
    // Get widget pointer first -> Then remove tab (otherwise we cannot access the pointer)
    const auto *tab = tabWidget->widget(index);

    tabWidget->removeTab(index);
    openedTabs.removeAt(index);
    delete tab;
}

void MainWindow::updateActionState()
{
    bool hasEditorTabs = openedTabs.count() > 0;
    bool hasAnyTabs = tabWidget->count() > 0;
    bool isEditorTab = hasAnyTabs && openedTabs[tabWidget->currentIndex()]->Editable;
    ui->actionCloseOthers->setEnabled(tabWidget->count() > 1);
    ui->actionClose->setEnabled(hasAnyTabs);
    ui->actionCloseAll->setEnabled(hasAnyTabs);

    ui->actionSave->setEnabled(isEditorTab);
    ui->actionSaveAs->setEnabled(isEditorTab);
    ui->actionSaveAll->setEnabled(hasEditorTabs);
}

void MainWindow::bindActions() const
{
    connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(createNew()));
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(ui->actionOpenProject, SIGNAL(triggered()), this, SLOT(openProject()));
    connect(ui->actionClose, SIGNAL(triggered()), this, SLOT(closeTab()));
    connect(ui->actionHome, SIGNAL(triggered()), this, SLOT(showHome()));
    connect(ui->actionTranslationGenerator, SIGNAL(triggered()), this, SLOT(showTranslationGenerator()));
    connect(ui->actionHelp, SIGNAL(triggered()), this, SLOT(help()));
    connect(ui->actionAboutProject, SIGNAL(triggered()), this, SLOT(about()));
    connect(ui->actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(ui->actionExit, SIGNAL(triggered()), qApp, SLOT(quit()));

    connect(tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
    connect(tabWidget, SIGNAL(currentChanged(int)), this, SLOT(updateActionState()));
}

void MainWindow::bindShortcuts() const
{
    ui->actionNew->setShortcut(QKeySequence::New);
    ui->actionOpen->setShortcut(QKeySequence::Open);
    ui->actionHelp->setShortcut(QKeySequence::HelpContents);
    ui->actionSave->setShortcut(QKeySequence::Save);
    ui->actionSaveAs->setShortcut(QKeySequence::SaveAs);
    ui->actionClose->setShortcut(QKeySequence::Close);
    ui->actionExit->setShortcut(QKeySequence::Quit);
}

MainWindow::~MainWindow()
{
    delete tabWidget;
    delete ui;
}
