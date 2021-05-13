#include "widget_modelset.h"
#include "ui_widget_modelset.h"

widget_modelset::widget_modelset(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widget_modelset)
{
    ui->setupUi(this);

    std::srand(QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0);

    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                    QCP::iSelectLegend | QCP::iSelectPlottables);
    ui->customPlot->xAxis->setRange(-1000, 1000);
    ui->customPlot->yAxis->setRange(-1000, 1000);
    ui->customPlot->axisRect()->setupFullAxesBox();

    ui->customPlot->xAxis->setLabel("x, m");
    ui->customPlot->yAxis->setLabel("y, m");

}

widget_modelset::~widget_modelset()
{
    delete ui;
}
