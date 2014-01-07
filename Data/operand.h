#ifndef OPERAND_H
#define OPERAND_H

#include <iostream>

enum Relation {
    oneToOne,
    sum,
    average
};

class Operand
{
public:
    Operand();
    bool neighbours[3][3];
    int additionalNeighbours;
    int field;
    Relation relation;
    bool matchAll;
};

#endif // OPERAND_H
