#ifndef ENGINE_H
#define ENGINE_H

#include "datamanager.h"
#include "state.h"
#include "transition.h"
#include "condition.h"
#include "operand.h"
#include "cell.h"

class Engine
{
public:
    Engine();
    Engine(DataManager* dm);

    void start(std::vector< std::vector<Cell*> > cells);
private:
    DataManager* dataMan;

    void prepareNextState(Cell *cell);
    bool transition(const Transition &transition, const Cell &cell);
    bool checkCombinationsOfConditions(const Cell &cell, const Condition &condition);
    std::vector<bool*> getPossibleNeighboursVector(bool neighbours[3][3], int additionalNeighbours);
    bool nextCombination(std::vector<bool*> additionalNeighbours);
    std::vector<double> nextValues(bool neighbours[3][3], int field, const Cell &cell);
    bool checkCondition(const std::vector<double> &leftValues, Relation leftRelation,
                                const std::vector<double> &rightValues, Relation rightRelation, Sign sign);
    std::vector<double> calculateValues(const std::vector<double> &values, Relation relation);
    void prepareNextValues(Cell* cell, const Transition &transition);
};

#endif // ENGINE_H
