#include "MainWindow.h"

#include "./ui_MainWindow.h"
#include "ProjectAboutDialog.h"

#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    bindActions();
    bindShortcuts();
}

void MainWindow::about()
{
    ProjectAboutDialog aboutDialog(this);
    aboutDialog.exec();
}

void MainWindow::open()
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

    // TODO: Replace with tab update and JSON deserialization
    if (!files.isEmpty())
    {
        QString dialogText = tr("Selected files:") + "\n";

        for (const auto& str : files)
        {
            dialogText += str + ";\n";
        }

        QMessageBox::information(this, tr("Prompt"), dialogText);
    }
}

void MainWindow::bindActions() const
{
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::open);
    connect(ui->actionAboutProject, &QAction::triggered, this, &MainWindow::about);
    connect(ui->actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(ui->actionExit, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void MainWindow::bindShortcuts() const
{
    ui->actionNew->setShortcut(QKeySequence::New);
    ui->actionOpen->setShortcut(QKeySequence::Open);
    ui->actionSave->setShortcut(QKeySequence::Save);
    ui->actionSaveAs->setShortcut(QKeySequence::SaveAs);
    ui->actionClose->setShortcut(QKeySequence::Close);
    ui->actionExit->setShortcut(QKeySequence::Quit);
}

MainWindow::~MainWindow()
{
    delete ui;
}
