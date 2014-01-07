#ifndef CONDITION_H
#define CONDITION_H

#include <iostream>
#include "operand.h"

enum Sign {
    greater,
    greaterEqual,
    equal,
    lower,
    lowerEqual
};

class Condition
{
public:
    Condition();
    Operand leftOperand;
    Operand rightOperand;
    Sign conditionSign; //enum
};

#endif // CONDITION_H
