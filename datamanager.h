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

enum Neighbourhood {
    Neumann,
    Moore
};

class DataManager
{
public:
    DataManager();

    //static std::vector<State> statesListInfo;
    std::vector<State> statesListInfo;
    std::vector<std::string> names;
    Neighbourhood neighbourhood;
    uint boardWidth;
    uint boardHeight;
    uint cellSize;


    void addProperty(std::string name);
    void removeProperty();
    void addState(State s);
    void removeState(uint id);
    void addCondition(uint state, uint transition, QWidget* parent);
    void removeCondition(uint stateNr, uint transitionNr, uint conditionNr);
    void addTransition(uint state, uint transition);
    void removeTransition(uint state, uint transition);

    void removeTransitionsToState(int id);

    void saveData();
    void loadData();

};

#endif // GUIMANAGER_H
