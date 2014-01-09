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
    for (uint i = 0; i < rows; ++i) {
        std::vector<Cell*> cellsVec;
        for (uint j = 0; j < cols; ++j) {
            Cell* c = new Cell(i, j);
            cellsVec.push_back(c);
            layout_cells->addWidget(c, i, j);
        }
        cells.push_back(cellsVec);
    }

//    foreach (std::vector<Cell*> vec, cells) {
//        foreach (Cell* c, vec) {
//            c->addNeighbours(cells);
//        }
//    }
    // TODO
    //std::cout << cells.size() << "; " << cells[0].size() << std::endl;
    for (uint i = 1; i < cells.size() - 1; ++i) { // TODO omijam brzegi
        for (uint j = 1; j < cells[0].size() - 1; ++j) {
            //std::cout << i << "; " << j << std::endl;
            cells[i][j]->addNeighbours(cells);
        }
    }
}

void MainWindow::clearCells()
{
    foreach (std::vector<Cell*> vec, cells) {
        foreach (Cell* c, vec) {
            delete c;
            vec.erase(vec.begin());
        }
        cells.erase(cells.begin());
    }
}

void MainWindow::on_startButton_clicked()
{
    if (configWindow->dataManager.statesListInfo.size() > 0) {
        // dodanie data managera, o ile nei zostal juz dodany
        if (dataMan) {
            dataMan = &(configWindow->dataManager);
            engine = Engine(dataMan);
            Cell c;
            c.dataMan = dataMan;
            paintCells(dataMan->boardHeight, dataMan->boardWidth);
        }
        // sprawdzenie, czy wielkosc planszy byla zmieniana
        if (dataMan->boardHeight*dataMan->boardWidth != cells.size() * cells[0].size()) {
            clearCells();
            if (dataMan->statesListInfo.size() > 0) {
                paintCells(dataMan->boardHeight, dataMan->boardWidth);
            }
        }

        engine.start(cells);
    }
}
