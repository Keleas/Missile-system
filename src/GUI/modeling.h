#ifndef MODELING_H
#define MODELING_H

#include <QWidget>
#include <QInputDialog>
#include "qcustomplot.h"

namespace Ui {
class modeling;
}

class modeling : public QWidget
{
    Q_OBJECT

public:
    explicit modeling(QWidget *parent = 0);
    ~modeling();

private slots:


private:
    Ui::modeling *ui;
};

#endif // MODELING_H
