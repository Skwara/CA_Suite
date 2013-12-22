#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <vector>
#include <utility>

#include <QColor>

class State
{
public:
    State();

    int id;
    std::string name;
    QColor color;
    std::vector<double> values;
    //List<Transition> transitions;
};

#endif // STATE_H
