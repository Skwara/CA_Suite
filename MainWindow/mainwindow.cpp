#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    layout_cells = new QGridLayout();
    layout_cells->setAlignment(Qt::AlignLeft);
    layout_cells->setHorizontalSpacing(0);
    layout_cells->setVerticalSpacing(0);
    ui->scrollArea_cells->setLayout(layout_cells);
    configWindow = new ConfigWindow(this);

    //DO WYWALENIA
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 20; ++j) {
            Cell* c = new Cell(i, j);
            c->setColor(255, 255, 255);
            layout_cells->addWidget(c, i, j);
        }
    }
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
