//
// Created by clonewith on 25-3-2.
//

#ifndef TRANSLATIONGENERATORWINDOW_H
#define TRANSLATIONGENERATORWINDOW_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class TranslationGeneratorWindow; }
QT_END_NAMESPACE

class TranslationGeneratorWindow : public QWidget {
Q_OBJECT

public:
    explicit TranslationGeneratorWindow(QWidget *parent = nullptr);
    ~TranslationGeneratorWindow() override;

private:
    Ui::TranslationGeneratorWindow *ui;
};


#endif //TRANSLATIONGENERATORWINDOW_H
