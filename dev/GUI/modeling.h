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
//  void titleDoubleClick(QMouseEvent *event);
//  void axisLabelDoubleClick(QCPAxis* axis, QCPAxis::SelectablePart part);
//  void legendDoubleClick(QCPLegend* legend, QCPAbstractLegendItem* item);
//  void selectionChanged();
//  void mousePress();
  void mouseWheel();
//  void addRandomGraph();
//  void removeSelectedGraph();
//  void removeAllGraphs();
//  void contextMenuRequest(QPoint pos);
//  void moveLegend();
//  void graphClicked(QCPAbstractPlottable *plottable, int dataIndex);

private:
    Ui::modeling *ui;
};

#endif // MODELING_H
