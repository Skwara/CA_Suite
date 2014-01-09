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
    this->setStyleSheet(QString("background-color: rgb( %1, %2, %3); border: 1px solid #000000").arg(r).arg(g).arg(b));
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

// TODO
void Cell::addNeighbours(const std::vector< std::vector<Cell*> >& cells) {
    switch (dataMan->neighbourhood) {
    case Neumann:
//        neighbours.push_back(0); // i - 1; j - 1
//        neighbours.push_back(cells[row - 1][col]);
//        neighbours.push_back(0); // i - 1; j + 1
//        neighbours.push_back(cells[row][col - 1]);
//        neighbours.push_back(cells[row][col]);
//        neighbours.push_back(cells[row][col + 1]);
//        neighbours.push_back(0);
//        neighbours.push_back(cells[row + 1][col]);
//        neighbours.push_back(0);
        break;
    case Moore:
        neighbours.push_back(cells[row - 1][col - 1]);
        neighbours.push_back(cells[row - 1][col]);
        neighbours.push_back(cells[row - 1][col + 1]);
        neighbours.push_back(cells[row][col - 1]);
        neighbours.push_back(cells[row][col]);
        neighbours.push_back(cells[row][col + 1]);
        neighbours.push_back(cells[row + 1][col - 1]);
        neighbours.push_back(cells[row + 1][col]);
        neighbours.push_back(cells[row + 1][col + 1]);;
        break;
    default:
        break;
    }
}
