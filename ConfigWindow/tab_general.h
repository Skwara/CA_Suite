#ifndef TAB_GENERAL_H
#define TAB_GENERAL_H

#include <QWidget>

#include "datamanager.h"

namespace Ui {
class Tab_General;
}

class Tab_General : public QWidget
{
    Q_OBJECT

public:
    explicit Tab_General(DataManager *dm, QWidget *parent = 0);
    ~Tab_General();

private slots:
    void on_spinBox_boardWidth_valueChanged(int arg1);
    void on_spinBox_boardHeight_valueChanged(int arg1);
    void on_radioButton_Neumann_pressed();

    void on_radioButton_Moore_pressed();

    void on_pushButton_save_clicked();

    void on_pushButton_load_clicked();

private:
    Ui::Tab_General *ui;
    DataManager* dataMan;
};

#endif // TAB_GENERAL_H
