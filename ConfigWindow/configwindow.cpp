#include "configwindow.h"
#include "ui_configwindow.h"

ConfigWindow::ConfigWindow(QWidget *parent) :
    QDialog(parent),
    dataManager(ui),
    ui(new Ui::ConfigWindow)
{
    ui->setupUi(this);
    tab_states = new Tab_States(&dataManager);
    tab_logic = new Tab_Logic(&dataManager);
    ui->statesTab->setLayout(tab_states->layout());
    ui->logicTab->setLayout(tab_logic->layout());
}

ConfigWindow::~ConfigWindow()
{
    delete ui;
}

void ConfigWindow::resizeEvent(QResizeEvent* event) {
    tab_states->windowResized();
}

void ConfigWindow::on_configTabs_currentChanged(int index)
{
    switch (index) {
    case 2:
        tab_logic->pageActivated();
        break;
    default:
        break;
    }
}
