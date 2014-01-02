#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

// mozna by zmienic ramke na domyslne tlo, wtedy wygladaloby jakby byl wcisniety, analogiczny efekt jest dla czarnego klacka z biala ramka
// moze byc problem z serializacja vectorow, mozna by recznie ja zdefiniowac, np przepisac do listy
