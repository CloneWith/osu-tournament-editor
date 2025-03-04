#include "MainWindow.h"

#include "./ui_MainWindow.h"
#include "ProjectAboutDialog.h"

#include <QFileDialog>

#include "Tabs/WelcomeTab.h"

MainWindow::MainWindow(QWidget* parent)
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

    if (Settings.value("show_startup_home_tab").toBool())
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
    }

    // TODO: Tab update and JSON deserialization
}

void MainWindow::showHome()
{
    auto* homeTab = new WelcomeTab();
    connect(homeTab, SIGNAL(signalNew()), this, SLOT(createNew()));
    connect(homeTab, SIGNAL(signalOpen()), this, SLOT(openFile()));
    connect(homeTab, SIGNAL(signalOpenProject()), this, SLOT(openProject()));
    connect(homeTab, SIGNAL(signalHelp()), this, SLOT(help()));

    connect(tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));
    tabWidget->addTab(homeTab, QIcon::fromTheme(QIcon::ThemeIcon::GoHome), "Welcome");
}

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
    connect(ui->actionHelp, SIGNAL(triggered()), this, SLOT(help()));
    connect(ui->actionAboutProject, SIGNAL(triggered()), this, SLOT(about()));
    connect(ui->actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(ui->actionExit, SIGNAL(triggered()), qApp, SLOT(quit()));
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
