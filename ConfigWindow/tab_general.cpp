#include "tab_general.h"
#include "ui_tab_general.h"

Tab_General::Tab_General(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tab_General)
{
    ui->setupUi(this);
}

Tab_General::~Tab_General()
{
    delete ui;
}
