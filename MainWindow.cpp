#include "MainWindow.h"
#include "./ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    connect(ui->actionExit, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void MainWindow::bindActions() const {
    connect(ui->actionExit, SIGNAL(triggered()), qApp, SLOT(quit()));
}

MainWindow::~MainWindow() {
    delete ui;
}
