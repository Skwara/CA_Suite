#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    configWindow = new ConfigWindow(this);
    ui->setupUi(this);
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
