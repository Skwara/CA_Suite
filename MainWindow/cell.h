#ifndef CELL_H
#define CELL_H

#include <QLabel>

class Cell : public QLabel
{
Q_OBJECT
public:
    Cell( uint row, uint col, QWidget * parent = 0 );
    ~Cell(){}

protected:
    void mousePressEvent( QMouseEvent * event );

private:
    uint row, col;

    void clicked();
};

#endif // CELL_H
