#include "cell.h"

DataManager* Cell::dataMan;

Cell::Cell() {
}

Cell::Cell(uint row, uint col, QWidget * parent ) :
    QLabel(parent)
{
    stateId = 0;
    this->row = row;
    this->col = col;
    uint cellSize = dataMan->cellSize;
    setMinimumHeight(cellSize);
    setMinimumWidth(cellSize);
    setMaximumHeight(cellSize);
    setMaximumWidth(cellSize);
    QColor color = dataMan->statesListInfo[stateId].color;
    setColor(color.red(), color.green(), color.blue());
}

void Cell::setColor(uint r, uint g, uint b)
{
    this->setStyleSheet(QString("background-color: rgb( %1, %2, %3); border: 1px solid #C0C0C0").arg(r).arg(g).arg(b));
}

void Cell::mousePressEvent ( QMouseEvent * event )
{
    clicked();
}

void Cell::clicked()
{

    ++stateId;
    if (stateId >= dataMan->statesListInfo.size()) {
        stateId = 0;
    }
    QColor color = dataMan->statesListInfo[stateId].color;
    setColor(color.red(), color.green(), color.blue());
}

void Cell::addNeighbours(const std::vector< std::vector<Cell*> >& cells) {
    bool isLeft = true;
    bool isRight = true;
    bool isTop = true;
    bool isBottom = true;
    if (row == 0) isTop = false;
    if (row == cells.size() - 1) isBottom = false;
    if (col == 0) isLeft = false;
    if (col == cells[0].size() - 1) isRight = false;

    switch (dataMan->neighbourhood) {
    case Neumann:
        neighbours.push_back(0);
        if (isTop) {
            neighbours.push_back(cells[row - 1][col]);
        }else{
            neighbours.push_back(0);
        }
        neighbours.push_back(0);
        if (isLeft) {
            neighbours.push_back(cells[row][col - 1]);
        }else{
            neighbours.push_back(0);
        }
        neighbours.push_back(cells[row][col]);
        if (isRight) {
            neighbours.push_back(cells[row][col + 1]);
        }else{
            neighbours.push_back(0);
        }
        neighbours.push_back(0);
        if (isBottom) {
            neighbours.push_back(cells[row + 1][col]);
        }else{
            neighbours.push_back(0);
        }
        neighbours.push_back(0);
        break;
    case Moore:
        if (isTop) {
            if (isLeft) {
                neighbours.push_back(cells[row - 1][col - 1]);
            }else{
                neighbours.push_back(0);
            }
            neighbours.push_back(cells[row - 1][col]);
            if (isRight) {
                neighbours.push_back(cells[row - 1][col + 1]);
            }else{
                neighbours.push_back(0);
            }
        }else{
            neighbours.push_back(0);
            neighbours.push_back(0);
            neighbours.push_back(0);
        }

        if (isLeft) {
            neighbours.push_back(cells[row][col - 1]);
        }else{
            neighbours.push_back(0);
        }
        neighbours.push_back(cells[row][col]);
        if (isRight) {
            neighbours.push_back(cells[row][col + 1]);
        }else{
            neighbours.push_back(0);
        }

        if (isBottom) {
            if (isLeft) {
                neighbours.push_back(cells[row + 1][col - 1]);
            }else{
                neighbours.push_back(0);
            }
            neighbours.push_back(cells[row + 1][col]);
            if (isRight) {
                neighbours.push_back(cells[row + 1][col + 1]);
            }
        }else{
            neighbours.push_back(0);
            neighbours.push_back(0);
            neighbours.push_back(0);
        }
        break;
    default:
        break;
    }
}

void Cell::setNextState() {
    if (stateId != nextStateId) {
        stateId = nextStateId;
        QColor color = dataMan->statesListInfo[stateId].color;
        setColor(color.red(), color.green(), color.blue());
    }
    values = nextValues;

}
