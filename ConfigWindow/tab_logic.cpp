#include "tab_logic.h"
#include "ui_tab_logic.h"

Tab_Logic::Tab_Logic(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tab_Logic)
{
    ui->setupUi(this);

    initLogicBookmark();
}

Tab_Logic::~Tab_Logic()
{
    delete ui;
}

void Tab_Logic::initLogicBookmark() {
    activeStateLogicButton = -1; // stan wejsciowy - brak wybranego przycisku
    activeTargetLogicButton = -1;

    layout_logic_states = new QVBoxLayout();
    layout_logic_states->setAlignment(Qt::AlignTop);
    ui->scrollArea_logic_states->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->scrollArea_logic_states->widget()->setLayout(layout_logic_states);

    layout_logic_targets = new QVBoxLayout();
    layout_logic_targets->setAlignment(Qt::AlignTop);
    ui->scrollArea_logic_targets->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->scrollArea_logic_targets->widget()->setLayout(layout_logic_targets);

    layout_conditions = new QVBoxLayout();
    layout_conditions->setAlignment(Qt::AlignTop);
    ui->scrollArea_conditions->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->scrollArea_conditions->widget()->setLayout(layout_conditions);
}

// metoda wywolywana przez przycisk addState z zakladki states
void Tab_Logic::addStateToLogic(State s) {
    QPushButton* pb = Tools::createStateButton(s);
    connect( pb, SIGNAL(clicked()), this, SLOT(stateLogicAction_clicked()) );
    statesLogicList.push_back(pb);
    layout_logic_states->addWidget(pb);
}

// metoda wywolywana przez przycisk remove state z zakladki states
void Tab_Logic::removeStateFromLogic(int removedStateId) {
    Tools::removeStateButton(statesLogicList, removedStateId);
    Tools::removeStateButton(targetsDialogList, removedStateId);
    // usuwanie transitions'ow celujacych w usunietego state'a
    for (uint i = 0; i < ConfigWindow::statesListInfo.size(); ++i) {
        for (int j = ConfigWindow::statesListInfo[i].transitions.size() - 1; j >= 0; --j) {
            if (ConfigWindow::statesListInfo[i].transitions[j].targetStateId == removedStateId) {
                ConfigWindow::statesListInfo[i].transitions.erase(ConfigWindow::statesListInfo[i].transitions.begin() + j);
            }
        }
    }
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
            for (uint i = 0; i < ((State) ConfigWindow::statesListInfo[activeStateLogicButton]).transitions.size(); ++i) {
                QPushButton* pb = Tools::createStateButton(ConfigWindow::statesListInfo[((State) ConfigWindow::statesListInfo[activeStateLogicButton]).transitions[i].targetStateId]);
                connect( pb, SIGNAL(clicked()), this, SLOT(targetButtonAction_clicked()) );
                layout_logic_targets->addWidget(pb);
                targetsList.push_back(pb);
            }
            break;
        }
    }
}

void Tab_Logic::on_button_addTarget_clicked()
{
   // if ( (activeStateLogicButton != -1) && (targetsDialogList.empty()) ){
        QDialog * d = new QDialog();
      //  d->setGeometry(0,0,100,100);
        QVBoxLayout* vl = new QVBoxLayout();
        d->setLayout(vl);
        connect( d, SIGNAL(finished(int)), this, SLOT(deleteTargetDialogAction()));
        foreach (State s, ConfigWindow::statesListInfo) {
            QPushButton* pb = Tools::createStateButton(s);
            connect( pb, SIGNAL(clicked()), this, SLOT(dialogTargetButtonAction_clicked()) );
            targetsDialogList.push_back(pb);
            vl->addWidget(pb);
        }
        d->show();
    //}
}

void Tab_Logic::deleteTargetDialogAction() {
    for (int i = targetsDialogList.size(); i > 0; --i) {
        delete targetsDialogList[0];
        targetsDialogList.erase(targetsDialogList.begin());
    }
}

void Tab_Logic::dialogTargetButtonAction_clicked() {
    foreach (QPushButton* pb, targetsDialogList) {
        if ( pb == sender() ) {
            QPushButton* newPb = Tools::createStateButton(ConfigWindow::statesListInfo[pb->text().toInt()]);
            connect( newPb, SIGNAL(clicked()), this, SLOT(targetButtonAction_clicked()) );
            layout_logic_targets->addWidget(newPb);
            targetsList.push_back(newPb);
            // dodanie transition do aktywnego state'a
            Transition t;
            t.targetStateId = pb->text().toInt();
            ConfigWindow::statesListInfo[activeStateLogicButton].transitions.push_back(t);
            break;
        }
    }
}

void Tab_Logic::targetButtonAction_clicked() {
    if (activeTargetLogicButton != -1) {
        Tools::activePushButton(targetsList[activeTargetLogicButton], false);
    }
    //clearConditions();
    for (uint i = 0; i < targetsList.size(); ++i) {
        if ( targetsList[i] == sender()  ) {
                Tools::activePushButton(targetsList[i], true);
                if ( (uint) activeTargetLogicButton != i ) {
                    clearConditions();
                }
                activeTargetLogicButton = i;
                layout_conditions->addLayout(createTransitionLayout());
            }
    }
    // ta linijka powinna zapisywac transition
    //ConfigWindow::statesListInfo[activeStateLogicButton].transitions[activeTargetLogicButton] = getTransition();
}

void Tab_Logic::on_button_removeTarget_clicked()
{
    if (activeTargetLogicButton != -1) {
        clearConditions();
        delete targetsList[activeTargetLogicButton];
        targetsList.erase(targetsList.begin() + activeTargetLogicButton);
        // usuwanie informacji o poszczegolnym warunku z listy stanow
        ConfigWindow::statesListInfo[activeStateLogicButton].transitions.erase(ConfigWindow::statesListInfo[activeStateLogicButton].transitions.begin() + activeTargetLogicButton);
        activeTargetLogicButton = -1;
    }
}

// tworzy operanda
QHBoxLayout* Tab_Logic::createOperandLayout() {
    QGridLayout* neighboursLayout = new QGridLayout();
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            QCheckBox* cb = new QCheckBox();
            neighboursLayout->addWidget(cb, i, j);
        }
    }
    neighboursLayout->setHorizontalSpacing(0);
    neighboursLayout->setVerticalSpacing(0);

    QSpinBox* additionalNeihbours = new QSpinBox();
    additionalNeihbours->setMaximum(9);
    neighboursLayout->addWidget(additionalNeihbours, 3, 0, 3, 3);

    QComboBox* field = new QComboBox();
    field->addItem("pole 1");
    field->addItem("pole 2");

    QComboBox* relation = new QComboBox();
    relation->addItem("1-1");
    relation->addItem("Suma");
    relation->addItem("Srednia");

    QHBoxLayout* operandLayout = new QHBoxLayout();
    operandLayout->addLayout(neighboursLayout);
    operandLayout->addWidget(field);
    operandLayout->addWidget(relation);

    return operandLayout;
}

// tworzy cale pola wyrazenia funkcji
QHBoxLayout* Tab_Logic::createTransitionLayout() {

    QHBoxLayout* transitionLayout = new QHBoxLayout();
    transitionLayout->addLayout(createOperandLayout());

    QComboBox* sign = new QComboBox();
    sign->addItem("<");
    sign->addItem(">");
    //sign->setSizePolicy();
    transitionLayout->addWidget(sign);

    transitionLayout->addLayout(createOperandLayout());
    transitionLayout->setAlignment(Qt::AlignTop);

    return transitionLayout ;

}

// usuwa cala liste warunkow
void Tab_Logic::clearConditions() {
    QLayout* transitionLayout;
    QLayoutItem* item;
    while ((item  = layout_conditions->takeAt(0))) {
        transitionLayout = item->layout();
        // lewy
        clearOperand( transitionLayout->takeAt(0)->layout() );
        // sign
        delete transitionLayout->takeAt(0)->widget();
        // prawy
        clearOperand( transitionLayout->takeAt(0)->layout() );
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
    o.field = ( (QComboBox*) operandLayout->takeAt(1)->widget() )->currentText().toStdString();
    o.relation = ( (QComboBox*) operandLayout->takeAt(2)->widget() )->currentText().toStdString();
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
        c.conditionSign = ( (QComboBox*) transitionLayout->takeAt(0)->widget() )->currentText().toStdString();
        // prawy
        c.rightOperand = getOperand( transitionLayout->takeAt(2)->layout() );
        t.conditions.push_back(c);
    }
    return t;
}
