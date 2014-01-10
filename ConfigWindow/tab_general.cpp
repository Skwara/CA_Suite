#include "tab_general.h"
#include "ui_tab_general.h"

Tab_General::Tab_General(DataManager* dm, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tab_General)
{
    ui->setupUi(this);
    dataMan = dm;

    dataMan->neighbourhood = Moore;
    dataMan->cellSize = ui->spinBox_cellSize->value();
    dataMan->boardHeight = 10;
    dataMan->boardWidth = 10;

    ui->spinBox_boardHeight->setValue(10);
    ui->spinBox_boardWidth->setValue(10);
    ui->radioButton_Moore->setChecked(true);
}

Tab_General::~Tab_General()
{
    delete ui;
}

void Tab_General::on_spinBox_boardWidth_valueChanged(int arg1)
{
    dataMan->boardWidth = arg1;
}

void Tab_General::on_spinBox_boardHeight_valueChanged(int arg1)
{
    dataMan->boardHeight = arg1;
}

void Tab_General::on_radioButton_Neumann_pressed()
{
    dataMan->neighbourhood = Neumann;
}

void Tab_General::on_radioButton_Moore_pressed()
{
    dataMan->neighbourhood = Moore;
}

void Tab_General::on_pushButton_save_clicked()
{
    dataMan->saveData();
}

void Tab_General::on_pushButton_load_clicked()
{
    dataMan->loadData();
}

void Tab_General::on_spinBox_cellSize_valueChanged(int arg1)
{
    dataMan->cellSize = arg1;
}
