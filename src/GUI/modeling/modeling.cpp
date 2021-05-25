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
    ui->customPlot_1->xAxis->setRange(-1000, 10000);
    ui->customPlot_1->yAxis->setRange(-1000, 10000);

    ui->customPlot_2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                    QCP::iSelectLegend | QCP::iSelectPlottables);
    ui->customPlot_2->xAxis->setRange(-10000, 10000);
    ui->customPlot_2->yAxis->setRange(-10000, 10000);

    //ui->customPlot_2->
    //ui->customPlot_2->axisRect()->setupFullAxesBox();

//    ui->customPlot_1->plotLayout()->insertRow(0);
//    QCPTextElement *title = new QCPTextElement(ui->customPlot_1,
//                                               "Interaction Example",
//                                               QFont("sans", 17, QFont::Bold));
//    ui->customPlot_1->plotLayout()->addElement(0, 0, title);

    ui->customPlot_2->xAxis->setLabel("x, km");
    ui->customPlot_2->yAxis->setLabel("y, km");

    ui->customPlot_1->xAxis->setLabel("Горизонтальная дальность, км");
    ui->customPlot_1->yAxis->setLabel("Высота, км");

    pbu_model pbu;
    x_pbu.append(0);
    y_pbu.append(0);
    z_pbu.append(0);
    range_pbu.append(0);
    create_stationary_graphs();

//    connect(ui->customPlot_1, SIGNAL(mouseWheel(QWheelEvent*)),
//            this, SLOT(mouseWheel_1(QWheelEvent*)));
//    connect(ui->customPlot_2, SIGNAL(mouseWheel(QWheelEvent*)),
//            this, SLOT(mouseWheel_2(QWheelEvent*)));

    //ui->customPlot_1->legend->setVisible(true);
//    QFont legendFont = font();
//    legendFont.setPointSize(10);
//    ui->customPlot_1->legend->setFont(legendFont);
//    ui->customPlot_1->legend->setSelectedFont(legendFont);
//    ui->customPlot_1->legend->setSelectableParts(QCPLegend::spItems); // legend box shall not be selectable, only legend items

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
//    connect(ui->customPlot_1, SIGNAL(mouseWheel(QWheelEvent*)),
//            this, SLOT(mouseWheel()));
}

modeling::~modeling()
{
    delete ui;
}

void modeling::clear_data()
{
    count_graph = 3;
    vector_range_radar.clear();
    vector_x_radar.clear();
    vector_y_radar.clear();
    vector_z_radar.clear();
}

void modeling::set_data(QString _config_name)
{
    QFile fileJson(_config_name);
    fileJson.open(QIODevice::ReadOnly);
    QJsonDocument doc = QJsonDocument::fromJson(fileJson.readAll());
    QJsonObject j_object = doc.object();

    //QString name = j_object["scenario_name"].toString();
   // ui->time_modelinglineEdit->setText(j_object["end_time"].toString());

    //set_properties_antiaircraft();

    QJsonArray array = j_object["objects"].toArray();
    for (QJsonValue value : array)
    {
        if (value.toObject()["model_name"].toString() == "PBU")
        {
            pbu.set_id(value.toObject()["id"].toInt());
            pbu.set_name(value.toObject()["model_name"].toString());
            pbu.set_coordinates(
                        value.toObject()["initial_data"].toObject()["x"].toDouble(),
                    value.toObject()["initial_data"].toObject()["y"].toDouble(),
                    value.toObject()["initial_data"].toObject()["z"].toDouble());
        }
        if (value.toObject()["model_name"].toString() == "RLS")
        {
            QJsonObject j_object_radar = value.toObject()["initial_data"].toObject();
            radar_model radar(j_object_radar);
            int id =value.toObject()["id"].toInt();
            radar.set_id(id);
            radar.set_name(value.toObject()["model_name"].toString()+"_"
                                                    +map_radars.size());
            //radar.set_model(value.toObject()["model"].toString());
            map_radars.insert(id,radar);
        }

        if (value.toObject()["model_name"].toString() == "PU")
        {
            QJsonObject j_object_launcher = value.toObject()["initial_data"].toObject();
            launcher_model pu(j_object_launcher);
            int id =value.toObject()["id"].toInt();
            pu.set_id(id);
            pu.set_name(value.toObject()["model_name"].toString()+"_"
                                                    +map_launchers.size());
            map_launchers.insert(id,pu);
        }

        if (value.toObject()["model_name"].toString() == "AirTarget")
        {
            QJsonObject j_object_craft = value.toObject()["initial_data"].toObject();
            aircraft_model craft(j_object_craft);
            int id =value.toObject()["id"].toInt();
            craft.set_id(id);
            map_aircraft_m.insert(id,craft);
        }

        if (value.toObject()["model_name"].toString() == "ZUR")
        {
            QJsonObject j_object_craft = value.toObject()["initial_data"].toObject();
            zur_model zur(j_object_craft);
            int id =value.toObject()["id"].toInt();
            zur.set_id(id);
            map_zurs.insert(id,zur);
        }
    }
    fileJson.close();
}

//void set_data_pbu(int id, double x, double y)
//{

//}

void modeling::set_name_json(QString _name_json)
{
    name_config = _name_json;
    set_data(_name_json);
    create_moving_graphs();
    ///vremenno
    read_csv();
}

void modeling::plot_1(int number,
                    QVector<double> vector_z,
                    QVector<double> vector_range)
{
    ui->customPlot_1->graph(number)->setData(vector_z,vector_range,true);
    ui->customPlot_1->replot();
    ui->customPlot_1->update();
}

void modeling::plot_2(int number,
                    QVector<double> vector_x,
                    QVector<double> vector_y)
{
    ui->customPlot_2->graph(number)->setData(vector_x,vector_y,true);
    ui->customPlot_2->replot();
    ui->customPlot_2->update();
}

void modeling::create_stationary_graphs()
{
    ui->customPlot_1->addGraph();
    ui->customPlot_1->addGraph();
    ui->customPlot_1->addGraph();

    ui->customPlot_2->addGraph();
    ui->customPlot_2->addGraph();
    ui->customPlot_2->addGraph();

    QPen pen(Qt::green, 6, Qt::DashDotDotLine,
             Qt::RoundCap, Qt::RoundJoin);
    //radar
    ui->customPlot_1->graph(radar_plot)->setLineStyle(QCPGraph::lsNone);
    ui->customPlot_1->graph(radar_plot)->
            setScatterStyle(QCPScatterStyle::ssSquare);
    ui->customPlot_1->graph(radar_plot)->setPen(pen);

    ui->customPlot_2->graph(radar_plot)->setLineStyle(QCPGraph::lsNone);
    ui->customPlot_2->graph(radar_plot)->
            setScatterStyle(QCPScatterStyle::ssSquare);
    ui->customPlot_2->graph(radar_plot)->setPen(pen);
    //pu
    pen.setColor(Qt::blue);
    ui->customPlot_1->graph(pu_plot)->setLineStyle(QCPGraph::lsNone);
    ui->customPlot_1->graph(pu_plot)->
            setScatterStyle(QCPScatterStyle::ssCircle);
    ui->customPlot_1->graph(pu_plot)->setPen(pen);

    ui->customPlot_2->graph(pu_plot)->setLineStyle(QCPGraph::lsNone);
    ui->customPlot_2->graph(pu_plot)->
            setScatterStyle(QCPScatterStyle::ssCircle);
    ui->customPlot_2->graph(pu_plot)->setPen(pen);
    //pbu
    pen.setColor(Qt::darkMagenta);
    ui->customPlot_1->graph(pbu_plot)->setLineStyle(QCPGraph::lsNone);
    ui->customPlot_1->graph(pbu_plot)->
            setScatterStyle(QCPScatterStyle::ssTriangle);
    ui->customPlot_1->graph(pbu_plot)->setPen(pen);

    ui->customPlot_2->graph(pbu_plot)->setLineStyle(QCPGraph::lsNone);
    ui->customPlot_2->graph(pbu_plot)->
            setScatterStyle(QCPScatterStyle::ssTriangle);
    ui->customPlot_2->graph(pbu_plot)->setPen(pen);
    plot_1(pbu_plot, x_pbu, y_pbu);
    plot_2(pbu_plot, z_pbu, range_pbu);
}

void modeling::set_stationary_elements()
{
    for (QMap <int, radar_model>::iterator i = map_radars.begin();
         i != map_radars.end(); ++i)
    {
        vector_range_radar.append(i->get_range());
        vector_x_radar.append(i->get_x());
        vector_y_radar.append(i->get_y());
        vector_z_radar.append(i->get_z());
    }
    plot_1(radar_plot,vector_z_radar,vector_range_radar);
    plot_2(radar_plot,vector_x_radar,vector_y_radar);
//    for (QMap <int, launcher_model*>::iterator i = map_launchers.begin();
//         i != map_launchers.end(); ++i)
//    {
//        ui->customPlot_1->addGraph();
//        ui->customPlot_2->addGraph();
//        i.value()->set_graph(count_graph);
//        set_pen(count_graph);
//        ++count_graph;
//    }

}

///@note позже добавть объекты видимости РЛС
void modeling::create_moving_graphs()
{
    for (QMap <int, aircraft_model>::iterator i = map_aircraft_m.begin();
         i != map_aircraft_m.end(); ++i)
    {
        ui->customPlot_1->addGraph();
        ui->customPlot_2->addGraph();
        i.value().set_graph(count_graph);
        set_pen(count_graph);
        ++count_graph;
    }
    for (QMap <int, aircraft_pbu*>::iterator i = map_aircraft_pbu.begin();
         i != map_aircraft_pbu.end(); ++i)
    {
        ui->customPlot_1->addGraph();
        ui->customPlot_2->addGraph();
        i.value()->set_graph(count_graph);
        set_pen(count_graph);
        ++count_graph;
    }
    for (QMap <int, zur_model>::iterator i = map_zurs.begin();
         i != map_zurs.end(); ++i)
    {
        ui->customPlot_1->addGraph();
        ui->customPlot_2->addGraph();
        i.value().set_graph(count_graph);
        set_pen(count_graph);
        ++count_graph;
    }
}

void modeling::set_pen(int index)
{
    QPen pen_line(Qt::red, 3, Qt::DashDotLine,
             Qt::RoundCap, Qt::RoundJoin);
    QColor color( qrand() % ((255 + 1) - 0) + 0,
                  qrand() % ((255 + 1) - 0) + 0,
                  qrand() % ((255 + 1) - 0) + 0, 255 );
    pen_line.setColor(color);
    ui->customPlot_1->graph(index)->
            setScatterStyle(QCPScatterStyle::ssCircle);
    ui->customPlot_1->graph(index)->setLineStyle(QCPGraph::lsNone);
    ui->customPlot_1->graph(index)->setPen(pen_line);

    ui->customPlot_2->graph(index)->
            setScatterStyle(QCPScatterStyle::ssCircle);
    ui->customPlot_2->graph(index)->setLineStyle(QCPGraph::lsLine);
    ui->customPlot_2->graph(index)->setPen(pen_line);
}

void modeling::set_data_plot()
{
    for (QMap <int, aircraft_model>::iterator i = map_aircraft_m.begin();
         i != map_aircraft_m.end(); ++i)
    {
        plot_1(i->get_graph(),i->get_vector_z(),i->get_vector_range());
        plot_2(i->get_graph(),i->get_vector_x(),i->get_vector_y());
    }
}

void modeling::read_csv()
{
    QDir dir;
    QFileInfoList list = dir.entryInfoList();
    QStringList regexp;
    regexp << "(1Target3Points_AirTarget_\\d+.csv)"; //0
    QRegExp rx;

   rx.setPattern(regexp[0]);


    for (int i = 0; i < list.size(); ++i)
    {
        QFileInfo fileInfo = list.at(i);
        if (rx.exactMatch(fileInfo.fileName()))
        {
            read_aircraft_csv(fileInfo.fileName());
            qDebug() <<fileInfo.fileName()<<" dsfsd";
        }
        qDebug() << qPrintable(QString("%1 %2").arg(fileInfo.size(), 10)
                               .arg(fileInfo.fileName()));
    }
    ////vremenno
    set_data_plot();
}

void modeling::read_aircraft_csv(QString name_csv)
{
    QFile file(name_csv);
    if ( !file.open(QFile::ReadOnly | QFile::Text) )
    {
        qDebug() << "File not exists";
    }
    else
    {
//        aircraft_model model;
        QTextStream in(&file);
        QString line = in.readLine();
        int id;
        while (!in.atEnd())
        {
            line = in.readLine();
            id=line.split(',').at(1).toInt();

            map_aircraft_m.operator[](id).append_point(line.split(',').at(2).toDouble(),
                                                  line.split(',').at(3).toDouble(),
                                                  line.split(',').at(4).toDouble());
            map_aircraft_m.operator[](id).set_status(line.split(',').at(10).toInt());
        }
        qDebug()<<map_aircraft_m.operator[](id).get_id()<<"id";
        file.close();
    }
}

void modeling::read_zur_csv(QString name_csv)
{
    QFile file(name_csv);
    if ( !file.open(QFile::ReadOnly | QFile::Text) )
    {
        qDebug() << "File not exists";
    }
    else
    {
        QTextStream in(&file);
        QString line = in.readLine();
        while (!in.atEnd())
        {

            line = in.readLine();
            int id=line.split(',').at(0).toInt();

            map_zurs.take(id).append_point(line.split(',').at(1).toDouble(),
                                            line.split(',').at(2).toDouble(),
                                            line.split(',').at(3).toDouble());
            map_zurs.take(id).set_status(line.split(',').at(9).toInt());

        }
        file.close();
    }
}
void modeling::read_radar_csv(QString name_csv)
{
    QFile file(name_csv);
    if ( !file.open(QFile::ReadOnly | QFile::Text) )
    {
        qDebug() << "File not exists";
    }
    else
    {
        QTextStream in(&file);
        QString line = in.readLine();
        while (!in.atEnd())
        {
            aircraft_pbu *craft = new aircraft_pbu();
            int id;
            QTextStream in(&file);
            line = in.readLine();
            while (!in.atEnd())
            {
                line = in.readLine();

                id=line.split(',').at(11).toInt();
                craft->set_id(id);
                craft->append_point(line.split(',').at(4).toDouble(),
                                    line.split(',').at(5).toDouble(),
                                    line.split(',').at(6).toDouble());
                craft->set_time_spotted(line.split(',').at(10).toDouble());
                craft->set_status(line.split(',').at(12).toInt());
            }
            map_aircraft_pbu.insert(id,craft);
        }
        file.close();
    }
}

void modeling::read_pbu_csv(QString name_csv)
{
    QFile file(name_csv);
    if ( !file.open(QFile::ReadOnly | QFile::Text) )
    {
        qDebug() << "File not exists";
    }
    else
    {
        QTextStream in(&file);
        QString line = in.readLine();
        aircraft_pbu *craft = new aircraft_pbu();
        int id;
        while (!in.atEnd())
        {
            line = in.readLine();

            id=line.split(',').at(11).toInt();
            craft->set_id(id);
            craft->append_point(line.split(',').at(4).toDouble(),
                                line.split(',').at(5).toDouble(),
                                line.split(',').at(6).toDouble());
            craft->set_time_spotted(line.split(',').at(10).toDouble());
            craft->set_status(line.split(',').at(12).toInt());
        }
        map_aircraft_pbu.insert(id,craft);
    }
    file.close();
}

void modeling::read_launcher_csv(QString name_csv)
{
    QFile file(name_csv);
    if ( !file.open(QFile::ReadOnly | QFile::Text) )
    {
        qDebug() << "File not exists";
    }
    else
    {
        QTextStream in(&file);
        QString line = in.readLine();
        while (!in.atEnd())
        {
            line = in.readLine();
            int id=line.split(',').at(0).toInt();
            map_launchers.take(id).set_ammo(line.split(',').at(4).toInt());
            map_zurs.take(id).set_status(line.split(',').at(6).toInt());
        }
        file.close();
    }
}
