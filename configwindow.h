#ifndef CONFIGWINDOW_H
#define CONFIGWINDOW_H

#include <QDialog>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QFormLayout>
#include <QGridLayout>
#include <QApplication>
#include <QSpinBox>
#include <QComboBox>
#include <QCheckBox>

#include <vector>
#include <utility>

#include "state.h"
#include "transition.h"
#include "operand.h"
#include "condition.h"

#define FONT_COLOR_THRESHOLD 250
#define STATE_SHAPE_SIZE 60

namespace Ui {
class ConfigWindow;
}

class ConfigWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigWindow(QWidget *parent = 0);
    ~ConfigWindow();

private slots:
    void on_button_addProp_clicked();
    void on_slider_R_valueChanged(int value);
    void on_slider_G_valueChanged(int value);
    void on_slider_B_valueChanged(int value);
    void on_button_addState_clicked();
    void stateButtonAction_clicked();
    void saveButtonAction_clicked();
    void on_button_removeProp_clicked();
    void on_button_removeState_clicked();

    void on_configTabs_currentChanged(int index);

    void stateLogicAction_clicked();
    void on_button_addTarget_clicked();
    void deleteTargetDialogAction();
    void dialogTargetButtonAction_clicked();
    void targetButtonAction_clicked();
    void on_button_removeTarget_clicked();

private:
    Ui::ConfigWindow *ui;

    QFormLayout* layout_fields;
    QVBoxLayout* layout_states;
    QVBoxLayout* layout_logic_states;
    QVBoxLayout* layout_logic_targets;
    QVBoxLayout* layout_conditions;

    std::vector< std::pair<QLineEdit*, QDoubleSpinBox*> > fieldsList;
    std::vector<QPushButton*> statesList;
    std::vector<QPushButton*> statesLogicList;
    std::vector<QPushButton*> targetsDialogList;
    std::vector<QPushButton*> targetsList;
    std::vector<State> statesListInfo;

    int maxStatesLineNumber;
    int activeStateLogicButton;
    int activeTargetLogicButton;

    QPushButton* createStateButton(State s);
    void savePushButtonColor(QPushButton* pb, int r, int g, int b);
    void activePushButton(QPushButton* stateButton, bool active);
    void removeStateButton(std::vector<QPushButton*>& buttonsList, int removedStateId);

    void initStatesBookmark();
    void setColorLabel(int r, int g, int b);
    void addStateToLayout(QPushButton* stateButton, int pozition);
    int getStatesLineNumber();
    State getCurrentState();
    void setDefaultState();
    void resizeEvent(QResizeEvent* event);
    void repaintStatesLayout();

    void initLogicBookmark();
    void addStateToLogic(State s);
    void removeStateFromLogic(int removedStateId);
    QHBoxLayout* createTransitionLayout();
    QHBoxLayout* createOperandLayout();
    void clearConditions();
    void clearOperand(QLayout* operand);
    Operand getOperand(QLayout* operandLayout);
    Transition getTransition();
};

#endif // CONFIGWINDOW_H
