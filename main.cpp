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

// CO TRZEBA JESZCZE ZROBIC

// - priorytety targetow
// - stala w warunku
// - wplyw zmiany typu sasiadow, na widoczosc sasiadow -> mysle zeby zrobic narazie jeden typ sasiedztwa
// - podpiac spinbox z dodawaniem stalej


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
