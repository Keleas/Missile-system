#include "radar.h"

Radar::Radar()
{

}

Radar::Radar(QJsonObject initData)
{
    id = initData["id"].toInt();
    model = initData["model"].toString();

    x =  initData["x"].toDouble();
    y =  initData["y"].toDouble();
    z =  initData["z"].toDouble();
    rotate_x = initData["rotate_x"].toDouble();
    rotate_y = initData["rotate_y"].toDouble();
    rotate_z = initData["rotate_z"].toDouble();
    name = initData["name"].toString();

    lambda = initData["lambda"].toDouble();
    Dmax = initData["Dmax"].toDouble();
    Dmin = initData["Dmin"].toDouble();
    Tscan = initData["Tscan"].toDouble();
    Timp = initData["Timp"].toDouble();
    V_res = initData["V_res"].toDouble();
    asimres = initData["asim_res"].toDouble();
    elevres = initData["elev_res"].toDouble();
    asimrestracecf = initData["asim_res_trace_cf"].toDouble();
    elevrestracecf = initData["elev_res_trace_cf"].toDouble();
    elev1 = initData["elev1"].toDouble();
    elev2 = initData["elev2"].toDouble();
    Nasim = initData["Nasim"].toDouble();
    Nelev = initData["Nelev"].toDouble();
    Bandwidth = initData["Bandwidth"].toDouble();
    Noise = initData["Noise"].toDouble();
    Gain = initData["Gain"].toDouble();
    P_peak = initData["P_peak"].toDouble();
    Tr = initData["Tr"].toDouble();
    calculate_radius(Dmin,Dmax);

    count_channels_targets = initData["Ntraj"].toDouble();
    count_channels_zurs = initData["Nmissiles"].toDouble();
}

QJsonObject Radar::toJsonObject()
{
    QJsonObject radarJsonObj
    {
        {"id", id},
        {"model_name", "RLS"},
        {"model",model}
    };
    QJsonObject radarJsonInitData
    {
        {"x",x},
        {"y",y},
        {"z",z},
        {"rotate_x",rotate_x},
        {"rotate_y",rotate_y},
        {"rotate_z",rotate_z},
        {"name",name},

        {"Ntraj",count_channels_targets},
        {"Nmissiles",count_channels_zurs},
        {"lambda",lambda},
        {"Dmax",Dmax},
        {"Dmin",Dmin},
        {"Tscan",Tscan},
        {"Timp",Timp},
        {"V_res",V_res},
        {"asim_res",asimres},
        {"elev_res",elevres},
        {"asim_res_trace_cf",asimrestracecf},
        {"elev_res_trace_cf",elevrestracecf},
        {"elev1",elev1},
        {"elev2",elev2},
        {"Nasim",Nasim},
        {"Nelev",Nelev},
        {"Bandwidth",Bandwidth},
        {"Noise",Noise},
        {"Gain",Gain},
        {"P_peak",P_peak},
        {"Tr",Tr}
    };
    radarJsonObj.insert("initial_data", QJsonValue(radarJsonInitData));
    return radarJsonObj;
}

QTreeWidgetItem* Radar::get_item(int count)
{
    QStringList list;
    list<<"ID: "+QString::number(id)
       <<"Модель: "+model
      <<"x: "+QString::number(x)
     <<"y: "+QString::number(y)
    <<"z: "+QString::number(z)
    <<"Dmax: "+QString::number(Dmax)
    <<"Dmin: "+QString::number(Dmin);

    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(0, "РЛС_"+QString::number(count));
    for (int ii=0;ii<list.size() ; ++ii)
    {
         QTreeWidgetItem* item_child = new QTreeWidgetItem();
         item->addChild(item_child);
         item_child->setText(0,list.at(ii));
    }
    return item;
}

void Radar::set_id(int _id)
{
    id = _id;
}

void Radar::set_rotates(double _rotate_x,
                        double _rotate_y,
                        double _rotate_z)
{
    rotate_x =_rotate_x;
    rotate_y = _rotate_y;
    rotate_z = _rotate_z;
}

void Radar::set_coordinates(double _x,
                            double _y,
                            double _z)
{
    x =_x;
    y = _y;
    z = _z;
}

void Radar::set_model(QString _model)
{
    model = _model;
}

void Radar::set_is_pisets_kolya(QString _model, QSqlDatabase db)
{
    QSqlQuery query(db);
    QString select = "SELECT lambda,Dmax,Dmin,Tscan,Timp,V_res,asimres,elevres,"
    "asimrestracecf,elevrestracecf,elev1,elev2,Nasim,Nelev,Bandwidth,Noise,"
    "Gain, P_peak, Tr, Ntraj, Nmissiles FROM radars WHERE type = '"+_model+"'";
    if(!query.exec(select))
    {
        qDebug()<<query.lastError()<<"select radar_all";
    }
    while (query.next())
    {
        lambda = query.value(0).toDouble();
        Dmax= query.value(1).toDouble();
        Dmin= query.value(2).toDouble();
        Tscan= query.value(3).toDouble();
        Timp= query.value(4).toDouble();
        V_res= query.value(5).toDouble();
        asimres= query.value(6).toDouble();
        elevres= query.value(7).toDouble();
        asimrestracecf= query.value(8).toDouble();
        elevrestracecf= query.value(9).toDouble();
        elev1= query.value(10).toDouble();
        elev2= query.value(11).toDouble();
        Nasim= query.value(12).toDouble();
        Nelev= query.value(13).toDouble();
        Bandwidth= query.value(14).toDouble();
        Noise= query.value(15).toDouble();
        Gain= query.value(16).toDouble();
        P_peak= query.value(17).toDouble();
        Tr= query.value(18).toDouble();
        count_channels_targets= query.value(19).toInt();
        count_channels_zurs = query.value(20).toInt();
    }
    rotate_x = 0;
    rotate_y = 0;
    rotate_z = 1;
    calculate_radius(Dmin,Dmax);
}

void Radar::calculate_radius(double radius_min, double radius_max)
{
    for (double t=0; t<2*3.14; t+=0.01)
    {
        vector_radius_min_x.append(radius_min*(cos(t))+x);
        vector_radius_min_y.append(radius_min*(sin(t))+y);
        vector_radius_max_x.append(radius_max*(cos(t))+x);
        vector_radius_max_y.append(radius_max*(sin(t))+y);
    }
}
