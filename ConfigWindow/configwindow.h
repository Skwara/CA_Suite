#ifndef CONFIGWINDOW_H
#define CONFIGWINDOW_H

#include <QDialog>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QFormLayout>
#include <QGridLayout>
#include <QApplication>
#include <QSpinBox>
#include <QComboBox>
#include <QCheckBox>

#include <vector>
#include <utility>

#include "state.h"
#include "transition.h"
#include "operand.h"
#include "condition.h"
#include "tools.h"

namespace Ui {
class ConfigWindow;
}

class ConfigWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigWindow(QWidget *parent = 0);
    ~ConfigWindow();

    static std::vector<State> statesListInfo;

private slots:

private:
    Ui::ConfigWindow *ui;
};

#endif // CONFIGWINDOW_H
