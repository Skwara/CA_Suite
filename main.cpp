#include "mainwindow.h"
#include <QApplication>

#include <engine.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();

}

// nie ma malego matcha z operandow, koncze pisac funkcje od kombinacji

// mozna by zmienic ramke na domyslne tlo, wtedy wygladaloby jakby byl wcisniety, analogiczny efekt jest dla czarnego klacka z biala ramka

// CO TRZEBA JESZCZE ZROBIC

// !!! - dodac sasiadow, metoda addNeighbours z Cell wywoluje sie przy paintcie w mainWindow

// - priorytety targetow
// - stala w warunku
// - wplyw zmiany typu sasiadow, na widoczosc sasiadow -> mysle zeby zrobic narazie jeden typ sasiedztwa
// - okno edycji targetow mozna minimalizowac
// - jak chcemy dynamiczna zmiane wartosci, to mysle, ze najlepiej byloby sprawdzac co iteracje czy jakas zmienna w configwindow
//      sie zmienila na true, jesli tak, to mozna by zastapic stary dm nowym, a do tego trzebaby bylo przekazywac kopie dm
//      do mainWindow i cellow, narazie zrobilem na referncji

// test kombinacji
//    bool b[3][3];
//    for (int i = 0; i < 3; ++i) {
//        for (int j = 0; j < 3; ++j) {
//            b[i][j] = false;
//        }
//    }
//    b[1][2] = true;

//    std::vector<bool*> posibleN;
//    for (int i = 0; i < 3; ++i) {
//        for (int j = 0; j < 3; ++j) {
//            if (!b[i][j]) {
//                posibleN.push_back(&b[i][j]);
//            }
//        }
//    }
//    *posibleN[0] = true;
//    *posibleN[1] = true;

//    Engine e;

//    for (int i = 0; i < 3; ++i) {
//        for (int j = 0; j < 3; ++j) {
//            std::cout << b[i][j] << " ";
//        }
//        std::cout << std::endl;
//    }

//    foreach (bool* v, posibleN) {
//        std::cout << *v << " ";
//    }
//    std::cout << std::endl;

//    while (e.nextCombination(posibleN)) {
//        for (int i = 0; i < 3; ++i) {
//            for (int j = 0; j < 3; ++j) {
//                std::cout << b[i][j] << " ";
//            }
//            std::cout << std::endl;
//        }
////        foreach (bool* v, posibleN) {
////            std::cout << *v << " ";
////        }
//        std::cout << std::endl;
//    }
