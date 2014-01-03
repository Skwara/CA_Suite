#ifndef TOOLS_H
#define TOOLS_H

#include <QPushButton>

#include <vector>

#include "state.h"

class Tools
{
public:
    Tools();

    static QPushButton* createStateButton(State s);
    static void savePushButtonColor(QPushButton* pb, int r, int g, int b);
    static void activePushButton(QPushButton* stateButton, bool active);
    static void removeStateButton(std::vector<QPushButton*>& buttonsList, int removedStateId);
};

#endif // TOOLS_H
