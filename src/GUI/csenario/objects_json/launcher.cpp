#include "launcher.h"

Launcher::Launcher()
{
//    id = 354341;
//    x =  3546;
//    y =  87;
//    z =  3124;
//    radius = 635;
//    count_ammo = 8796;
//    cooldown = 134;
    //rokets.append(1000);rokets.append(1001);rokets.append(1002);rokets.append(1003);
}

Launcher::Launcher(int id,
                   double x,
                   double y,
                   double z,
                   double radius,
                   int count_ammo,
                   int cooldown//,
                   //QVector<int> rokets
                   )
{
    this->id = id;
    this->x =  x;
    this->y =  y;
    this->z =  z;
    this->radius = radius;
    this->count_ammo = count_ammo;
    this->cooldown = cooldown;
    //this->rokets = rokets;
}

Launcher::Launcher(QJsonObject initData)
{
    id = initData["id"].toInt();
    x =  initData["x"].toDouble();
    y =  initData["y"].toDouble();
    z =  initData["z"].toDouble();
    radius = initData["radius"].toDouble();
    count_ammo = initData["rockets_amount"].toInt();
    cooldown = initData["cooldown"].toInt();

//    QJsonArray array = initData["zur_id"].toArray();
//    for (QJsonValue value : array)
//    {
//        rokets.append(value.toInt());
//    }
}

QJsonObject Launcher::toJsonObject()
{
    QJsonObject launcherJsonObj
    {
        {"id", id},
        {"model_name", "PU"}
    };
//    QJsonArray zur_id;
//    for (int roket_id : rokets)
//    {
//        zur_id.append(roket_id);
//    }
    QJsonObject launcherJsonInitData
    {
        //{"id", vector_data_pu.at(ii)},
        {"x",x},
        {"y",y},
        {"z",z},
        {"radius",radius},
        {"rockets_amount",count_ammo},
        {"cooldown",cooldown},
//        {"zur_id",QJsonValue(zur_id)}
    };
    launcherJsonObj.insert("initial_data", QJsonValue(launcherJsonInitData));
    return launcherJsonObj;
}


void Launcher::set_id(int _id)
{
    id = _id;
}
void Launcher::set_coordinates(double _x,
                            double _y,
                            double _z)
{
    x =_x;
    y = _y;
    z = _z;
}

void Launcher::set_properties(double _radius,
                              int _count_ammo,
                              int _cooldown)
{
    radius = _radius;
    count_ammo=_count_ammo;
    cooldown=_cooldown;
}

//--------------------------------------------------
Antiaircraft::Antiaircraft(int id,
                           QString target_model_name,
                           double max_Nx,
                           double max_Ny,
                           double min_Nx,
                           double max_M,
                           double roof)
{
    //this->target_name = target_model_name;
    this->target_model_name = target_model_name;
    this->id = id;
    this->max_Nx = max_Nx;
    this->max_Ny = max_Ny;
    this->min_Nx = min_Nx;
    this->max_M = max_M;
    this->roof = roof;
    //this->points = points;
}

Antiaircraft::Antiaircraft(QJsonObject initData)
{
    //target_name = initData["target_name"].toString();;
    target_model_name = initData["target_model_type"].toString();
    id = initData["id"].toInt();
    max_Nx = initData["target_max_Nx"].toDouble();
    max_Ny= initData["target_max_Ny"].toDouble();
    min_Nx= initData["target_min_Nx"].toDouble();
    max_M= initData["target_max_M"].toDouble();
    roof= initData["target_practical_roof"].toDouble();
}

QJsonObject Antiaircraft::toJsonObject()
{
    QJsonObject launcherJsonObj
    {
        {"id", QString::number(id)},
        {"model_name", "launcher"}
    };
//    QJsonArray zur_id;
//    for (int roket_id : rokets)
//    {
//        zur_id.append(roket_id);
//    }
//    QJsonObject launcherJsonInitData
//    {
//        //{"id", vector_data_pu.at(ii)},
//        {"target_name", target_name},
//        {"target_model_type", target_model_name},
//        {"target_max_Nx",max_Nx},
//        {"target_max_Ny",max_Ny},
//        {"target_min_Nx",min_Nx},
//        {"target_max_M",max_M},
//        {"target_practical_roof",roof}
//    };
//    launcherJsonObj.insert("initial_data", QJsonValue(launcherJsonInitData));
    return launcherJsonObj;
}
