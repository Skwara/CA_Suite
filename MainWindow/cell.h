#ifndef CELL_H
#define CELL_H

#include <QLabel>

class Cell : public QLabel
{
Q_OBJECT
public:
    uint row, col;
    uint stateId, nextStateId;
    std::vector<double> values;
    std::vector<double> nextValues;

    Cell( uint row, uint col, QWidget * parent = 0 );
    ~Cell(){}

    void setColor(uint r, uint g, uint b);

protected:
    void mousePressEvent( QMouseEvent * event );

private:

    void clicked();
};

#endif // CELL_H
