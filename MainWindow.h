#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private slots:
    void createNew();
    void help();
    void about();
    void open();
    void openProject();
    void showHome();

    static void showTranslationGenerator();

    void closeTab(int index);

private:
    Ui::MainWindow* ui;
    QTabWidget* tabWidget = new QTabWidget();

    void bindActions() const;
    void bindShortcuts() const;
};


#endif // MAINWINDOW_H
