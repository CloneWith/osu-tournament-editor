#include "MainWindow.h"

#include "./ui_MainWindow.h"
#include "ProjectAboutDialog.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    bindActions();
}

void MainWindow::about()
{
    ProjectAboutDialog aboutDialog;
    aboutDialog.exec();
}

void MainWindow::bindActions() const
{
    connect(ui->actionExit, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(ui->actionAboutProject, &QAction::triggered, qApp, &MainWindow::about);
    connect(ui->actionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void MainWindow::bindShortcuts() const
{
    ui->actionOpen->setShortcut(QKeySequence::Open);
}

MainWindow::~MainWindow()
{
    delete ui;
}
