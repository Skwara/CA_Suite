#ifndef CONFIGWINDOW_H
#define CONFIGWINDOW_H

#include <QDialog>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QFormLayout>
#include <QGridLayout>
#include <QApplication>

#include <vector>
#include <utility>

#include "state.h"

#define FONT_COLOR_THRESHOLD 250
#define STATE_SHAPE_SIZE 60

namespace Ui {
class ConfigWindow;
}

class ConfigWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigWindow(QWidget *parent = 0);
    ~ConfigWindow();

private slots:
    void on_button_addProp_clicked();

    void on_slider_R_valueChanged(int value);
    void on_slider_G_valueChanged(int value);
    void on_slider_B_valueChanged(int value);

    void on_button_addState_clicked();
    void stateButtonAction_clicked();
    void saveButtonAction_clicked();


    void on_button_removeProp_clicked();

    void on_button_removeState_clicked();

private:
    Ui::ConfigWindow *ui;

    QFormLayout* layout_fields;
    QVBoxLayout* layout_states;

    std::vector< std::pair<QLineEdit*, QDoubleSpinBox*> > fieldsList;
    std::vector<QPushButton*> statesList;
    std::vector<State> statesListInfo;

    void setColorLabel(int r, int g, int b);
    void savePushButtonColor(QPushButton* pb, int r, int g, int b);
    void activePushButton(QPushButton* stateButton, bool active);
    void addStateToLayout(QPushButton* stateButton);
    State getCurrentState();
    void setDefaultState();
    void resizeEvent(QResizeEvent* event);

};

#endif // CONFIGWINDOW_H
