#ifndef TAB_STATES_H
#define TAB_STATES_H

#include <QWidget>
#include <QPushButton>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QDoubleSpinBox>

#include "state.h"
#include "tools.h"
#include "configwindow.h"

#include <vector>

namespace Ui {
class Tab_States;
}

class Tab_States : public QWidget
{
    Q_OBJECT

public:
    explicit Tab_States(QWidget *parent = 0);
    ~Tab_States();

private slots:
    void on_button_addProp_clicked();
    void on_button_removeProp_clicked();
    void on_button_addState_clicked();
    void on_button_removeState_clicked();
    void on_slider_R_valueChanged(int value);
    void on_slider_G_valueChanged(int value);
    void on_slider_B_valueChanged(int value);
    void stateButtonAction_clicked();
    void saveButtonAction_clicked();

private:
    Ui::Tab_States *ui;

    QFormLayout* layout_fields;
    QVBoxLayout* layout_states;

    std::vector< std::pair<QLineEdit*, QDoubleSpinBox*> > fieldsList;
    std::vector<QPushButton*> statesList;

    int maxStatesLineNumber;

    void initStatesBookmark();
    void setColorLabel(int r, int g, int b);
    void addStateToLayout(QPushButton* stateButton, int pozition);
    int getStatesLineNumber();
    State getCurrentState();
    void setDefaultState();
    void resizeEvent(QResizeEvent* event);
    void repaintStatesLayout();
};

#endif // TAB_STATES_H
