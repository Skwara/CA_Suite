#ifndef GUIMANAGER_H
#define GUIMANAGER_H

#include <QFormLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QPushButton>

#include <vector>

#include "ui_configwindow.h"
#include "tools.h"
#include "state.h"

class DataManager
{
public:
    DataManager(Ui::ConfigWindow* ui);

    static std::vector<State> statesListInfo;

    void addProperty();
    void removeProperty();
    void addState(State s);
    void removeState(uint id);

    void removeTransitionsToState(int id);

private:
    Ui::ConfigWindow* ui;
};

#endif // GUIMANAGER_H
