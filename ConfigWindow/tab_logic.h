#ifndef TAB_LOGIC_H
#define TAB_LOGIC_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QCheckBox>

#include "configwindow.h"
#include "transition.h"
#include "operand.h"
#include "state.h"
#include "tools.h"

namespace Ui {
class Tab_Logic;
}

class Tab_Logic : public QWidget
{
    Q_OBJECT

public:
    explicit Tab_Logic(QWidget *parent = 0);
    ~Tab_Logic();

private slots:
    void stateLogicAction_clicked();
    void on_button_addTarget_clicked();
    void deleteTargetDialogAction();
    void dialogTargetButtonAction_clicked();
    void targetButtonAction_clicked();
    void on_button_removeTarget_clicked();

private:
    Ui::Tab_Logic *ui;

    QVBoxLayout* layout_logic_states;
    QVBoxLayout* layout_logic_targets;
    QVBoxLayout* layout_conditions;

    std::vector<QPushButton*> statesLogicList;
    std::vector<QPushButton*> targetsDialogList;
    std::vector<QPushButton*> targetsList;

    int activeStateLogicButton;
    int activeTargetLogicButton;

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

#endif // TAB_LOGIC_H
