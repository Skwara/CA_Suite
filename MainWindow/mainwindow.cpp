#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    layout_cells = new QGridLayout();
    layout_cells->setAlignment(Qt::AlignLeft);
    layout_cells->setAlignment(Qt::AlignTop);
    layout_cells->setHorizontalSpacing(0);
    layout_cells->setVerticalSpacing(0);
    layout_cells->setMargin(1);
    ui->scrollArea_cells->widget()->setLayout(layout_cells);
    configWindow = new ConfigWindow(this);

    paintCells(40, 40);
}

MainWindow::~MainWindow()
{
    delete configWindow;
    delete ui;
}

void MainWindow::on_configButton_clicked()
{
    configWindow->show();
}

void MainWindow::paintCells(uint rows, uint cols)
{
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            Cell* c = new Cell(i, j);
            c->setColor(255, 255, 255);
            layout_cells->addWidget(c, i, j);
        }
    }
}

void MainWindow::clearCells()
{

}
