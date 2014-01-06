#include "cell.h"

Cell::Cell(uint row, uint col, QWidget * parent ) :
    QLabel(parent)
{
    this->row = row;
    this->col = col;
}

void Cell::mousePressEvent ( QMouseEvent * event )
{
    clicked();
}

void Cell::clicked()
{

}
