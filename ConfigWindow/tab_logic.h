#ifndef TAB_LOGIC_H
#define TAB_LOGIC_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QCheckBox>
#include <QComboBox>

#include "transition.h"
#include "operand.h"
#include "state.h"
#include "tools.h"
#include "datamanager.h"
#include "conditionwidget.h"
#include "edittargetdialog.h"

namespace Ui {
class Tab_Logic;
}

class Tab_Logic : public QWidget
{
    Q_OBJECT

public:
    explicit Tab_Logic(DataManager* dm, QWidget *parent = 0);
    ~Tab_Logic();

    void pageActivated();

private slots:
    void stateLogicAction_clicked();
    void on_button_addTarget_clicked();
    void deleteTargetDialogAction();
    void dialogTargetButtonAction_clicked();
    void targetButtonAction_clicked();
    void on_button_removeTarget_clicked();

    void on_button_editTarget_clicked();

    void on_button_addCondition_clicked();
    void button_removeCondition_clicked();

    void on_checkBox_clicked(bool checked);

private:
    Ui::Tab_Logic *ui;
    DataManager* dataMan;

    QVBoxLayout* layout_states;
    QVBoxLayout* layout_targets;
    QVBoxLayout* layout_conditions;

    std::vector<QPushButton*> statesLogicList;
    std::vector<QPushButton*> targetsDialogList;
    std::vector<QPushButton*> targetsList;

    int activeStateLogicButton;
    int activeTargetLogicButton;

    void addStateToLogic(State s);
    void removeStateFromLogic(int removedStateId);
    void removeStateFromLogicOnlyButtons(int removedStateId);
    void clearConditions();
    void loadConditions();
    void clearOperand(QLayout* operand);
    Operand getOperand(QLayout* operandLayout);
    Transition getTransition();
};

#endif // TAB_LOGIC_H
