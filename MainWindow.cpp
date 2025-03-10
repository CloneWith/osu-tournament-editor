#include "MainWindow.h"

#include "./ui_MainWindow.h"
#include "ProjectAboutDialog.h"

#include <QFileDialog>
#include <QLabel>
#include <QMessageBox>

#include "TranslationGeneratorWindow.h"
#include "Models/LadderInfo.h"
#include "Tabs/WelcomeTab.h"

void logMessageHandler(const QtMsgType type, const QMessageLogContext &context, const QString &message)
{
    const QString typeStr = qFormatLogMessage(type, context, message);
    const qint64 currentTime = QDateTime::currentSecsSinceEpoch();

    QFile file("runtime_" + QString::fromStdString(std::to_string(currentTime)) + ".log");
    file.open(QIODevice::WriteOnly | QIODevice::Append);

    QTextStream textStream(&file);
    textStream << typeStr << "\n";
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow)
{
    // Set up logging
    qSetMessagePattern("[%{type}] %{time yyyy-MM-dd hh:mm:ss}%{if-debug}@%{function}:%{line}%{endif}: %{message}");
    qInstallMessageHandler(logMessageHandler);

    ui->setupUi(this);

    ui->statusbar->addPermanentWidget(versionInfo);

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

void MainWindow::recordToRecent(const QString &fileName)
{
    auto recentList = Settings.value("recent_files").toStringList();

    if (recentList.contains(fileName))
    {
        recentList.swapItemsAt(recentList.indexOf(fileName), 0);
    }
    else
    {
        recentList.insert(0, fileName);
    }

    Settings.setValue("recent_files", recentList);
    emit recentUpdated();
}

void MainWindow::askOpenFile()
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
            openFile(fileName);
        }
    }
}

void MainWindow::openFile(const QString &fileName)
{
    // Look for existing tabs with the same file
    if (std::any_of(openedTabs.begin(), openedTabs.end(), [fileName](const Tab *tab)
    {
        return tab->FilePath == fileName;
    }))
        return;

    if (QFile file(fileName); file.open(QFile::ReadOnly))
    {
        QJsonDocument jsonDocument = QJsonDocument::fromJson(file.readAll());
        QJsonObject jsonObject = jsonDocument.object();

        auto *testLadder = new LadderInfo();
        testLadder->fromJson(jsonObject);

        const QString tabName = QString::fromUtf8(file.filesystemFileName().filename().stem().string());
        testLadder->Name = tabName;
        addEditorTab(fileName, tabName, testLadder);
        recordToRecent(fileName);
    } else
    {
        QMessageBox::critical(this, tr("Error"), file.errorString());
    }
}

void MainWindow::save(const int index, const bool askNewPath = false)
{
    Tab *targetTab = openedTabs[index];
    QString newPath = targetTab->FilePath;

    if (!targetTab->Editable) return;

    if (askNewPath || targetTab->FilePath.isEmpty())
    {
        QFileDialog fileDialog(this);

        fileDialog.setWindowTitle(tr("Select save location"));
        fileDialog.setAcceptMode(QFileDialog::AcceptSave);
        fileDialog.setFileMode(QFileDialog::AnyFile);
        fileDialog.setNameFilter(tr("Tournament File (*.json)"));

        if (fileDialog.exec())
        {
            if (fileDialog.selectedFiles().count() == 0) return;
            newPath = fileDialog.selectedFiles()[0];
        }
    }

    if (newPath.isEmpty()) return;

    QFile file(newPath);
    file.open(QFile::WriteOnly);
    const auto ladder = targetTab->GetLadderInfo();
    const auto doc = QJsonDocument(ladder->toJson());
    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();

    // Update the file path after writing changes.
    recordToRecent(newPath);
    targetTab->FilePath = newPath;
    tabWidget->setTabText(index, QString::fromStdString(file.filesystemFileName().filename().stem().string()));
    ui->statusbar->showMessage(tr("File successfully saved"), 3000);
}

void MainWindow::saveCurrent()
{
    save(tabWidget->currentIndex(), false);
}

void MainWindow::saveAs()
{
    save(tabWidget->currentIndex(), true);
}

void MainWindow::saveAll()
{
    for (int index = 0; index < tabWidget->count(); index++)
    {
        save(index, false);
    }
}

void MainWindow::addEditorTab(const QString &path, const QString &name, LadderInfo *ladder)
{
    auto *tab = new EditorTab(nullptr, path, ladder);
    addTab(tab, QIcon::fromTheme(QIcon::ThemeIcon::Computer), name);

    // Manually update the action state since we don't have a signal for newly inserted tabs.
    updateActionState();
}

/// <summary>
/// Shows the "Get Started" welcome tab.
/// </summary>
void MainWindow::showHome()
{
    auto *homeTab = new WelcomeTab();
    connect(homeTab, SIGNAL(signalNew()), this, SLOT(createNew()));
    connect(homeTab, SIGNAL(signalOpen()), this, SLOT(askOpenFile()));
    connect(homeTab, SIGNAL(signalOpenProject()), this, SLOT(openProject()));
    connect(homeTab, SIGNAL(signalHelp()), this, SLOT(help()));
    connect(homeTab, SIGNAL(signalOpenRequest(QString)), this, SLOT(openFile(QString)));
    connect(this, SIGNAL(recentUpdated()), homeTab, SLOT(updateRecent()));

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
        ui->statusbar->showMessage(tr("This configuration has already opened."), 3000);
        qDebug() << "The tab " << tab->FilePath << " was already opened, skipping.";
        return;
    }

    openedTabs.append(tab);
    tabWidget->addTab(tab->Content, icon, name);
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

/// Closes the currently selected tab in the tab widget.
void MainWindow::closeCurrent()
{
    closeTab(tabWidget->currentIndex());
}

void MainWindow::closeOthers()
{
    for (int i = 0; i < tabWidget->currentIndex(); i++)
        closeTab(0);

    while (tabWidget->count() > 1)
        closeTab(1);
}

void MainWindow::closeAll()
{
    // Close actions affect the tab list, so we should always remove a tab with a certain index.
    while (tabWidget->count() > 0)
        closeTab(0);
}


void MainWindow::updateActionState()
{
    const bool hasEditorTabs = std::any_of(openedTabs.begin(), openedTabs.end(), [](const Tab *tab)
    {
        return tab->Editable;
    });
    const bool hasAnyTabs = tabWidget->count() > 0;
    const bool isEditorTab = hasAnyTabs && openedTabs[tabWidget->currentIndex()]->Editable;

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
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(askOpenFile()));
    connect(ui->actionOpenProject, SIGNAL(triggered()), this, SLOT(openProject()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveCurrent()));
    connect(ui->actionSaveAs, SIGNAL(triggered()), this, SLOT(saveAs()));
    connect(ui->actionSaveAll, SIGNAL(triggered()), this, SLOT(saveAll()));
    connect(ui->actionClose, SIGNAL(triggered()), this, SLOT(closeCurrent()));
    connect(ui->actionCloseOthers, SIGNAL(triggered()), this, SLOT(closeOthers()));
    connect(ui->actionCloseAll, SIGNAL(triggered()), this, SLOT(closeAll()));
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
