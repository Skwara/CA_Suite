#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>

#include "configwindow.h"
#include "cell.h"
#include "engine.h"

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

    void on_startButton_clicked();

    void configWindowClosed(int result);

    void on_spinBox_cellSize_valueChanged(int arg1);

    void on_resetButton_clicked();

private:
    Ui::MainWindow* ui;
    ConfigWindow* configWindow;
    QGridLayout* layout_cells;
    DataManager dataMan;
    Engine engine;
    std::vector< std::vector<Cell*> > cells;

    bool initialized;

    void paintCells(uint rows, uint cols);
    void clearCells();
};

#endif // MAINWINDOW_H
