#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>

#include "configwindow.h"
#include "cell.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_configButton_clicked();

private:
    Ui::MainWindow* ui;
    ConfigWindow* configWindow;
    QGridLayout* layout_cells;

    void paintCells(uint rows, uint cols);
    void clearCells();
};

#endif // MAINWINDOW_H
