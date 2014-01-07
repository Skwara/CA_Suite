#include "datamanager.h"

std::vector<State> DataManager::statesListInfo;

DataManager::DataManager(Ui::ConfigWindow* ui)
{
    this->ui = ui;
}

void DataManager::addProperty()
{
    //dla kazdego stanu dodaj wartosc 0
    for (uint i = 0; i < statesListInfo.size(); ++i) {
        statesListInfo[i].values.push_back(0);
    }
}

void DataManager::removeProperty()
{
    for (unsigned i = 0; i < statesListInfo.size(); i++) {
        if (!statesListInfo[i].values.empty()) { //TODO niekoniecznie potrzebny if, jesli fieldsList i statesListInfo dzialaja rownolegle
            statesListInfo[i].values.pop_back();
        }
    }
}

void DataManager::addState(State s)
{
    statesListInfo.push_back(s);
}

void DataManager::removeState(uint id)
{
    if (id < statesListInfo.size()) {
        statesListInfo.erase(statesListInfo.begin()+id);
        for (uint i = id; i < statesListInfo.size(); ++i) {
            statesListInfo[i].id--;
        }
    }
}

void DataManager::removeTransitionsToState(int id) {
    for (uint i = 0; i < statesListInfo.size(); ++i) {
        for (int j = statesListInfo[i].transitions.size() - 1; j >= 0; --j) {
            if (statesListInfo[i].transitions[j].targetStateId == id) {
                statesListInfo[i].transitions.erase(statesListInfo[i].transitions.begin() + j);
            }
        }
    }
}

void DataManager::saveData()
{

}

void DataManager::loadData()
{

}
