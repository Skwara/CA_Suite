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
#include <iostream>

#include "state.h"
#include "transition.h"
#include "operand.h"
#include "condition.h"
#include "tools.h"
#include "datamanager.h"
#include "tab_states.h"
#include "tab_logic.h"

namespace Ui {
class ConfigWindow;
}

class ConfigWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigWindow(QWidget *parent = 0);
    ~ConfigWindow();

    DataManager dataManager;

private slots:

    void on_configTabs_currentChanged(int index);

private:
    Ui::ConfigWindow *ui;

    Tab_States* tab_states;
    Tab_Logic* tab_logic;

    void resizeEvent(QResizeEvent* event);
};

#endif // CONFIGWINDOW_H
