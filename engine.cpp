#include "engine.h"

Engine::Engine() {

}

Engine::Engine(DataManager *dm)
{
    dataMan = dm;
}

void Engine::start(std::vector<std::vector<Cell *> > cells) {
    for (uint i = 0; i < cells.size(); ++i) {
        for (uint j = 0; j < cells[0].size(); ++j) {
            prepareNextState(cells[i][j]);
        }
    }
    for (uint i = 0; i < cells.size(); ++i) {
        for (uint j = 0; j < cells[0].size(); ++j) {
            cells[i][j]->setNextState();
        }
    }
}

// przygotowywuje przyszly stan
void Engine::prepareNextState(Cell* cell) {
//    std::cout << "-------------------------------------------" << std::endl;
//    std::cout << cell->row << "; " << cell->col << std::endl;
    foreach (Transition tran, dataMan->statesListInfo[cell->stateId].transitions) {
        if ( transition(tran, *cell) ) {
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
                 }
            } else {
            // jesli nie, to przejscie (transition) jest prawdziwe
                return true;
            }
        } else {
            if (transition.isConjunction) {
                return false;
            }
        }
    }
    //dla wszystkich prawdziwych
    if (transition.isConjunction) {
        return true;
    } else {
        return false;
    }
}

// sprawdza wszystki mozliwe kombinacje warunkow, zalezne od ilosci dobieranych sasiadow (additionalNeighbours)
bool Engine::checkCombinationsOfConditions(const Cell &cell, const Condition &condition) {

    // tworzenie kopii sasiadow, do pozniejszej edycji
    bool leftNeighbours[3][3];
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            leftNeighbours[i][j] = condition.leftOperand.neighbours[i][j]; // TODO WTF, czemu nei moge po prostu zwrocic?
        }
    }
    std::vector<bool*> possibleLeftNeighbours =
            getPossibleNeighboursVector( leftNeighbours, condition.leftOperand.additionalNeighbours);

    bool rightResult = false;
    bool leftResult = false;
    // petla po mozliwych lewych przypadkach
    do {
        // przygotowanie kopii prawych sasiadow, do pozneijszej edycji
        bool rightNeighbours[3][3];
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                rightNeighbours[i][j] = condition.rightOperand.neighbours[i][j];
            }
        }
        std::vector<bool*> possibleRightNeighbours =
                getPossibleNeighboursVector( rightNeighbours, condition.rightOperand.additionalNeighbours);

        // petla po mozliwych prawych przypadkach
        rightResult = false; // jesli ani razu warunek sie nie sprawdzi, jesli jest matchAny, to szuka do ost warunku
        do {
            if (checkCondition(nextValues(leftNeighbours, condition.leftOperand.field, cell), condition.leftOperand.relation,
                               nextValues(rightNeighbours, condition.rightOperand.field, cell), condition.rightOperand.relation,
                               condition.conditionSign)) {
                if (condition.rightOperand.matchAll) {
                    rightResult = true; // poki warunek nie zwroci falszu, kontynujemy dzialanie podstawianie prawdy
                } else {
                    rightResult = true; // dla match any, przy pierwszej prawdzie konczymy
                    break;
                }
            } else {
                if (condition.rightOperand.matchAll) {
                    rightResult = false; // dla matchAll przy pierwszym falszu konczymy petle
                    break;
                }
            }

            if (rightResult) {
                if (condition.leftOperand.matchAll) {
                    leftResult = true; // poki nie bedzie inaczej
                } else {
                    return true; // jesli dopasowal choc jeden z lewej strony
                }
            } else {
                if (condition.leftOperand.matchAll) {
                    return false; // jesli nie dopasowal choc jednego z lewej strony
                }
            }
        } while (nextCombination(possibleRightNeighbours));
    } while (nextCombination(possibleLeftNeighbours));
    // domyslnie jest falsz, jesli przejdzie wszystkie warunki poprawnie bedzie prawda
    return leftResult;
}

std::vector<bool*> Engine::getPossibleNeighboursVector(bool neighbours[3][3], int additionalNeighbours) {
    std::vector<bool*> possibleNeighbours;
    // tworzenie listy mozliwych do wyboru sasiadow
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (! (neighbours[i][j])) {
                possibleNeighbours.push_back(&neighbours[i][j]);
            }
        }
    }
    // ustawianie stanu poczatkowego listy
    for (int i = 0; i < additionalNeighbours; ++i) { // nie moze byc ich wiecej niz w sumie sasiadow
        *possibleNeighbours[i] = true;
    }
    return possibleNeighbours;
}

// zwraca nastepna kombinacje wartosci
// DZIALA!@#!#!@!# jak cos
bool Engine::nextCombination(std::vector<bool*> additionalNeighbours) {
    bool isLast = false;
    // jesli ostatni = 1, przygotuj sie na jego przesuniecie
    if (*additionalNeighbours[additionalNeighbours.size() - 1]) {
        isLast = true;
    }
    for (int i = additionalNeighbours.size() - 2; i >= 0; --i) {
        // jesli znajdzie pierwszy od lewej = 1
        if (*additionalNeighbours[i]) {
            // zmien go na 0
            *additionalNeighbours[i] = false;
            // jesli nastepny nie jest 1
            if (!(*additionalNeighbours[i + 1])) {
                // ustaw go = 1
                *(additionalNeighbours[(i + 1)]) = true;
                // ustaw ostatni obok pierwszego
                if ( isLast ) {
                    *additionalNeighbours[additionalNeighbours.size() - 1] = false;
                    *(additionalNeighbours[i + 2]) = true;
                }
            } else {
                // jesli nastepny jest = 1, to zakoncz
                return false;
            }
            return true;
        }
    }
    return false;
}

// na podstawie sasiadow tworzy liste ich wartosci
std::vector<double> Engine::nextValues(bool neighbours[3][3], int field, const Cell &cell) {
    std::vector<double> vector;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (neighbours[i][j]) {
                if (cell.neighbours[i*3 + j] != 0) {
                    vector.push_back(cell.neighbours[i*3 + j]->values[field]);
                }
            }
        }
    }
    return vector;
}

// sprawdza, czy dla podanych wartosci (pobranych juz z pol wybranych sasiadow) warunek jest prawdziwy
bool Engine::checkCondition(const std::vector<double> &leftValues, Relation leftRelation,
                            const std::vector<double> &rightValues, Relation rightRelation, Sign sign) {

    std::vector<double> leftValuesVector = calculateValues(leftValues, leftRelation);
    std::vector<double> rightValuesVector = calculateValues(rightValues, rightRelation);
    switch (sign) {
    case lower:
        // zwraca liste, gdyz w porownaniu 1-1 porownuje liste wartosci, a jedna wartosc dla sumy, czy sredniej,
        // dalej moze byc przetrzymywana w liscie
        foreach (double leftValue, leftValuesVector) {
            foreach (double rightValue, rightValuesVector) { // TODO
                if (! (leftValue < rightValue) ){
                    return false;
                }
            }
        }
        break;
    case lowerEqual:
        foreach (double leftValue, leftValuesVector) {
            foreach (double rightValue, rightValuesVector) {
                if (! (leftValue <= rightValue) ){
                    return false;
                }
            }
        }
        break;
    case equal:
        foreach (double leftValue, leftValuesVector) {
            foreach (double rightValue, rightValuesVector) {
                if (! (leftValue == rightValue) ){
                    return false;
                }
            }
        }
        break;
    case greater:
        foreach (double leftValue, leftValuesVector) {
            foreach (double rightValue, rightValuesVector) {
                if (! (leftValue > rightValue) ){
                    return false;
                }
            }
        }
        break;
    case greaterEqual:
        foreach (double leftValue, leftValuesVector) {
            foreach (double rightValue, rightValuesVector) {
                if (! (leftValue >= rightValue) ){
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
    if (transition.applyChanges) {
        for (uint i = 0; i < cell->nextValues.size(); ++i) {
            cell->nextValues[i] = cell->values[i] + transition.changes[i];
        }
    } else {
        for (uint i = 0; i < cell->nextValues.size(); ++i) {
            cell->nextValues[i] = dataMan->statesListInfo[cell->nextStateId].values[i];
        }
    }
}
