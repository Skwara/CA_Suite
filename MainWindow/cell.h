#ifndef CELL_H
#define CELL_H

#include <QLabel>

#include "datamanager.h"

class Cell : public QLabel
{
Q_OBJECT
public:
    static DataManager* dataMan;

    uint row, col;
    uint stateId, nextStateId;
    std::vector<double> values;
    std::vector<double> nextValues;
    std::vector<Cell*> neighbours;

    Cell();
    Cell( uint row, uint col, QWidget * parent = 0 );
    ~Cell(){}

    void setColor(uint r, uint g, uint b);
    void addNeighbours(const std::vector<std::vector<Cell *> > &cells);
    void setNextState();

protected:
    void mousePressEvent( QMouseEvent * event );

private:
    void clicked();
};

#endif // CELL_H
