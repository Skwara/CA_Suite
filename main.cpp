#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

// TODO przekazuje inta z listy pol!! [fieldow] wiec:
    // dopisalbym do listy fieldow na starcie id, mozna by tam je w ogole trzymac, uprosci to obliczenia
// mozna by zmienic ramke na domyslne tlo, wtedy wygladaloby jakby byl wcisniety, analogiczny efekt jest dla czarnego klacka z biala ramka
// moze byc problem z serializacja vectorow, mozna by recznie ja zdefiniowac, np przepisac do listy
