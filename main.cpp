#include "mainwindow.h"
#include <QApplication>

#include <engine.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();

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

}

// nie ma malego matcha z operandow, koncze pisac funkcje od kombinacji

// mozna by zmienic ramke na domyslne tlo, wtedy wygladaloby jakby byl wcisniety, analogiczny efekt jest dla czarnego klacka z biala ramka
// moze byc problem z serializacja vectorow, mozna by recznie ja zdefiniowac, np przepisac do listy
