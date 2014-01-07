#include "engine.h"

Engine::Engine() {

}

Engine::Engine(DataManager *dm)
{
    dataMan = dm;
}

// przygotowywuje przyszly stan
void Engine::prepareNextState(Cell *cell) {
    foreach (Transition tran, dataMan->statesListInfo[cell->stateId].transitions) {
        if ( transition(tran, *cell) ) { // nie daje lgowy ze przez *
            cell->nextStateId = tran.targetStateId;
            prepareNextValues(cell, tran);
            break;
        }
    }
}

// sprawdza czy przejscie zachodzi
bool Engine::transition(const Transition& transition, const Cell &cell) {
    for (uint i = 0; i < transition.conditions.size(); ++i) {
        // dla kazdej mozliwej kombinacji sasiadow jednego warunku
        if (checkCombinationsOfConditions(cell, transition.conditions[i]) ) { //TODO
            // nie przekazuje nigdzie sasiadow, nei trzymam nigdzie sasiadow, trzeba przez to sie dobrac ich wartosci danwgo pola i jego wlasnego rowniez
            if (transition.isConjunction) {
                 // jesli jest koniunkcja musi spelnic wszystkie warunki
                 if ( i < (transition.conditions.size() - 1)) {
                    continue;
                 } else {
                    return true;
                 }
            } else {
            // jesli nie, to przejscie (transition) jest prawdziwe
                return true;
            }
        }
    }
    return false;
}

// sprawdza wszystki mozliwe kombinacje warunkow, zalezne od ilosci dobieranych sasiadow (additionalNeighbours)
bool Engine::checkCombinationsOfConditions(const Cell &cell, const Condition &condition) {
    // TODO
    // z teog nizej bd funkcja, bo bd to samo dla lewego i prawego
    bool leftNeighbours[3][3];
//    leftNeighbours = condition.leftOperand.neighbours; // to robi kopie, nie?
    //bool rightNeighbours = condition.rightOperand.neighbours;

    std::vector<bool*> additionalNeighbours;
    // tworzenie listy mozliwych do wyboru sasiadow
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            if (!leftNeighbours[i][j]) {
                additionalNeighbours.push_back(&leftNeighbours[i][j]);
            }
        }
    }
    // ustawianie stanu poczatkowego listy
    for (int i = 0; i < condition.leftOperand.additionalNeighbours; ++i) {
        *additionalNeighbours[i] = true;
    }
  //  nextCombination();
 //   nextValues();
    return true;
}

// zwraca nastepna kombinacje wartosci
void Engine::nextCombination(bool* additionalNeighbours, int additionalNeighboursLength) {

}

// na podstawie sasiadow tworzy liste ich wartosci
std::vector<double> Engine::nextValues(bool neighbours[3][3], int field, const Cell &cell) {
    std::vector<double> vector;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            if (neighbours) {
                vector.push_back(cell.values[field]);
            }
        }
    }
    return vector;
}

// sprawdza, czy dla podanych wartosci (pobranych juz z pol wybranych sasiadow) warunek jest prawdziwy
bool Engine::checkCondition(const std::vector<double> &leftValues, Relation leftRelation,
                            const std::vector<double> &rightValues, Relation rightRelation, Sign sign) {
    switch (sign) {
    case lower:
        // zwraca liste, gdyz w porownaniu 1-1 porownuje liste wartosci, a jedna wartosc dla sumy, czy sredniej,
        // dalej moze byc przetrzymywana w liscie
        foreach (double leftValue, calculateValues(leftValues, leftRelation)) {
            foreach (double rightValue, calculateValues(rightValues, rightRelation)) {
                if (! leftValue < rightValue ){
                    return false;
                }
            }
        }
        break;
    case lowerEqual:
        foreach (double leftValue, calculateValues(leftValues, leftRelation)) {
            foreach (double rightValue, calculateValues(rightValues, rightRelation)) {
                if (! leftValue <= rightValue ){
                    return false;
                }
            }
        }
        break;
    case equal:
        foreach (double leftValue, calculateValues(leftValues, leftRelation)) {
            foreach (double rightValue, calculateValues(rightValues, rightRelation)) {
                if (! leftValue == rightValue ){
                    return false;
                }
            }
        }
        break;
    case greater:
        foreach (double leftValue, calculateValues(leftValues, leftRelation)) {
            foreach (double rightValue, calculateValues(rightValues, rightRelation)) {
                if (! leftValue > rightValue ){
                    return false;
                }
            }
        }
        break;
    case greaterEqual:
        foreach (double leftValue, calculateValues(leftValues, leftRelation)) {
            foreach (double rightValue, calculateValues(rightValues, rightRelation)) {
                if (! leftValue >= rightValue ){
                    return false;
                }
            }
        }
        break;
    default:
        break;
    }
    return true;
}

// zwraca liste wartosci dla danej relacji miedzy wartosciami
std::vector<double> Engine::calculateValues(const std::vector<double> &values, Relation relation) {
    std::vector<double> vector;
    double s = 0.0;
    switch (relation) {
    case oneToOne:
        foreach (double d, values) {
            vector.push_back(d); // moze return values; ??
        }
        break;
    case sum:
        foreach (double d, values) {
            s = s + d;
        }
        vector.push_back(s);
        break;
    case average:
        foreach (double d, values) {
            s = s + d;
        }
        vector.push_back(s / values.size());
        break;
    default:
        break;
    }
    return vector;
}

// przygotowywuje przyszle wartosci, na podstawie zmian zadeklarowanych w edycji celu (edit target)
void Engine::prepareNextValues(Cell* cell, const Transition &transition) {

}
