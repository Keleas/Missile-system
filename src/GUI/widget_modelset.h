#ifndef WIDGET_MODELSET_H
#define WIDGET_MODELSET_H

#include <QWidget>
#include "qcustomplot.h"

namespace Ui {
class widget_modelset;
}

class widget_modelset : public QWidget
{
    Q_OBJECT

public:
    explicit widget_modelset(QWidget *parent = nullptr);
    ~widget_modelset();

private:
    Ui::widget_modelset *ui;
};

#endif // WIDGET_MODELSET_H
