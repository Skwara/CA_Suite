#include "configwindow.h"
#include "ui_configwindow.h"

#include <iostream>

#include <QPalette>

ConfigWindow::ConfigWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigWindow)
{
    ui->setupUi(this);

    initStatesBookmark();
    initLogicBookmark();
}

ConfigWindow::~ConfigWindow()
{
    delete ui;
}

//###########################################
// COMMONS
//###########################################

QPushButton* ConfigWindow::createStateButton(State s) {
    QPushButton* stateButton = new QPushButton( QString("%1").arg(s.id) );

    savePushButtonColor(stateButton, s.color.red(), s.color.green(), s.color.blue());

    stateButton->setMinimumHeight(STATE_SHAPE_SIZE);
    stateButton->setMaximumHeight(STATE_SHAPE_SIZE);
    stateButton->setMinimumWidth(STATE_SHAPE_SIZE);
    stateButton->setMaximumWidth(STATE_SHAPE_SIZE);

    return stateButton;
}

// ustawienie koloru tla i czcionki dla przyciskow stanu
void ConfigWindow::savePushButtonColor(QPushButton* stateButton, int r, int g, int b) {
    if (r + b + g < FONT_COLOR_THRESHOLD) {
        stateButton->setStyleSheet( QString("background-color: rgb( %1,%2,%3 ); color: rgb(255, 255, 255); border: 0px").arg(r).arg(g).arg(b) );
    } else {
        stateButton->setStyleSheet( QString("background-color: rgb( %1,%2,%3 ); border: 0px").arg(r).arg(g).arg(b) );
    }
}

void ConfigWindow::activePushButton(QPushButton* stateButton, bool active) {
    int r = stateButton->palette().background().color().red();
    int g = stateButton->palette().background().color().green();
    int b = stateButton->palette().background().color().blue();
    if (active) {
        if (r + g + b < FONT_COLOR_THRESHOLD) {
            stateButton->setStyleSheet(QString("background-color: rgb( %1,%2,%3 ); color: rgb(255, 255, 255); border: 2px solid #ffffff").arg(r).arg(g).arg(b));
        } else {
            stateButton->setStyleSheet(QString("background-color: rgb( %1,%2,%3 ); border: 2px solid #000000").arg(r).arg(g).arg(b));
        }
    } else {
        savePushButtonColor(stateButton, r, g, b);
    }
}
// usuwa button z listy state'ow, przesuwa idki
void ConfigWindow::removeStateButton(std::vector<QPushButton*>& buttonsList, int removedStateId) {
    if ((uint) removedStateId < buttonsList.size()) {
        delete buttonsList[removedStateId];
        buttonsList.erase(buttonsList.begin()+removedStateId);
        for (uint i = removedStateId; i < buttonsList.size(); ++i) {
            buttonsList[i]->setText( QString("%1").arg(i) );
        }
    }
}

//###########################################
// zakladaka STATES
//###########################################

void ConfigWindow::initStatesBookmark() {
    maxStatesLineNumber = getStatesLineNumber();

    // konfiguracja scrollArea'i dla dodatkowych pol komorek
    layout_fields = new QFormLayout();
    ui->scrollArea_fields->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->scrollArea_fields->widget()->setLayout(layout_fields);

    // konfiguracja scrollArea'i dla zapisanych juz stanow
    layout_states = new QVBoxLayout();
    layout_states->setAlignment(Qt::AlignLeft);
    layout_states->setAlignment(Qt::AlignTop);
    ui->scrollArea_states->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->scrollArea_states->widget()->setLayout(layout_states);

    // ustawienie poczatkowego koloru
    setColorLabel(0, 0, 0);
    ui->spinBox_id->setReadOnly(true);
}

void ConfigWindow::on_button_addProp_clicked()
{
    QLineEdit* name = new QLineEdit();
    QDoubleSpinBox* value = new QDoubleSpinBox();
    name->setFixedWidth(120);
    value->setFixedWidth(70);
    name->setPlaceholderText("name");
    fieldsList.push_back(std::pair<QLineEdit*, QDoubleSpinBox*>(name, value));

    for (uint i = 0; i < statesListInfo.size(); ++i) {
        statesListInfo[i].values.push_back(0);
    }

    layout_fields->addRow(name, value);
}

void ConfigWindow::on_button_removeProp_clicked()
{
    if (fieldsList.size() > 0) {
        delete fieldsList[fieldsList.size() - 1].first;
        delete fieldsList[fieldsList.size() - 1].second;
        fieldsList.pop_back();
        for (unsigned i = 0; i < statesListInfo.size(); i++) {
            if (!statesListInfo[i].values.empty()) {
                statesListInfo[i].values.pop_back();
            }
        }
    }
}

void ConfigWindow::on_button_removeState_clicked()
{
    uint removedStateId = (uint)ui->spinBox_id->value();
    if (statesListInfo.size() > 0) {
        if ((uint)removedStateId < statesListInfo.size()) {
            statesListInfo.erase(statesListInfo.begin()+removedStateId);
            ui->spinBox_id->setValue(removedStateId - 1);
            for (uint i = removedStateId; i < statesListInfo.size(); ++i) {
                statesListInfo[i].id--;
            }
        }
        removeStateButton(statesList, removedStateId);
    }
    setDefaultState();
    if (ui->button_addState->text() != "Add State") {
        ui->button_addState->setText("Add State");
        disconnect( ui->button_addState, SIGNAL(clicked()), this, SLOT(saveButtonAction_clicked()) );
        connect( ui->button_addState, SIGNAL(clicked()), this, SLOT(on_button_addState_clicked()) );
    }
    repaintStatesLayout();
    removeStateFromLogic(removedStateId);
}

void ConfigWindow::on_slider_R_valueChanged(int value)
{
    setColorLabel(value, ui->slider_G->value(), ui->slider_B->value() );
}

void ConfigWindow::on_slider_G_valueChanged(int value)
{
    setColorLabel(ui->slider_R->value(), value, ui->slider_B->value() );
}

void ConfigWindow::on_slider_B_valueChanged(int value)
{
    setColorLabel(ui->slider_R->value(), ui->slider_G->value(), value );

}

void ConfigWindow::setColorLabel(int r, int g, int b) {
    ui->color_label->setStyleSheet( QString("background-color: rgb( %1,%2,%3 )").arg(r).arg(g).arg(b) );
}

void ConfigWindow::on_button_addState_clicked()
{
    State s = getCurrentState();
    QPushButton* stateButton = createStateButton(s);
    connect( stateButton, SIGNAL(clicked()), this, SLOT(stateButtonAction_clicked()) );

    addStateToLogic(s);

    addStateToLayout(stateButton, statesList.size());
    statesList.push_back(stateButton);  
    statesListInfo.push_back(s);

    setDefaultState();
}

void ConfigWindow::stateButtonAction_clicked() {
    for (unsigned i = 0; i < statesList.size(); i++) {
        // sprawdzenie, ktory przycisk zostal wcisniety
        if ( statesList[i] == sender() ) {
            //wylaczenie ramki poprzedniego zaznaczonego stanu
            if ((uint)ui->spinBox_id->value() < statesList.size()) {
                activePushButton(statesList[ui->spinBox_id->value()], false);
            }
            // wczytanie wartosci z zapisanego juz stanu
            ui->spinBox_id->setValue(statesListInfo[i].id);
            ui->lineEdit_name->setText(statesListInfo[i].name.c_str());
            ui->spinBox_B->setValue(statesListInfo[i].color.blue());
            ui->spinBox_G->setValue(statesListInfo[i].color.green());
            ui->spinBox_R->setValue(statesListInfo[i].color.red());
            for (unsigned j = 0; j < statesListInfo[i].values.size(); j++) {
                fieldsList[j].second->setValue(statesListInfo[i].values[j]);
            }
            activePushButton((QPushButton*)sender(), true);
            break;
        }
    }
    // zmina akcji z dodawania na zapisywanie
    ui->button_addState->setText("save");
    disconnect( ui->button_addState, SIGNAL(clicked()), this, SLOT(on_button_addState_clicked()) );
    connect( ui->button_addState, SIGNAL(clicked()), this, SLOT(saveButtonAction_clicked()) );
}

void ConfigWindow::saveButtonAction_clicked() {
    State s = getCurrentState();
    statesListInfo[s.id] = s;

    QPushButton* pb = statesList[s.id];
    pb->setText(QString("%1").arg(s.id));
    savePushButtonColor(pb, s.color.red(), s.color.green(), s.color.blue());
    setDefaultState();

    activePushButton(pb, false);

    ui->button_addState->setText("Add State");
    disconnect( ui->button_addState, SIGNAL(clicked()), this, SLOT(saveButtonAction_clicked()) );
    connect( ui->button_addState, SIGNAL(clicked()), this, SLOT(on_button_addState_clicked()) );
}

void ConfigWindow::addStateToLayout(QPushButton* stateButton, int pozition) {
    if ( pozition % maxStatesLineNumber == 0 ){
          QHBoxLayout* hl = new QHBoxLayout();
          layout_states->addLayout(hl);
          hl->addWidget(stateButton);
          hl->setAlignment(Qt::AlignLeft);
      } else {
          ( (QHBoxLayout*) layout_states->itemAt(pozition / maxStatesLineNumber) )->addWidget(stateButton);
      }
}

int ConfigWindow::getStatesLineNumber() {
    return ui->scrollArea_states->width() / (STATE_SHAPE_SIZE + 10);
}

// pobiera ustawienia aktualnie wyswietlanego stanu
State ConfigWindow::getCurrentState() {
    State s = State();
    s.id = ui->spinBox_id->value();
    s.name = ui->lineEdit_name->text().toStdString();
    s.color = QColor(ui->spinBox_R->value(), ui->spinBox_G->value(), ui->spinBox_B->value());
    for (unsigned i = 0; i < fieldsList.size(); i++ ) {
        s.values.push_back( fieldsList[i].second->value());
    }
    return s;
}

void ConfigWindow::setDefaultState() {
    ui->spinBox_id->setValue(statesListInfo.size());
    ui->lineEdit_name->setText("");
    ui->spinBox_B->setValue(0);
    ui->spinBox_G->setValue(0);
    ui->spinBox_R->setValue(0);
    for (unsigned j = 0; j < fieldsList.size(); j++) {
        fieldsList[j].second->setValue(0);
    }
}

void ConfigWindow::resizeEvent(QResizeEvent* event) {
    int newMaxStatesLineNumber = getStatesLineNumber();
    if ( newMaxStatesLineNumber != maxStatesLineNumber) {
        maxStatesLineNumber = newMaxStatesLineNumber;
        repaintStatesLayout();
    }
}

void ConfigWindow::repaintStatesLayout() {
    QLayoutItem* li;
    while ((uint) (li = layout_states->itemAt(0))) {
        layout_states->removeItem(li);
    }
    for (unsigned i = 0; i < statesList.size(); ++i) {
        addStateToLayout(statesList[i], i);
    }
}

//###########################################
// zakladaka LOGIC
//###########################################

void ConfigWindow::initLogicBookmark() {
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
void ConfigWindow::addStateToLogic(State s) {
    QPushButton* pb = createStateButton(s);
    connect( pb, SIGNAL(clicked()), this, SLOT(stateLogicAction_clicked()) );
    statesLogicList.push_back(pb);
    layout_logic_states->addWidget(pb);
}

// metoda wywolywana przez przycisk remove state z zakladki states
void ConfigWindow::removeStateFromLogic(int removedStateId) {
    removeStateButton(statesLogicList, removedStateId);
    removeStateButton(targetsDialogList, removedStateId);
    // usuwanie transitions'ow celujacych w usunietego state'a
    for (uint i = 0; i < statesListInfo.size(); ++i) {
        for (int j = statesListInfo[i].transitions.size() - 1; j >= 0; --j) {
            if (statesListInfo[i].transitions[j].targetStateId == removedStateId) {
                statesListInfo[i].transitions.erase(statesListInfo[i].transitions.begin() + j);
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

void ConfigWindow::stateLogicAction_clicked() {
    if (activeStateLogicButton != -1) {
        activePushButton(statesLogicList[activeStateLogicButton], false);
    }
    if (activeTargetLogicButton != -1) {
        activePushButton(targetsList[activeTargetLogicButton], false);
        activeTargetLogicButton = -1;
    }
    clearConditions();
    for (unsigned i = 0; i < statesLogicList.size(); i++) {
        if ( statesLogicList[i] == sender() ) {
            activeStateLogicButton = i;
            activePushButton(statesLogicList[activeStateLogicButton], true);
            //  wcszytanie transition: usuwanie starych przyciskow
            foreach (QPushButton* pb, targetsList) {
                delete pb;
                targetsList.erase(targetsList.begin());
            }
            // dodawanei nowych
            for (uint i = 0; i < ((State) statesListInfo[activeStateLogicButton]).transitions.size(); ++i) {
                QPushButton* pb = createStateButton(statesListInfo[((State) statesListInfo[activeStateLogicButton]).transitions[i].targetStateId]);
                connect( pb, SIGNAL(clicked()), this, SLOT(targetButtonAction_clicked()) );
                layout_logic_targets->addWidget(pb);
                targetsList.push_back(pb);
            }
            break;
        }
    }
}

void ConfigWindow::on_button_addTarget_clicked()
{
    if ( (activeStateLogicButton != -1) && (targetsDialogList.empty()) ){
        QDialog * d = new QDialog();
      //  d->setGeometry(0,0,100,100);
        QVBoxLayout* vl = new QVBoxLayout();
        d->setLayout(vl);
        connect( d, SIGNAL(finished(int)), this, SLOT(deleteTargetDialogAction()));
        foreach (State s, statesListInfo) {
            QPushButton* pb = createStateButton(s);
            connect( pb, SIGNAL(clicked()), this, SLOT(dialogTargetButtonAction_clicked()) );
            targetsDialogList.push_back(pb);
            vl->addWidget(pb);
        }
        d->show();
    }
}

void ConfigWindow::deleteTargetDialogAction() {
    for (int i = targetsDialogList.size(); i > 0; --i) {
        delete targetsDialogList[0];
        targetsDialogList.erase(targetsDialogList.begin());
    }
}

void ConfigWindow::dialogTargetButtonAction_clicked() {
    foreach (QPushButton* pb, targetsDialogList) {
        if ( pb == sender() ) {
            QPushButton* newPb = createStateButton(statesListInfo[pb->text().toInt()]);
            connect( newPb, SIGNAL(clicked()), this, SLOT(targetButtonAction_clicked()) );
            layout_logic_targets->addWidget(newPb);
            targetsList.push_back(newPb);
            // dodanie transition do aktywnego state'a
            Transition t;
            t.targetStateId = pb->text().toInt();
            statesListInfo[activeStateLogicButton].transitions.push_back(t);
            break;
        }
    }
}

void ConfigWindow::targetButtonAction_clicked() {
    if (activeTargetLogicButton != -1) {
        activePushButton(targetsList[activeTargetLogicButton], false);
    }
    //clearConditions();
    for (uint i = 0; i < targetsList.size(); ++i) {
        if ( targetsList[i] == sender()  ) {
                activePushButton(targetsList[i], true);
                if ( (uint) activeTargetLogicButton != i ) {
                    clearConditions();
                }
                activeTargetLogicButton = i;
                layout_conditions->addLayout(createTransitionLayout());
            }
    }
    // ta linijka powinna zapisywac transition
    //statesListInfo[activeStateLogicButton].transitions[activeTargetLogicButton] = getTransition();
}

void ConfigWindow::on_button_removeTarget_clicked()
{
    if (activeTargetLogicButton != -1) {
        clearConditions();
        delete targetsList[activeTargetLogicButton];
        targetsList.erase(targetsList.begin() + activeTargetLogicButton);
        // usuwanie informacji o poszczegolnym warunku z listy stanow
        statesListInfo[activeStateLogicButton].transitions.erase(statesListInfo[activeStateLogicButton].transitions.begin() + activeTargetLogicButton);
        activeTargetLogicButton = -1;
    }
}

void ConfigWindow::on_configTabs_currentChanged(int index)
{

}

// tworzy operanda
QHBoxLayout* ConfigWindow::createOperandLayout() {
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
QHBoxLayout* ConfigWindow::createTransitionLayout() {

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
void ConfigWindow::clearConditions() {
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
void ConfigWindow::clearOperand(QLayout* operand) {
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

Operand ConfigWindow::getOperand(QLayout* operandLayout) {
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

Transition ConfigWindow::getTransition() {
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

