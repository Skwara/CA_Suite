#include "configwindow.h"
#include "ui_configwindow.h"

#include <iostream>

ConfigWindow::ConfigWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigWindow)
{
    ui->setupUi(this);

    // konfiguracja scrollArea'i dla dodatkowych pol komorek
    layout_fields = new QFormLayout();
    ui->scrollArea_fields->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->scrollArea_fields->widget()->setLayout(layout_fields);

    // konfiguracja scrollArea'i dla zapisanych juz stanow
    layout_states = new QGridLayout();
    layout_states->setAlignment(Qt::AlignLeft);
    layout_states->setAlignment(Qt::AlignTop);
    ui->scrollArea_states->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->scrollArea_states->widget()->setLayout(layout_states);

    // ustawienie poczatkowego koloru
    setColorLabel(0, 0, 0);
    ui->spinBox_id->setReadOnly(true);
}

ConfigWindow::~ConfigWindow()
{
    delete ui;
}

//###########################################
// zakladaka STATES
//###########################################

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
    QPushButton* stateButton = new QPushButton( QString("%1: %2").arg(ui->spinBox_id->value()).arg(ui->lineEdit_name->text()) );

    savePushButtonColor(stateButton, ui->slider_R->value(), ui->slider_G->value(), ui->slider_B->value());

    stateButton->setMinimumHeight(60);
    stateButton->setMaximumHeight(60);
    stateButton->setMinimumWidth(60);
    stateButton->setMaximumWidth(60);
    connect( stateButton, SIGNAL(clicked()), this, SLOT(stateButtonAction_clicked()) );

    statesList.push_back(stateButton);
    layout_states->addWidget(stateButton);

    statesListInfo.push_back(getCurrentState());

    setDefaultState();
}

// ustawienie koloru tla i czcionki dla przyciskow stanu
void ConfigWindow::savePushButtonColor(QPushButton* stateButton, int r, int g, int b) {
    if (r + b + g < 383) {
        stateButton->setStyleSheet( QString("background-color: rgb( %1,%2,%3 ); color: rgb(255, 255, 255)").arg(r).arg(g).arg(b) );
    } else {
        stateButton->setStyleSheet( QString("background-color: rgb( %1,%2,%3 )").arg(r).arg(g).arg(b) );
    }
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

void ConfigWindow::stateButtonAction_clicked() {
    for (unsigned i = 0; i < statesListInfo.size(); i++) {
        // sprawdzenie, ktory przycisk zostal wcisniety
        if ( layout_states->itemAt(i)->widget() == sender() ) {
            // wczytanie wartosci z zapisanego juz stanu
            ui->spinBox_id->setValue(statesListInfo[i].id);
            ui->lineEdit_name->setText(statesListInfo[i].name.c_str());
            ui->spinBox_B->setValue(statesListInfo[i].color.blue());
            ui->spinBox_G->setValue(statesListInfo[i].color.green());
            ui->spinBox_R->setValue(statesListInfo[i].color.red());
            if (!statesListInfo[i].values.empty()) { // chyba niepotrzebne
                for (unsigned j = 0; j < statesListInfo[i].values.size(); j++) {
                    fieldsList[j].second->setValue(statesListInfo[i].values[j]);
                }
            }
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
    ui->button_addState->setText("Add State");

    QPushButton* pb = statesList[s.id];
    pb->setText(QString("%1: %2").arg(s.id).arg(s.name.c_str()));
    savePushButtonColor(pb, s.color.red(), s.color.green(), s.color.blue());
    setDefaultState();

    disconnect( ui->button_addState, SIGNAL(clicked()), this, SLOT(saveButtonAction_clicked()) );
    connect( ui->button_addState, SIGNAL(clicked()), this, SLOT(on_button_addState_clicked()) );
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
            delete statesList[removedStateId];
            statesListInfo.erase(statesListInfo.begin()+removedStateId);
            statesList.erase(statesList.begin()+removedStateId);
            ui->spinBox_id->setValue(removedStateId - 1);
            for (uint i = removedStateId; i < statesListInfo.size(); ++i) {
                statesListInfo[i].id--;
                statesList[i]->setText( QString("%1: %2").arg(statesListInfo[i].id).arg(statesListInfo[i].name.c_str()) );
            }
        }
    }
    setDefaultState();
}
