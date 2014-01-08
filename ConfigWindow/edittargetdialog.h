#ifndef EDITTARGETDIALOG_H
#define EDITTARGETDIALOG_H

#include <QDialog>
#include <QFormLayout>

#include "datamanager.h"

namespace Ui {
class EditTargetDialog;
}

class EditTargetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditTargetDialog(uint stateNr, uint transitionNr, DataManager* dm, QWidget *parent = 0);
    ~EditTargetDialog();

private slots:
    void valueChanged(double value);

private:
    Ui::EditTargetDialog *ui;
    DataManager* dataMan;

    uint stateNr, transitionNr;
};

#endif // EDITTARGETDIALOG_H
