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
    tabWidget->setMovable(true);
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
    addEditorTab(tr("New Tournament"), new LadderInfo);
}

void MainWindow::openProject()
{
    QFileDialog fileDialog(this);
    QString dir;

    fileDialog.setWindowTitle(tr("Select a tournament directory"));
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setFileMode(QFileDialog::Directory);
    fileDialog.setNameFilter(tr("Tournament Directory"));

    if (fileDialog.exec())
    {
        dir = fileDialog.selectedFiles()[0];
    }

    // TODO: Tab update and JSON deserialization
}

void MainWindow::openFile()
{
    QFileDialog fileDialog(this);
    QStringList files;

    fileDialog.setWindowTitle(tr("Select a tournament bracket file"));
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setFileMode(QFileDialog::ExistingFiles);
    fileDialog.setNameFilter(tr("Tournament Bracket File (*.json)"));

    // exec() would wait until user action finished.
    if (fileDialog.exec())
    {
        files = fileDialog.selectedFiles();

        for (const auto &fileName: files)
        {
            // Look for existing tabs with the same file
            if (std::any_of(openedTabs.begin(), openedTabs.end(), [fileName](EditorTab *tab)
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
                addEditorTab(tabName, testLadder);
            } else
            {
                QMessageBox::critical(this, tr("Error"), file.errorString());
            }
        }
    }
}

void MainWindow::addEditorTab(const QString &name, LadderInfo *ladder)
{
    auto *tab = new EditorTab(nullptr, name, ladder);
    openedTabs.append(tab);
    tabWidget->addTab(tab, name);
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

    tabWidget->addTab(homeTab, QIcon::fromTheme(QIcon::ThemeIcon::GoHome), "Welcome");
}

void MainWindow::showTranslationGenerator()
{
    auto *translationWindow = new TranslationGeneratorWindow();
    translationWindow->show();
}

/// <summary>
/// Closes the currently selected tab in the tab widget.
/// </summary>
void MainWindow::closeTab()
{
    closeTab(tabWidget->currentIndex());
}

/// <summary>
/// Closes the tab with specific index in the tab widget.
/// </summary>
/// <param name="index">the index of the tab</param>
void MainWindow::closeTab(int index)
{
    // Get widget pointer first -> Then remove tab (otherwise we cannot access the pointer)
    auto *tab = tabWidget->widget(index);

    tabWidget->removeTab(index);
    delete tab;
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
