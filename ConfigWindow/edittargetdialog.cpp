#include "edittargetdialog.h"
#include "ui_edittargetdialog.h"

#define DATAMAN dataMan

EditTargetDialog::EditTargetDialog(uint stateNr, uint transitionNr, DataManager* dm, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditTargetDialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);

    dataMan = dm;
    this->stateNr = stateNr;
    this->transitionNr = transitionNr;

    QFormLayout* layout_scrollArea = new QFormLayout();
    ui->scrollArea->setLayout(layout_scrollArea);

    for (uint i = 0; i < dataMan->names.size(); ++i) {
        QLineEdit* name = new QLineEdit();
        QDoubleSpinBox* value = new QDoubleSpinBox();
        name->setFixedWidth(120);
        value->setFixedWidth(70);
        name->setPlaceholderText(QString(dataMan->names[i].c_str()));
        name->setReadOnly(true);
        value->setMinimum(-999);
        value->setMaximum(999);
        connect(value, SIGNAL(valueChanged(double)), this, SLOT(valueChanged(double)));

        layout_scrollArea->addRow(name, value);
    }
}

EditTargetDialog::~EditTargetDialog()
{
    delete ui;
}

void EditTargetDialog::valueChanged(double value)
{
    //TODO changes w kazdym transition musza sie dodawac i usuwac w tym samym momencie, w ktorym dodawane i usuwane sa names
    //oraz przy dodawaniu nowego transition trzeba uzupelnic go o changes
    for (uint i = 0; i < DATAMAN->names.size(); ++i) {
        if ((QDoubleSpinBox*)sender() == ui->scrollArea->layout()->itemAt(2*i+1)->widget()) {
            std::vector<double>* changes = (std::vector<double>*)&(DATAMAN->statesListInfo[stateNr].transitions[transitionNr].changes);
            changes->at(i) = value;
            break;
        }
    }
}
