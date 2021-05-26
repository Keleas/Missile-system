#include "modeling.h"
#include "ui_modeling.h"

modeling::modeling(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::modeling)
{
    std::srand(QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0);
    ui->setupUi(this);

    //left
    ui->customPlot_2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom /*| QCP::iSelectAxes |
                                    QCP::iSelectLegend | QCP::iSelectPlottables*/);
    ui->customPlot_2->xAxis->setRange(-10000, 10000);
    ui->customPlot_2->yAxis->setRange(-10000, 10000);

    //right
    ui->customPlot_1->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom /*| QCP::iSelectAxes |
                                    QCP::iSelectLegend | QCP::iSelectPlottables*/);
    ui->customPlot_1->xAxis->setRange(-1000, 10000);
    ui->customPlot_1->yAxis->setRange(-1000, 10000);



    //ui->customPlot_2->
    //ui->customPlot_2->axisRect()->setupFullAxesBox();

//    ui->customPlot_1->plotLayout()->insertRow(0);
//    QCPTextElement *title = new QCPTextElement(ui->customPlot_1,
//                                               "Interaction Example",
//                                               QFont("sans", 17, QFont::Bold));
//    ui->customPlot_1->plotLayout()->addElement(0, 0, title);

    ui->customPlot_2->xAxis->setLabel("x, м");
    ui->customPlot_2->yAxis->setLabel("y, м");

    ui->customPlot_1->xAxis->setLabel("Горизонтальная дальность, м");
    ui->customPlot_1->yAxis->setLabel("Высота, м");

    pbu_model pbu;
    x_pbu.append(0);
    y_pbu.append(0);
    z_pbu.append(0);
    range_pbu.append(0);

    create_stationary_graphs();

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

//    qDebug()<< j_object["scenario_name"].toString();
//    qDebug()<<j_object["end_time"].toDouble();
    end_time = j_object["end_time"].toDouble();

//    qDebug()<<end_time/_STEP_TIME_;

    ui->sosiska->setMaximum(end_time);
    ui->sosiska->setMinimum(0);
    ui->sosiska->setSingleStep(_STEP_TIME_);
    connect(ui->sosiska, SIGNAL(valueChanged(int)),
            this, SLOT(change_step(int)));


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

void modeling::accept_json(QString _name_json)
{
    name_config = _name_json;
    set_data(_name_json);
    ///установка объектов из json
    create_moving_graphs();
    set_stationary_elements();
    append_layout_pu();
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
    ui->customPlot_1->graph(launcher_plot)->setLineStyle(QCPGraph::lsNone);
    ui->customPlot_1->graph(launcher_plot)->
            setScatterStyle(QCPScatterStyle::ssCircle);
    ui->customPlot_1->graph(launcher_plot)->setPen(pen);

    ui->customPlot_2->graph(launcher_plot)->setLineStyle(QCPGraph::lsNone);
    ui->customPlot_2->graph(launcher_plot)->
            setScatterStyle(QCPScatterStyle::ssCircle);
    ui->customPlot_2->graph(launcher_plot)->setPen(pen);
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
    plot_1(radar_plot,vector_range_radar,vector_z_radar);
    plot_2(radar_plot,vector_x_radar,vector_y_radar);

    for (QMap <int, launcher_model>::iterator i = map_launchers.begin();
         i != map_launchers.end(); ++i)
    {
        vector_range_pu.append(i->get_range());
        vector_x_pu.append(i->get_x());
        vector_y_pu.append(i->get_y());
        vector_z_pu.append(i->get_z());
    }
    plot_1(launcher_plot,vector_range_pu,vector_z_pu);
    plot_2(launcher_plot,vector_x_pu,vector_y_pu);
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
    ui->customPlot_2->graph(index)->setLineStyle(QCPGraph::lsNone);
    ui->customPlot_2->graph(index)->setPen(pen_line);
}

void modeling::set_pen_radius(int number)
{
    QPen pen_line(Qt::red, 3, Qt::DashDotLine,
             Qt::RoundCap, Qt::RoundJoin);
    QColor color( qrand() % ((255 + 1) - 0) + 0,
                  qrand() % ((255 + 1) - 0) + 0,
                  qrand() % ((255 + 1) - 0) + 0, 255 );
    pen_line.setColor(color);
    ui->customPlot_1->graph(number)->
            setScatterStyle(QCPScatterStyle::ssDot);
    ui->customPlot_1->graph(number)->setLineStyle(QCPGraph::lsNone);
    ui->customPlot_1->graph(number)->setPen(pen_line);

    ui->customPlot_2->graph(number)->
            setScatterStyle(QCPScatterStyle::ssDot);
    ui->customPlot_2->graph(number)->setLineStyle(QCPGraph::lsNone);
    ui->customPlot_2->graph(number)->setPen(pen_line);
}

///@note позже добавть объекты видимости РЛС
void modeling::create_moving_graphs()
{
    for (QMap <int, aircraft_model>::iterator i = map_aircraft_m.begin();
         i != map_aircraft_m.end(); ++i)
    {
        ui->customPlot_1->addGraph();
        ui->customPlot_2->addGraph();
        count_graph = (ui->customPlot_1->graphCount())-1;
        i.value().set_graph(count_graph);
        set_pen(count_graph);
    }
//    for (QMap <int, aircraft_pbu*>::iterator i = map_aircraft_pbu.begin();
//         i != map_aircraft_pbu.end(); ++i)
//    {
//        ui->customPlot_1->addGraph();
//        ui->customPlot_2->addGraph();
//        i.value()->set_graph(count_graph);
//        set_pen(count_graph);
//        ++count_graph;
//    }
//    for (QMap <int, zur_model>::iterator i = map_zurs.begin();
//         i != map_zurs.end(); ++i)
//    {
//        ui->customPlot_1->addGraph();
//        ui->customPlot_2->addGraph();
//        i.value().set_graph(count_graph);
//        set_pen(count_graph);
//        ++count_graph;
//    }
}

void modeling::create_dynamic_elements()
{
        for (QMap <int, aircraft_pbu*>::iterator i = map_aircraft_pbu.begin();
             i != map_aircraft_pbu.end(); ++i)
    {
        ui->customPlot_1->addGraph();
        ui->customPlot_2->addGraph();
        count_graph = (ui->customPlot_1->graphCount())-1;
        i.value()->set_graph(count_graph);
        set_pen(count_graph);
        //plot_1(count_graph,i.value()->get_vector_range(),i.value()->get_vector_z());
        //plot_2(count_graph,i.value()->get_vector_x(),i.value()->get_vector_y());
    }

//    for (QMap <int, zur_model*>::iterator i = map_launchers.begin();
//         i != map_launchers.end(); ++i)
//    {
//        ui->customPlot_1->addGraph();
//        ui->customPlot_2->addGraph();
//        count_graph = (ui->customPlot_1->graphCount())-1;
//        i.value()->set_graph(count_graph);
//        set_pen(count_graph);
//    }

}

///@note полное отображение траектории
void modeling::set_data_plot()
{
    for (QMap <int, aircraft_model>::iterator i = map_aircraft_m.begin();
         i != map_aircraft_m.end(); ++i)
    {
        plot_1(i->get_graph(),i->get_vector_range(),i->get_vector_z());
        plot_2(i->get_graph(),i->get_vector_x(),i->get_vector_y());
    }
//    for (QMap <int, aircraft_pbu*>::iterator i = map_aircraft_pbu.begin();
//         i != map_aircraft_pbu.end(); ++i)
//    {
//        plot_1(i.value()->get_graph(),i.value()->get_vector_z(),
//               i.value()->get_vector_range());
//        plot_2(i.value()->get_graph(),i.value()->get_vector_x(),
//               i.value()->get_vector_y());
//    }
}

void modeling::read_csv()
{
    QDir dir;
    QFileInfoList list = dir.entryInfoList();
    QStringList regexp;
    regexp << "("+name_config.split("/").last().split(".").at(0)+"_PBU_\\d+.csv)"//0
           << "("+name_config.split("/").last().split(".").at(0)+"_AirTarget_\\d+.csv)"//1
           << "("+name_config.split("/").last().split(".").at(0)+"_PU_\\d+.csv)" //2
           << "("+name_config.split("/").last().split(".").at(0)+"_RLS_\\d+.csv)" //3
           << "("+name_config.split("/").last().split(".").at(0)+"_ZUR_\\d+.csv)";  //4
    QRegExp rx;
    QThread::sleep(3);
    for (int ii = 0; ii<regexp.size(); ++ii)
    {
        rx.setPattern(regexp[ii]);
        for (int jj = 0; jj < list.size(); ++jj)
        {
            QFileInfo fileInfo = list.at(jj);
            if (rx.exactMatch(fileInfo.fileName()))
            {
                pick_read_method(ii,fileInfo.fileName());
                //qDebug() <<fileInfo.fileName()<<" dsfsd";
            }
//            qDebug() << qPrintable(QString("%1 %2").arg(fileInfo.size(), 10)
//                                   .arg(fileInfo.fileName()));
        }
    }
    ///@note vremenno
    //set_data_plot();
    create_dynamic_elements();
}

void modeling::pick_read_method(int state, QString _name_csv)
{
    switch (state)
    {
    case rls_read:
    {
        qDebug()<<"Не робит";
       // read_radar_csv(_name_csv);
    }break;
    case launcher_read:
    {
        read_launcher_csv(_name_csv);
    }break;
    case pbu_read:
    {
        read_pbu_csv(_name_csv);
    }break;
    case aircraft_read:
    {
        read_aircraft_csv(_name_csv);
    }break;
    case zur_read:
    {
        //read_zur_csv(_name_csv);
    }break;
    }
}

///@note уточнить
void modeling::read_aircraft_csv(QString name_csv)
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
        int id;
        int ii=0;/////временно
        while (!in.atEnd())
        {
            ++ii; /////временно
            line = in.readLine();
            id=line.split(',').at(1).toInt();

            map_aircraft_m.operator[](id).append_point(ii,
                                                       line.split(',').at(2).toDouble(),
                                                       line.split(',').at(3).toDouble(),
                                                       line.split(',').at(4).toDouble(),
                                                       line.split(',').at(10).toInt());
        }
        file.close();
    }
}
///@note уточнить
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
        int id;
        while (!in.atEnd())
        {
            line = in.readLine();
            id=line.split(',').at(2).toInt();

            map_zurs.take(id).append_point(line.split(',').at(0).toDouble(),
                                           line.split(',').at(2).toDouble(),
                                           line.split(',').at(3).toDouble(),
                                           line.split(',').at(4).toDouble(),
                                           line.split(',').at(9).toInt());
            ///@note уточнить
            map_zurs.take(id).set_status(line.split(',').at(9).toInt());
        }
        file.close();
    }
}
///@note не нужен
void modeling::read_radar_csv(QString name_csv)
{
    QFile file(name_csv);
    if ( !file.open(QFile::ReadOnly | QFile::Text) )
    {
        qDebug() << "File not exists";
    }
    else
    {
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
        QVector <int> id_pbu_aircrafts;
        int id =0;
        id_pbu_aircrafts.append(id);
        while (!in.atEnd())
        {
            line = in.readLine();
            id=line.split(',').at(1).toInt();
            if(id>id_pbu_aircrafts.last())
            {
               id_pbu_aircrafts.append(id);
               aircraft_pbu *craft = new aircraft_pbu();
               craft->set_id(id);
               craft->set_time_spotted(line.split(',').last().toDouble());

               ui->customPlot_1->addGraph();
               ui->customPlot_2->addGraph();
               count_graph = (ui->customPlot_1->graphCount())-1;
               craft->set_graph(count_graph);

               map_aircraft_pbu.insert(id,craft);
            }

            map_aircraft_pbu.operator[](id)->append_point(
                        line.split(',').at(0).toDouble(),
                        line.split(',').at(2).toDouble(),
                        line.split(',').at(3).toDouble(),
                        line.split(',').at(4).toDouble(),
                        0);
        }
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
        int id;

        while (!in.atEnd())
        {
            line = in.readLine();
            id=line.split(',').at(1).toInt();
            map_launchers.operator[](id).append_step(line.split(',').at(0).toDouble(),
                                                     line.split(',').at(5).toInt(),
                                                     line.split(',').at(7).toInt());
        }
        file.close();
    }
}

void modeling::change_step(int index)
{

    for (QMap <int, aircraft_model>::iterator i = map_aircraft_m.begin();
         i != map_aircraft_m.end(); ++i)
    {
        double uu = double(index);
        if(i->get_points().contains(uu)==true)
        {
            plot_1(i->get_graph(),i->get_points().operator[](uu)->vector_point_range,
                    i->get_points().operator[](uu)->vector_point_z);
            plot_2(i->get_graph(),i->get_points().operator[](uu)->vector_point_x,
                    i->get_points().operator[](uu)->vector_point_y);
        }
    }

    for (QMap <int, aircraft_pbu*>::iterator i = map_aircraft_pbu.begin();
         i != map_aircraft_pbu.end(); ++i)
    {
        double uu = double(index);

        if(i.value()->get_points().contains(uu)==true)
        {
            plot_1(i.value()->get_graph(),
                   i.value()->get_points().operator[](uu)->vector_point_range,
                    i.value()->get_points().operator[](uu)->vector_point_z);
            plot_2(i.value()->get_graph(),
                   i.value()->get_points().operator[](uu)->vector_point_x,
                    i.value()->get_points().operator[](uu)->vector_point_y);
        }
    }

    for(QMap <int, launcher_model>::iterator i = map_launchers.begin();
        i != map_launchers.end(); ++i)
    {
        double uu = double(index);

        if(i->get_steps().contains(uu)==true)
        {
            i->get_steps().operator[](uu)->ammo_curr;
            i->get_steps().operator[](uu)->status_curr;
        }
    }
//    map_aircraft_m;
//    map_aircraft_pbu;
//    map_launchers;
}

void modeling::append_layout_pu()
{
    QVBoxLayout* vbox = new QVBoxLayout(this);
    for (QMap <int, launcher_model>::iterator i = map_launchers.begin();
         i != map_launchers.end(); ++i)
    {
        QHBoxLayout* hbox = new QHBoxLayout(this);
        QLabel* name_label = new QLabel(i->get_name(),this);
        QLabel* ammo_label = new QLabel(QString::number(i->get_ammo()),this);
        hbox->addWidget(name_label);
        hbox->addWidget(ammo_label);
        vbox->addLayout(hbox);
    }
    ui->pu_box->setLayout(vbox);
}

