#include "tab_logic.h"
#include "ui_tab_logic.h"

#include <iostream>

#define DATAMAN dataMan

Tab_Logic::Tab_Logic(DataManager* dm, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tab_Logic)
{
    ui->setupUi(this);

    dataMan = dm;

    activeStateLogicButton = -1; // stan wejsciowy - brak wybranego przycisku
    activeTargetLogicButton = -1;

    layout_states = new QVBoxLayout();
    layout_states->setAlignment(Qt::AlignTop);
    ui->scrollArea_states->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->scrollArea_states->widget()->setLayout(layout_states);

    layout_targets = new QVBoxLayout();
    layout_targets->setAlignment(Qt::AlignTop);
    ui->scrollArea_targets->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->scrollArea_targets->widget()->setLayout(layout_targets);

    layout_conditions = new QVBoxLayout();
    layout_conditions->setAlignment(Qt::AlignTop);
    ui->scrollArea_conditions->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->scrollArea_conditions->widget()->setLayout(layout_conditions);
}

Tab_Logic::~Tab_Logic()
{
    delete ui;
}

//wywolywana przy kliknieciu na LogicTab
void Tab_Logic::pageActivated() {
    foreach (QPushButton* pb, statesLogicList) {
        removeStateFromLogicOnlyButtons(pb->text().toInt()); //ta funkcja to fix do buga (brzydkie, ale dziala)
    }
    for (uint i = targetsList.size(); i > 0; --i) {
        Tools::removeStateButton(targetsList, i-1);
    }
    foreach (State s, DATAMAN->statesListInfo) {
        addStateToLogic(s);
    }
}

void Tab_Logic::on_button_addTarget_clicked()
{
    if ( (activeStateLogicButton != -1) && (targetsDialogList.empty()) ){
        QDialog * d = new QDialog();
      //  d->setGeometry(0,0,100,100);
        QVBoxLayout* vl = new QVBoxLayout();
        d->setLayout(vl);
        connect( d, SIGNAL(finished(int)), this, SLOT(deleteTargetDialogAction()));
        foreach (State s, dataMan->statesListInfo) {
            QPushButton* pb = Tools::createStateButton(s);
            connect( pb, SIGNAL(clicked()), this, SLOT(dialogTargetButtonAction_clicked()) );
            targetsDialogList.push_back(pb);
            vl->addWidget(pb);
        }
        d->show();
    }
}

void Tab_Logic::on_button_removeTarget_clicked()
{
    if (activeTargetLogicButton != -1) {
        clearConditions();
        delete targetsList[activeTargetLogicButton];
        targetsList.erase(targetsList.begin() + activeTargetLogicButton);
        // usuwanie informacji o poszczegolnym warunku z listy stanow
        DATAMAN->removeTransition(activeStateLogicButton, activeTargetLogicButton);
        activeTargetLogicButton = -1;
    }
}

void Tab_Logic::on_button_editTarget_clicked()
{
    if ( (activeStateLogicButton != -1) && (activeTargetLogicButton != -1) ) {
        EditTargetDialog* dialog = new EditTargetDialog(activeStateLogicButton, activeTargetLogicButton, DATAMAN);
        dialog->exec();
    }
}

void Tab_Logic::on_button_addCondition_clicked()
{
    if (activeTargetLogicButton != -1) {
        ConditionWidget* cw = new ConditionWidget(DATAMAN, &(DATAMAN->statesListInfo[activeStateLogicButton]), activeTargetLogicButton, this);
        layout_conditions->addWidget(cw);
    }
}

void Tab_Logic::button_removeCondition_clicked()
{
    ConditionWidget* widget = (ConditionWidget*)sender()->parent();
    DATAMAN->removeCondition(widget->getStateNumber(), widget->getTransitionNumber(), widget->getConditionNumber());
    delete layout_conditions->takeAt(widget->getConditionNumber())->widget();
}

// metoda wywolywana przez przycisk addState z zakladki states
void Tab_Logic::addStateToLogic(State s) {
    QPushButton* pb = Tools::createStateButton(s);
    connect( pb, SIGNAL(clicked()), this, SLOT(stateLogicAction_clicked()) );
    statesLogicList.push_back(pb);
    layout_states->addWidget(pb);
}

// metoda wywolywana przez przycisk remove state z zakladki states
void Tab_Logic::removeStateFromLogic(int removedStateId) {
    Tools::removeStateButton(statesLogicList, removedStateId);
    Tools::removeStateButton(targetsDialogList, removedStateId);
    // usuwanie transitions'ow celujacych w usunietego state'a
    DATAMAN->removeTransitionsToState(removedStateId);
    // dla aktywnego stanu w logic, usun button
    for (uint i = 0; i < targetsList.size(); ++i) {
        if (targetsList[i]->text() == QString("%1").arg(removedStateId)) {
            delete targetsList[i];
            targetsList.erase(targetsList.begin() + i);
            --i;
        }
    }
}

//fix do buga
void Tab_Logic::removeStateFromLogicOnlyButtons(int removedStateId) {
    Tools::removeStateButton(statesLogicList, removedStateId);
    Tools::removeStateButton(targetsDialogList, removedStateId);
    // dla aktywnego stanu w logic, usun button
    for (uint i = 0; i < targetsList.size(); ++i) {
        if (targetsList[i]->text() == QString("%1").arg(removedStateId)) {
            delete targetsList[i];
            targetsList.erase(targetsList.begin() + i);
            --i;
        }
    }
}

void Tab_Logic::stateLogicAction_clicked() {
    if (activeStateLogicButton != -1) {
        Tools::activePushButton(statesLogicList[activeStateLogicButton], false);
    }
    if (activeTargetLogicButton != -1) {
        Tools::activePushButton(targetsList[activeTargetLogicButton], false);
        activeTargetLogicButton = -1;
    }
    clearConditions();
    for (unsigned i = 0; i < statesLogicList.size(); i++) {
        if ( statesLogicList[i] == sender() ) {
            activeStateLogicButton = i;
            Tools::activePushButton(statesLogicList[activeStateLogicButton], true);
            //  wcszytanie transition: usuwanie starych przyciskow
            foreach (QPushButton* pb, targetsList) {
                delete pb;
                targetsList.erase(targetsList.begin());
            }
            // dodawanei nowych
            for (uint i = 0; i < ((State) dataMan->statesListInfo[activeStateLogicButton]).transitions.size(); ++i) {
                QPushButton* pb = Tools::createStateButton(dataMan->statesListInfo[((State) dataMan->statesListInfo[activeStateLogicButton]).transitions[i].targetStateId]);
                connect( pb, SIGNAL(clicked()), this, SLOT(targetButtonAction_clicked()) );
                layout_targets->addWidget(pb);
                targetsList.push_back(pb);
            }
            break;
        }
    }
}

void Tab_Logic::dialogTargetButtonAction_clicked() {
    foreach (QPushButton* pb, targetsDialogList) {
        if ( pb == sender() ) {
            QPushButton* newPb = Tools::createStateButton(dataMan->statesListInfo[pb->text().toInt()]);
            connect( newPb, SIGNAL(clicked()), this, SLOT(targetButtonAction_clicked()) );
            layout_targets->addWidget(newPb);
            targetsList.push_back(newPb);
            // dodanie transition do aktywnego state'a
            DATAMAN->addTransition(activeStateLogicButton, pb->text().toInt());
            break;
        }
    }
}

void Tab_Logic::targetButtonAction_clicked() {
    if (activeTargetLogicButton != -1) {
        if (targetsList[activeTargetLogicButton] == sender()) {
            on_button_editTarget_clicked();
        }else{
            Tools::activePushButton(targetsList[activeTargetLogicButton], false);
        }
    }
    for (uint i = 0; i < targetsList.size(); ++i) {
        if ( targetsList[i] == sender()  ) {
            Tools::activePushButton(targetsList[i], true);
            if ( (uint) activeTargetLogicButton != i ) {
                clearConditions();
                activeTargetLogicButton = i;
                loadConditions();
            }else{
                activeTargetLogicButton = i;
            }
            //layout_conditions->addWidget(new ConditionWidget());
            break;
        }
    }
}

void Tab_Logic::deleteTargetDialogAction() {
    for (int i = targetsDialogList.size(); i > 0; --i) {
        delete targetsDialogList[0];
        targetsDialogList.erase(targetsDialogList.begin());
    }
}

// usuwa cala liste warunkow
void Tab_Logic::clearConditions() {
    QLayoutItem* item;
    while ((item = layout_conditions->takeAt(0))) {
        delete item->widget();
    }
}

void Tab_Logic::loadConditions() {
    for (uint i = 0; i < DATAMAN->statesListInfo[activeStateLogicButton].transitions[activeTargetLogicButton].conditions.size(); ++i) {
        Condition c = DATAMAN->statesListInfo[activeStateLogicButton].transitions[activeTargetLogicButton].conditions[i];
        ConditionWidget* cw = new ConditionWidget(DATAMAN, c, &(DATAMAN->statesListInfo[activeStateLogicButton]), activeTargetLogicButton, i, this);
        layout_conditions->addWidget(cw);
    }
}

// usuwa layout operanda z potomkami
void Tab_Logic::clearOperand(QLayout* operand) {
    // sasiedzi
    QLayout* gridLayout = operand->takeAt(0)->layout();
    for (int i = 0; i < 10; ++i) {
        delete gridLayout->takeAt(0)->widget();
    }
    delete gridLayout;
    // field
    delete operand->takeAt(0)->widget();
    // relation
    delete operand->takeAt(0)->widget();

    delete operand;
}

Operand Tab_Logic::getOperand(QLayout* operandLayout) {
    Operand o;
    QLayout* gridLayout = operandLayout->takeAt(0)->layout();
    for (uint i = 0; i < 9; ++i) {
        o.neighbours[i / 3][i % 3] = ( (QCheckBox*) gridLayout->takeAt(i)->widget() )->isChecked();
    }
    o.additionalNeighbours = ( (QSpinBox*) gridLayout->takeAt(9)->widget() )->value();
    o.field = ( (QComboBox*) operandLayout->takeAt(1)->widget() )->currentIndex();
    o.relation = Relation (( (QComboBox*) operandLayout->takeAt(2)->widget() )->currentIndex());
    return o;
}

Transition Tab_Logic::getTransition() {
    Transition t;
    t.targetStateId = targetsList[activeTargetLogicButton]->text().toInt();
    QLayout* transitionLayout;
    QLayoutItem* item;
    while ((item  = layout_conditions->takeAt(0))) {
        transitionLayout = item->layout();
        // lewy
        Condition c;
        c.leftOperand = getOperand( transitionLayout->takeAt(0)->layout() );
        // sign
        c.conditionSign = Sign( ( (QComboBox*) transitionLayout->takeAt(0)->widget() )->currentIndex() );
        // prawy
        c.rightOperand = getOperand( transitionLayout->takeAt(2)->layout() );
        t.conditions.push_back(c);
    }
    return t;
}

void Tab_Logic::on_checkBox_clicked(bool checked)
{
    if ( (activeStateLogicButton != -1) && (activeTargetLogicButton != -1) ){
        dataMan->statesListInfo[activeStateLogicButton].transitions[activeTargetLogicButton].isConjunction = checked;
    }
}
