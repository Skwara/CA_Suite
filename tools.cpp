#include "tools.h"

#define STATE_SHAPE_SIZE 60
#define FONT_COLOR_THRESHOLD 250

Tools::Tools()
{
}

QPushButton* Tools::createStateButton(State s) {
    QPushButton* stateButton = new QPushButton( QString("%1").arg(s.id) );

    savePushButtonColor(stateButton, s.color.red(), s.color.green(), s.color.blue());

    stateButton->setMinimumHeight(STATE_SHAPE_SIZE);
    stateButton->setMaximumHeight(STATE_SHAPE_SIZE);
    stateButton->setMinimumWidth(STATE_SHAPE_SIZE);
    stateButton->setMaximumWidth(STATE_SHAPE_SIZE);

    return stateButton;
}

// ustawienie koloru tla i czcionki dla przyciskow stanu
void Tools::savePushButtonColor(QPushButton* stateButton, int r, int g, int b) {
    if (r + b + g < FONT_COLOR_THRESHOLD) {
        stateButton->setStyleSheet( QString("background-color: rgb( %1,%2,%3 ); color: rgb(255, 255, 255); border: 0px").arg(r).arg(g).arg(b) );
    } else {
        stateButton->setStyleSheet( QString("background-color: rgb( %1,%2,%3 ); border: 0px").arg(r).arg(g).arg(b) );
    }
}

void Tools::activePushButton(QPushButton* stateButton, bool active) {
    int r = stateButton->palette().background().color().red();
    int g = stateButton->palette().background().color().green();
    int b = stateButton->palette().background().color().blue();
    if (active) {
        if (r + g + b < FONT_COLOR_THRESHOLD) {
            stateButton->setStyleSheet(QString("background-color: rgb( %1,%2,%3 ); color: rgb(255, 255, 255); border: 2px solid #C0C0C0").arg(r).arg(g).arg(b));
        } else {
            stateButton->setStyleSheet(QString("background-color: rgb( %1,%2,%3 ); border: 2px solid #C0C0C0").arg(r).arg(g).arg(b));
        }
    } else {
        savePushButtonColor(stateButton, r, g, b);
    }
}
// usuwa button z listy state'ow, przesuwa idki
void Tools::removeStateButton(std::vector<QPushButton*>& buttonsList, uint removedStateId) {
    if (removedStateId < buttonsList.size()) {
        delete buttonsList[removedStateId];
        buttonsList.erase(buttonsList.begin()+removedStateId);
        for (uint i = removedStateId; i < buttonsList.size(); ++i) {
            buttonsList[i]->setText( QString("%1").arg(i) );
        }
    }
}
