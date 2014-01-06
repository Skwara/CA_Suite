#ifndef STATE_H
#define STATE_H

#include <vector>

#include <QColor>

#include "transition.h"

class State
{
public:
    State();

    int id;
    std::string name;
    QColor color;
    std::vector<double> values;
    std::vector<Transition> transitions;
};

#endif // STATE_H
