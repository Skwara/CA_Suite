#include "datamanager.h"

std::vector<State> DataManager::statesListInfo;

DataManager::DataManager()
{
}

void DataManager::addProperty(std::string name)
{
    //dla kazdego stanu dodaj wartosc 0
    for (uint i = 0; i < statesListInfo.size(); ++i) {
        names.push_back(name);
        statesListInfo[i].values.push_back(0);
        for (uint j = 0; j < statesListInfo[i].transitions.size(); ++j) {
            statesListInfo[i].transitions[j].changes.push_back(0);
        }
    }
}

void DataManager::removeProperty()
{
    for (unsigned i = 0; i < statesListInfo.size(); i++) {
        if (!statesListInfo[i].values.empty()) { //TODO niekoniecznie potrzebny if, jesli fieldsList i statesListInfo dzialaja rownolegle
            names.pop_back();
            statesListInfo[i].values.pop_back();
            for (uint j = 0; j < statesListInfo[i].transitions.size(); ++j) {
                statesListInfo[i].transitions[j].changes.pop_back();
            }
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

void DataManager::addCondition(uint state, uint transition, QWidget* parent)
{

}

void DataManager::removeCondition(uint stateNr, uint transitionNr, uint conditionNr)
{
    std::vector<Condition>* conditionsPtr = (std::vector<Condition>*)&(statesListInfo[stateNr].transitions[transitionNr].conditions);
    conditionsPtr->erase(conditionsPtr->begin() + conditionNr);
}

void DataManager::addTransition(uint state, uint transition)
{
    Transition t;
    t.targetStateId = transition;
    t.applyChanges = false;
    for (uint i = 0; i < names.size(); ++i) {
        t.changes.push_back(0);
    }
    statesListInfo[state].transitions.push_back(t);
}
void DataManager::removeTransition(uint state, uint transition)
{
    statesListInfo[state].transitions.erase(statesListInfo[state].transitions.begin() + transition);
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
