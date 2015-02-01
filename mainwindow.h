#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "BuddyAllocater.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    double totalMemory;
    BuddyAllocater* buddy_;
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_allocateBtt_clicked();

    void on_releaseBtt_clicked();

    void on_setBtt_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
