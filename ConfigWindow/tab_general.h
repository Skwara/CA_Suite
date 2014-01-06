#ifndef TAB_GENERAL_H
#define TAB_GENERAL_H

#include <QWidget>

namespace Ui {
class Tab_General;
}

class Tab_General : public QWidget
{
    Q_OBJECT

public:
    explicit Tab_General(QWidget *parent = 0);
    ~Tab_General();

private:
    Ui::Tab_General *ui;
};

#endif // TAB_GENERAL_H
