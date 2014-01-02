#ifndef TRANSITION_H
#define TRANSITION_H

#include <vector>
#include "condition.h"

class Transition
{
public:
    Transition();

    int targetStateId;
    bool isConjunction;
    std::vector<Condition> conditions;
};

#endif // TRANSITION_H
