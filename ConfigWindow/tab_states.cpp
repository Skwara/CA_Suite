#include "tab_states.h"
#include "ui_tab_states.h"

#include <iostream>

#define STATE_SHAPE_SIZE 60
#define DATAMAN dataMan

Tab_States::Tab_States(DataManager* dm, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tab_States)
{
    ui->setupUi(this);

    dataMan = dm;

    //maxStatesLineNumber = getStatesLineNumber();

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

    setDefaultState();
}

Tab_States::~Tab_States()
{
    delete ui;
}

void Tab_States::pageActivated()
{
    windowResized();
}

void Tab_States::on_button_addProp_clicked()
{
    QLineEdit* name = new QLineEdit();
    QDoubleSpinBox* value = new QDoubleSpinBox();
    connect(name, SIGNAL(textChanged(QString)), this, SLOT(on_textChanged(QString)));
    name->setFixedWidth(120);
    value->setFixedWidth(70);
    name->setPlaceholderText(QString("name%1").arg(fieldsList.size()));

    DATAMAN->addProperty(name->placeholderText().toStdString());

    fieldsList.push_back(std::pair<QLineEdit*, QDoubleSpinBox*>(name, value));
    layout_fields->addRow(name, value);
}

void Tab_States::on_button_removeProp_clicked()
{
    if (fieldsList.size() > 0) {
        DATAMAN->removeProperty();

        delete fieldsList[fieldsList.size() - 1].first;
        delete fieldsList[fieldsList.size() - 1].second;
        fieldsList.pop_back();
    }
}

void Tab_States::on_button_addState_clicked()
{
    State s = getCurrentState();
    DATAMAN->addState(s);

    QPushButton* stateButton = Tools::createStateButton(s);
    addStateToLayout(stateButton, statesList.size());
    connect(stateButton, SIGNAL(clicked()), this, SLOT(stateButtonAction_clicked()));
    statesList.push_back(stateButton);
    setDefaultState();
}

void Tab_States::on_button_removeState_clicked()
{
    uint removedStateId = (uint)ui->spinBox_id->value();
    ui->spinBox_id->setValue(removedStateId - 1);

    DATAMAN->removeState(removedStateId);

    Tools::removeStateButton(statesList, removedStateId);

    setDefaultState();
    if (ui->button_addState->text() != "Add State") {
        ui->button_addState->setText("Add State");
        disconnect( ui->button_addState, SIGNAL(clicked()), this, SLOT(saveButtonAction_clicked()) );
        connect( ui->button_addState, SIGNAL(clicked()), this, SLOT(on_button_addState_clicked()) );
    }
    repaintStatesLayout();
    //removeStateFromLogic(removedStateId);
}

void Tab_States::on_slider_R_valueChanged(int value)
{
    setColorLabel(value, ui->slider_G->value(), ui->slider_B->value() );
}

void Tab_States::on_slider_G_valueChanged(int value)
{
    setColorLabel(ui->slider_R->value(), value, ui->slider_B->value() );
}

void Tab_States::on_slider_B_valueChanged(int value)
{
    setColorLabel(ui->slider_R->value(), ui->slider_G->value(), value );
}

void Tab_States::on_textChanged(QString value)
{
    //TODO dopisac zmiane nazw w conditionWidget comboBox
    std::string senderName = ((QLineEdit*)sender())->placeholderText().toStdString();
    ((QLineEdit*)sender())->setPlaceholderText(value);
    for (uint i = 0; i < DATAMAN->names.size(); ++i) {
        if (senderName == DATAMAN->names[i]) {
            DATAMAN->names[i] = value.toStdString();
        }
    }
}

void Tab_States::setColorLabel(int r, int g, int b) {
    ui->color_label->setStyleSheet( QString("background-color: rgb( %1,%2,%3 )").arg(r).arg(g).arg(b) );
}

void Tab_States::stateButtonAction_clicked() {
    for (unsigned i = 0; i < statesList.size(); i++) {
        // sprawdzenie, ktory przycisk zostal wcisniety
        if ( statesList[i] == sender() ) {
            //wylaczenie ramki poprzedniego zaznaczonego stanu
            if ((uint)ui->spinBox_id->value() < statesList.size()) {
                Tools::activePushButton(statesList[ui->spinBox_id->value()], false);
            }
            // wczytanie wartosci z zapisanego juz stanu
            ui->spinBox_id->setValue( dataMan->statesListInfo[i].id);
            ui->lineEdit_name->setText( dataMan->statesListInfo[i].name.c_str());
            ui->spinBox_B->setValue( dataMan->statesListInfo[i].color.blue());
            ui->spinBox_G->setValue( dataMan->statesListInfo[i].color.green());
            ui->spinBox_R->setValue( dataMan->statesListInfo[i].color.red());
            //przesuniecie bo pierwszym elementem jest id stanu
            for (unsigned j = 1; j < dataMan->statesListInfo[i].values.size(); ++j) {
                fieldsList[j - 1].second->setValue( dataMan->statesListInfo[i].values[j]);
            }
            Tools::activePushButton((QPushButton*)sender(), true);
            break;
        }
    }
    // zmina akcji z dodawania na zapisywanie
    ui->button_addState->setText("save");
    disconnect( ui->button_addState, SIGNAL(clicked()), this, SLOT(on_button_addState_clicked()) );
    connect( ui->button_addState, SIGNAL(clicked()), this, SLOT(saveButtonAction_clicked()) );
}

void Tab_States::saveButtonAction_clicked() {
    State s = getCurrentState();
    dataMan->statesListInfo[s.id] = s;

    QPushButton* pb = statesList[s.id];
    pb->setText(QString("%1").arg(s.id));
    Tools::savePushButtonColor(pb, s.color.red(), s.color.green(), s.color.blue());
    setDefaultState();

    Tools::activePushButton(pb, false);

    ui->button_addState->setText("Add State");
    disconnect( ui->button_addState, SIGNAL(clicked()), this, SLOT(saveButtonAction_clicked()) );
    connect( ui->button_addState, SIGNAL(clicked()), this, SLOT(on_button_addState_clicked()) );
}

// pobiera ustawienia aktualnie wyswietlanego stanu
State Tab_States::getCurrentState() {
    State s = State();
    s.id = ui->spinBox_id->value();
    s.name = ui->lineEdit_name->text().toStdString();
    s.color = QColor(ui->spinBox_R->value(), ui->spinBox_G->value(), ui->spinBox_B->value());
    s.values.push_back(s.id);
    for (unsigned i = 0; i < fieldsList.size(); i++ ) {
        s.values.push_back( fieldsList[i].second->value());
    }
    return s;
}

void Tab_States::setDefaultState() {
    ui->spinBox_id->setValue(dataMan->statesListInfo.size());
    ui->lineEdit_name->setText("");
    ui->lineEdit_name->setPlaceholderText("name");
    ui->spinBox_B->setValue(0);
    ui->spinBox_G->setValue(0);
    ui->spinBox_R->setValue(0);
    for (unsigned j = 0; j < fieldsList.size(); j++) {
        fieldsList[j].second->setValue(0);
    }
}

void Tab_States::windowResized() {
    int newMaxStatesLineNumber = getStatesLineNumber();
    if ( newMaxStatesLineNumber != maxStatesLineNumber) {
        maxStatesLineNumber = newMaxStatesLineNumber;
        repaintStatesLayout();
    }
}

int Tab_States::getStatesLineNumber() {
    return ui->scrollArea_states->width() / (STATE_SHAPE_SIZE + 6);
}

void Tab_States::repaintStatesLayout() {
    QLayoutItem* li;
    while ((li = layout_states->itemAt(0))) {
        layout_states->removeItem(li);
    }
    for (unsigned i = 0; i < statesList.size(); ++i) {
        addStateToLayout(statesList[i], i);
    }
}

void Tab_States::addStateToLayout(QPushButton* stateButton, int position) {
    if ( position % maxStatesLineNumber == 0 ){
        QHBoxLayout* hl = new QHBoxLayout();
        layout_states->addLayout(hl);
        hl->addWidget(stateButton);
        hl->setAlignment(Qt::AlignLeft);
    } else {
        ( (QHBoxLayout*) layout_states->itemAt(position / maxStatesLineNumber) )->addWidget(stateButton);
    }
}
