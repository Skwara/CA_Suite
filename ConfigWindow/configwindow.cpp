#include "configwindow.h"
#include "ui_configwindow.h"
#include "tab_states.h"
#include "tab_logic.h"

#include <iostream>

#include <QPalette>

std::vector<State> ConfigWindow::statesListInfo;

ConfigWindow::ConfigWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigWindow)
{
    ui->setupUi(this);
    ui->statesTab->setLayout((new Tab_States())->layout());
    ui->logicTab->setLayout((new Tab_Logic())->layout());
}

ConfigWindow::~ConfigWindow()
{
    delete ui;
}
