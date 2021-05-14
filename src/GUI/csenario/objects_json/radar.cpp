#include "radar.h"

Radar::Radar()
{
//    id = 324;
//    x = 21;
//    y = 756;
//    z = 867;
//    radius = 354;
//    model = 87;
//    count_channels_targets = 345;
//    count_channels_zurs = 789;
//    rotate_x = 43;
//    rotate_y = 354;
//    rotate_z = 8675;
}

Radar::Radar(int id,
             double x,
             double y,
             double z,
             int model,
             int count_channels_targets,
             int count_channels_zurs,
//             double rotate_x,
//             double rotate_y,
//             double rotate_z,
             double radius)
{
    this->id = id;
    this->x = x;
    this->y = y;
    this->z = z;
    this->radius = radius;
    this->model = model;
    this->count_channels_targets = count_channels_targets;
    this->count_channels_zurs = count_channels_zurs;
//    this->rotate_x = rotate_x;
//    this->rotate_y = rotate_y;
//    this->rotate_z = rotate_z;
}

Radar::Radar(QJsonObject initData)
{
    id = initData["id"].toInt();
    x =  initData["x"].toDouble();
    y =  initData["y"].toDouble();
    z =  initData["z"].toDouble();
    radius = initData["radius"].toDouble();
    model = initData["model"].toDouble();
    count_channels_targets = initData["count_channels_targets"].toInt();
    count_channels_zurs = initData["count_channels_zurs"].toInt();
//    rotate_x = initData["rotate_x"].toDouble();
//    rotate_y = initData["rotate_y"].toDouble();
//    rotate_z = initData["rotate_z"].toDouble();
}

QJsonObject Radar::toJsonObject()
{
    QJsonObject radarJsonObj
    {
        {"id", QString::number(id)},
        {"model_name", "RLS"}
    };
    QJsonObject radarJsonInitData
    {
        //{"id", vector_data_pu.at(ii)},
        {"x",x},
        {"y",y},
        {"z",z},
        {"radius",radius},
        {"model",model},
        {"count_channels_targets",count_channels_targets},
        {"count_channels_zurs",count_channels_zurs}//,
//        {"rotate_x",QString::number(rotate_x)},
//        {"rotate_y",QString::number(rotate_y)},
//        {"rotate_z",QString::number(rotate_z)}
    };
    radarJsonObj.insert("initial_data", QJsonValue(radarJsonInitData));
    return radarJsonObj;
}

QTreeWidgetItem* Radar::get_item()
{
    QTreeWidgetItem *item = new QTreeWidgetItem();

//    item-

    return item;
}

void Radar::set_id(int _id)
{
    id = _id;
}
void Radar::set_coordinates(double _x,
                            double _y,
                            double _z)
{
    x =_x;
    y = _y;
    z = _z;
}

void Radar::set_model(int _model)
{
    model = _model;
}

void Radar::set_properties(int _count_channels_targets,
                    int _count_channels_zurs,
                    double _radius)
{
    count_channels_targets =_count_channels_targets;
    count_channels_zurs=_count_channels_zurs;
    radius=_radius;
}
