#include "aircraft.h"

Point::Point()
{
    //point = 5665;
//    x =  12;
//    y =  32;
//    z =  3453;
//    velocity = 76567564;
}

Point::Point(double x,
             double y,
             double z,
             double velocity)
{
    this->x=x;
    this->x=y;
    this->x=z;
    this->x=velocity;
}

Point::Point(QJsonObject initData)
{
    //point = initData["point"].toInt();
    x =  initData["x"].toDouble();
    y =  initData["y"].toDouble();
    z =  initData["z"].toDouble();
    velocity = initData["vel"].toDouble();
}

QJsonObject Point::toJsonObject()
{
    QJsonObject pointJsonObj
    {
       // {"point", point},
        {"x", x},
        {"y", y},
        {"z", z},
        {"vel", velocity}
    };
    return pointJsonObj;
}

void Point::set_point(int _point)
{
    point = _point;
}

void Point::set_coordinates(double _x,
                            double _y,
                            double _z)
{
    x =_x;
    y = _y;
    z = _z;
}

void Point::set_velocity(double _velocity)
{
    velocity = _velocity;
}


Aircraft::Aircraft()
{
//    target_name = "10";
//    target_model_name = "initData[].toString()";
//    id = 666;
//    max_Nx = 333;
//    max_Ny= 444;
//    min_Nx= 555;
//    max_M= 666;
//    roof= 777;
//    points.append(Point());
}

//Aircraft::Aircraft(QString target_name,
//                   QString target_model_name,
//                   int id,
//                   double max_Nx,
//                   double max_Ny,
//                   double min_Nx,
//                   double max_M,
//                   double roof,
//                   QVector<Point> points)
//{
//    this->target_name = target_name;
//    this->target_model_name = target_model_name;
//    this->id = id;
//    this->max_Nx = max_Nx;
//    this->max_Ny = max_Ny;
//    this->min_Nx = min_Nx;
//    this->max_M = max_M;
//    this->roof = roof;
//    this->points = points;
//}

Aircraft::Aircraft(QJsonObject initData)
{
    target_name = initData["target_name"].toString();
    target_model_name = initData["target_model_type"].toString();
    id = initData["id"].toInt();
    max_Nx = initData["target_max_Nx"].toDouble();
    max_Ny= initData["target_max_Ny"].toDouble();
    min_Nx= initData["target_min_Nx"].toDouble();
    max_M= initData["target_max_M"].toDouble();
    roof= initData["target_practical_roof"].toDouble();
    QJsonArray array = initData["target_points"].toArray();
    for (QJsonValue value : array)
    {
        Point p(value.toObject());
        points.append(p);
    }
}

QJsonObject Aircraft::toJsonObject()
{
    QJsonObject aircraftJsonObj
    {
        {"id", id},
        {"model_name", "AirTarget"}
    };

    QJsonObject aircraftJsonInitData
    {
        {"target_name", target_name},
        {"target_model_type", target_model_name},
        {"target_max_Nx",max_Nx},
        {"target_max_Ny",max_Ny},
        {"target_min_Nx",min_Nx},
        {"target_max_M",max_M},
        {"target_practical_roof",roof}
    };
    QJsonArray aircraft_points;
    for (Point p : points)
        aircraft_points.append(p.toJsonObject());


    aircraftJsonInitData.insert("target_points", QJsonValue(aircraft_points));
    aircraftJsonObj.insert("initial_data", QJsonValue(aircraftJsonInitData));
    return aircraftJsonObj;
}

void Aircraft::set_id(int _id)
{
    id = _id;
}
void Aircraft::set_name(QString _target_name)
{
    target_name = _target_name;
}
void Aircraft::set_model(QString _target_model_name)
{
    target_model_name = _target_model_name;
}
void Aircraft::set_properties(double _max_Nx,
                              double _max_Ny,
                              double _min_Nx,
                              double _max_M,
                              double _roof)
{
    max_Nx = _max_Nx;
    max_Ny = _max_Ny;
    min_Nx = _min_Nx;
    max_M =_max_M;
    roof =_roof;
}

void Aircraft::set_points(QVector<Point> _points)
{
    points = _points;
}

void Aircraft::append_point(Point _point)
{
    points.append(_point);
}
