#include "conditionwidget.h"
#include "ui_conditionwidget.h"

#define DATAMAN dataMan
#define THISCONDITION ((Condition*)&(state->transitions[transitionNumber].conditions[conditionNumber]))

ConditionWidget::ConditionWidget(DataManager* dm, State* state, uint transitionNumber, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConditionWidget)
{
    ui->setupUi(this);

    dataMan = dm;

    connect(ui->button_removeCondition, SIGNAL(clicked()), (Tab_Logic*)parent, SLOT(button_removeCondition_clicked()));

    this->state = state;
    this->transitionNumber = transitionNumber;
    this->conditionNumber = state->transitions[transitionNumber].conditions.size();
    Condition condition;
    condition.conditionSign = Sign( ui->comboBox_sign->currentIndex() );
    condition.leftOperand.additionalNeighbours = ui->spinBox_left->value();
    condition.rightOperand.additionalNeighbours = ui->spinBox_right->value();
    condition.leftOperand.field = ui->comboBox_leftField->currentIndex();
    condition.rightOperand.field = ui->comboBox_rightField->currentIndex();
    condition.leftOperand.relation = Relation( ui->comboBox_leftRelation->currentIndex() );
    condition.rightOperand.relation = Relation( ui->comboBox_rightRelation->currentIndex() );
    condition.leftOperand.matchAll = ui->radioButton_leftAll->isChecked();
    condition.rightOperand.matchAll = ui->radioButton_rightAll->isChecked();
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            condition.leftOperand.neighbours[i][j] = false;
            condition.rightOperand.neighbours[i][j] = false;
        }
    }
    state->transitions[transitionNumber].conditions.push_back(condition);

    ui->comboBox_leftField->addItem(QString("State ID"));
    ui->comboBox_rightField->addItem(QString("State ID"));
    for (uint i = 0; i < DATAMAN->names.size(); ++i) {
        ui->comboBox_leftField->addItem(QString(DATAMAN->names[i].c_str()));
        ui->comboBox_rightField->addItem(QString(DATAMAN->names[i].c_str()));
    }
}

ConditionWidget::ConditionWidget(DataManager* dm, Condition c, State* state, uint transitionNumber, uint conditionNumber, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConditionWidget)
{
    ui->setupUi(this);

    dataMan = dm;

    connect(ui->button_removeCondition, SIGNAL(clicked()), (Tab_Logic*)parent, SLOT(button_removeCondition_clicked()));

    this->state = state;
    this->transitionNumber = transitionNumber;
    this->conditionNumber = conditionNumber;

    //init
    ui->comboBox_leftField->addItem(QString("State ID"));
    ui->comboBox_rightField->addItem(QString("State ID"));
    for (uint i = 0; i < DATAMAN->names.size(); ++i) {
        ui->comboBox_leftField->addItem(QString(DATAMAN->names[i].c_str()));
        ui->comboBox_rightField->addItem(QString(DATAMAN->names[i].c_str()));
    }
    for (int j = 0; j < 3; ++j) { //zakladajac sasiadow 3x3
        for (int k = 0; k < 3; ++k) {
            if (c.leftOperand.neighbours[j][k]) {
                ((QCheckBox*)(ui->gridLayout->itemAtPosition(j, k)->widget()))->setChecked(true);
            }
            if (c.rightOperand.neighbours[j][k]) {
                ((QCheckBox*)(ui->gridLayout_2->itemAtPosition(j, k)->widget()))->setChecked(true);
            }
        }
    }
    ui->comboBox_leftField->setCurrentIndex(c.leftOperand.field);
    ui->comboBox_rightField->setCurrentIndex(c.rightOperand.field);
    ui->comboBox_leftRelation->setCurrentIndex(c.leftOperand.relation);
    ui->comboBox_rightRelation->setCurrentIndex(c.rightOperand.relation);
    ui->comboBox_sign->setCurrentIndex(c.conditionSign);
    if (c.leftOperand.matchAll) {
        ui->radioButton_leftAll->setChecked(true);
    }else{
        ui->radioButton_leftAny->setChecked(true);
    }
    if (c.rightOperand.matchAll) {
        ui->radioButton_rightAll->setChecked(true);
    }else{
        ui->radioButton_rightAny->setChecked(true);
    }
}

ConditionWidget::~ConditionWidget()
{
    delete ui;
}

uint ConditionWidget::getStateNumber()
{
    return state->id;
}

uint ConditionWidget::getTransitionNumber()
{
    return transitionNumber;
}

uint ConditionWidget::getConditionNumber()
{
    return conditionNumber;
}

void ConditionWidget::setLeftNeighbour(QObject* sender, uint row, uint col)
{
    if (((QCheckBox*)sender)->checkState() == Qt::Checked) {
        THISCONDITION->leftOperand.neighbours[row][col] = true;
    }else{
        THISCONDITION->leftOperand.neighbours[row][col] = false;
    }
}

void ConditionWidget::setRightNeighbour(QObject* sender, uint row, uint col)
{
    if (((QCheckBox*)sender)->checkState() == Qt::Checked) {
        THISCONDITION->rightOperand.neighbours[row][col] = true;
    }else{
        THISCONDITION->rightOperand.neighbours[row][col] = false;
    }
}

void ConditionWidget::on_checkBox_clicked()
{
    setLeftNeighbour(sender(), 0, 0);
}

void ConditionWidget::on_checkBox_2_clicked()
{
    setLeftNeighbour(sender(), 0, 1);
}

void ConditionWidget::on_checkBox_3_clicked()
{
    setLeftNeighbour(sender(), 0, 2);
}

void ConditionWidget::on_checkBox_4_clicked()
{
    setLeftNeighbour(sender(), 1, 0);
}

void ConditionWidget::on_checkBox_5_clicked()
{
    setLeftNeighbour(sender(), 1, 1);
}

void ConditionWidget::on_checkBox_6_clicked()
{
    setLeftNeighbour(sender(), 1, 2);
}

void ConditionWidget::on_checkBox_7_clicked()
{
    setLeftNeighbour(sender(), 2, 0);
}

void ConditionWidget::on_checkBox_8_clicked()
{
    setLeftNeighbour(sender(), 2, 1);
}

void ConditionWidget::on_checkBox_9_clicked()
{
    setLeftNeighbour(sender(), 2, 2);
}

void ConditionWidget::on_checkBox_10_clicked()
{
    setRightNeighbour(sender(), 0, 0);
}

void ConditionWidget::on_checkBox_11_clicked()
{
    setRightNeighbour(sender(), 0, 1);
}

void ConditionWidget::on_checkBox_12_clicked()
{
    setRightNeighbour(sender(), 0, 2);
}

void ConditionWidget::on_checkBox_13_clicked()
{
    setRightNeighbour(sender(), 1, 0);
}

void ConditionWidget::on_checkBox_14_clicked()
{
    setRightNeighbour(sender(), 1, 1);
}

void ConditionWidget::on_checkBox_15_clicked()
{
    setRightNeighbour(sender(), 1, 2);
}

void ConditionWidget::on_checkBox_16_clicked()
{
    setRightNeighbour(sender(), 2, 0);
}

void ConditionWidget::on_checkBox_17_clicked()
{
    setRightNeighbour(sender(), 2, 1);
}

void ConditionWidget::on_checkBox_18_clicked()
{
    setRightNeighbour(sender(), 2, 2);
}

void ConditionWidget::on_spinBox_left_valueChanged(int arg1)
{
    THISCONDITION->leftOperand.additionalNeighbours = arg1;
}

void ConditionWidget::on_spinBox_right_valueChanged(int arg1)
{
    THISCONDITION->rightOperand.additionalNeighbours = arg1;
}

void ConditionWidget::on_comboBox_leftField_currentIndexChanged(int index)
{
    THISCONDITION->leftOperand.field = index;
}

void ConditionWidget::on_comboBox_rightField_currentIndexChanged(int index)
{
    THISCONDITION->rightOperand.field = index;
}

void ConditionWidget::on_comboBox_leftRelation_currentIndexChanged(int index)
{
    THISCONDITION->leftOperand.relation = (Relation)index;
}

void ConditionWidget::on_comboBox_rightRelation_currentIndexChanged(int index)
{
    THISCONDITION->rightOperand.relation = (Relation)index;
}

void ConditionWidget::on_comboBox_sign_currentIndexChanged(int index)
{
    THISCONDITION->conditionSign = (Sign)index;
}

void ConditionWidget::on_radioButton_leftAll_clicked()
{
    THISCONDITION->leftOperand.matchAll = ((QRadioButton*)sender())->isChecked();
}

void ConditionWidget::on_radioButton_leftAny_clicked()
{
    THISCONDITION->leftOperand.matchAll = !((QRadioButton*)sender())->isChecked();
}

void ConditionWidget::on_radioButton_rightAll_clicked()
{
    THISCONDITION->rightOperand.matchAll = ((QRadioButton*)sender())->isChecked();
}

void ConditionWidget::on_radioButton_rightAny_clicked()
{
    THISCONDITION->rightOperand.matchAll = !((QRadioButton*)sender())->isChecked();
}
