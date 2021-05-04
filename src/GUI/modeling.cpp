#include "modeling.h"
#include "ui_modeling.h"

modeling::modeling(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::modeling)
{
    std::srand(QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0);
    ui->setupUi(this);

    ui->customPlot_1->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                    QCP::iSelectLegend | QCP::iSelectPlottables);
    ui->customPlot_1->xAxis->setRange(-1000, 1000);
    ui->customPlot_1->yAxis->setRange(-1000, 1000);
    ui->customPlot_1->axisRect()->setupFullAxesBox();

    ui->customPlot_2->xAxis->setRange(-1000, 1000);
    ui->customPlot_2->yAxis->setRange(-1000, 1000);
    ui->customPlot_2->axisRect()->setupFullAxesBox();

//    ui->customPlot_1->plotLayout()->insertRow(0);
//    QCPTextElement *title = new QCPTextElement(ui->customPlot_1,
//                                               "Interaction Example",
//                                               QFont("sans", 17, QFont::Bold));
//    ui->customPlot_1->plotLayout()->addElement(0, 0, title);

    ui->customPlot_2->xAxis->setLabel("x, m");
    ui->customPlot_2->yAxis->setLabel("y, m");

    ui->customPlot_1->xAxis->setLabel("Дальность, m");
    ui->customPlot_1->yAxis->setLabel("Высота, m");

    //ui->customPlot_1->legend->setVisible(true);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    ui->customPlot_1->legend->setFont(legendFont);
    ui->customPlot_1->legend->setSelectedFont(legendFont);
    ui->customPlot_1->legend->setSelectableParts(QCPLegend::spItems); // legend box shall not be selectable, only legend items

//    addRandomGraph();
//    addRandomGraph();
//    addRandomGraph();
//    addRandomGraph();
//    ui->customPlot->rescaleAxes();

    // connect slot that ties some axis selections together (especially opposite axes):
//    connect(ui->customPlot, SIGNAL(selectionChangedByUser()),
//            this, SLOT(selectionChanged()));
//    // connect slots that takes care that when an axis is selected, only that direction can be dragged and zoomed:
//    connect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)),
//            this, SLOT(mousePress()));
//    connect(ui->customPlot, SIGNAL(mouseWheel(QWheelEvent*)),
//            this, SLOT(mouseWheel()));

//    // make bottom and left axes transfer their ranges to top and right axes:
//    connect(ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)),
//            ui->customPlot->xAxis2, SLOT(setRange(QCPRange)));
//    connect(ui->customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)),
//            ui->customPlot->yAxis2, SLOT(setRange(QCPRange)));

//    // connect some interaction slots:
//    connect(ui->customPlot, SIGNAL(axisDoubleClick(QCPAxis*,QCPAxis::SelectablePart,QMouseEvent*)),
//            this, SLOT(axisLabelDoubleClick(QCPAxis*,QCPAxis::SelectablePart)));
//    connect(ui->customPlot, SIGNAL(legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*,QMouseEvent*)),
//            this, SLOT(legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*)));
//    connect(title, SIGNAL(doubleClicked(QMouseEvent*)), this, SLOT(titleDoubleClick(QMouseEvent*)));

//    // connect slot that shows a message in the status bar when a graph is clicked:
//    connect(ui->customPlot, SIGNAL(plottableClick(QCPAbstractPlottable*,int,QMouseEvent*)),
//            this, SLOT(graphClicked(QCPAbstractPlottable*,int)));

//    // setup policy and connect slot for context menu popup:
//    ui->customPlot->setContextMenuPolicy(Qt::CustomContextMenu);
//    connect(ui->customPlot, SIGNAL(customContextMenuRequested(QPoint)),
//            this, SLOT(contextMenuRequest(QPoint)));
    connect(ui->customPlot_1, SIGNAL(mouseWheel(QWheelEvent*)),
            this, SLOT(mouseWheel()));
}

modeling::~modeling()
{
    delete ui;
}

void modeling::mouseWheel()
{
  if (ui->customPlot_1->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
    ui->customPlot_1->axisRect()->setRangeZoom(ui->customPlot_1->xAxis->orientation());
  else if (ui->customPlot_1->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
    ui->customPlot_1->axisRect()->setRangeZoom(ui->customPlot_1->yAxis->orientation());
  else
    ui->customPlot_1->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
}
