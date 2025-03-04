//
// Created by clonewith on 25-3-2.
//

// You may need to build the project (run Qt uic code generator) to get "ui_TranslationGeneratorWindow.h" resolved

#include "TranslationGeneratorWindow.h"
#include "ui_TranslationGeneratorWindow.h"


TranslationGeneratorWindow::TranslationGeneratorWindow(QWidget *parent) :
    QWidget(parent), ui(new Ui::TranslationGeneratorWindow) {
    ui->setupUi(this);
}

TranslationGeneratorWindow::~TranslationGeneratorWindow() {
    delete ui;
}
