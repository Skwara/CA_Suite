#ifndef CONDITIONW_H
#define CONDITIONW_H

#include <QWidget>

#include "state.h"
#include "transition.h"
#include "datamanager.h"

namespace Ui {
class ConditionWidget;
}

class ConditionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ConditionWidget(DataManager* dm, State* state, uint transitionNumber, QWidget *parent = 0);
    ~ConditionWidget();

private slots:
    void on_checkBox_clicked();

    void on_checkBox_2_clicked();

    void on_checkBox_3_clicked();

    void on_checkBox_4_clicked();

    void on_checkBox_5_clicked();

    void on_checkBox_6_clicked();

    void on_checkBox_7_clicked();

    void on_checkBox_8_clicked();

    void on_checkBox_9_clicked();

    void on_checkBox_10_clicked();

    void on_checkBox_11_clicked();

    void on_checkBox_12_clicked();

    void on_checkBox_13_clicked();

    void on_checkBox_14_clicked();

    void on_checkBox_15_clicked();

    void on_checkBox_16_clicked();

    void on_checkBox_17_clicked();

    void on_checkBox_18_clicked();

    void on_spinBox_left_valueChanged(int arg1);

    void on_spinBox_right_valueChanged(int arg1);

    void on_comboBox_leftField_currentTextChanged(const QString &arg1);

    void on_comboBox_rightField_currentTextChanged(const QString &arg1);

    void on_comboBox_leftRelation_currentTextChanged(const QString &arg1);

    void on_comboBox_rightRelation_currentTextChanged(const QString &arg1);

    void on_comboBox_sign_currentTextChanged(const QString &arg1);

    void on_radioButton_leftAll_clicked();

    void on_radioButton_leftAny_clicked();

    void on_radioButton_rightAll_clicked();

    void on_radioButton_rightAny_clicked();

    void on_button_removeCondition_clicked();

private:
    Ui::ConditionWidget *ui;
    DataManager* dataMan;
    State* state;
    uint transitionNumber;
    uint conditionNumber;

    //do przemyslenia
    void setLeftNeighbour(QObject* sender, uint row, uint col);
    void setRightNeighbour(QObject* sender, uint row, uint col);
};

#endif // CONDITIONW_H
