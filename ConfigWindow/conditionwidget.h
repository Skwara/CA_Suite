#ifndef CONDITIONW_H
#define CONDITIONW_H

#include <QWidget>

namespace Ui {
class ConditionWidget;
}

class ConditionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ConditionWidget(QWidget *parent = 0);
    ~ConditionWidget();

private:
    Ui::ConditionWidget *ui;
};

#endif // CONDITIONW_H
