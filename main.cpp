#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

// zalozylem ze id jest unikatowe i stale, usuwac mozna (stan) np jeden ost, bo zmienic jeden wewnatrz jest jak stworzyc nowy
// miales racje zeby nie trzymac wartosci w liscie par, tylko w listach jednoelemtnowych [nieoptymalne zuzycie pamieci na kopiowanie nazw pol i irytujaca psrawa z apsiem]
