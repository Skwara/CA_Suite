#include "cell.h"

Cell::Cell(uint row, uint col, QWidget * parent ) :
    QLabel(parent)
{
    this->row = row;
    this->col = col;
    setMinimumHeight(20);
    setMinimumWidth(20);
    setMaximumHeight(20);
    setMaximumWidth(20);
}

void Cell::setColor(uint r, uint g, uint b)
{
    this->setStyleSheet(QString("background-color: rgb( %1, %2, %3); border: 1px solid #000000").arg(r).arg(g).arg(b));
}

void Cell::mousePressEvent ( QMouseEvent * event )
{
    clicked();
}

void Cell::clicked()
{

}
