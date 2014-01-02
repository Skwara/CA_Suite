#ifndef CONDITION_H
#define CONDITION_H

#include <iostream>
#include "operand.h"

class Condition
{
public:
    Condition();
    Operand leftOperand;
    Operand rightOperand;
    std::string conditionSign; //enum
};

#endif // CONDITION_H
