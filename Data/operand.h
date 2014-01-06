#ifndef OPERAND_H
#define OPERAND_H

#include <iostream>

class Operand
{
public:
    Operand();
    bool neighbours[3][3];
    int additionalNeighbours;
    std::string field;
    std::string relation;
    bool matchAll;
};

#endif // OPERAND_H
