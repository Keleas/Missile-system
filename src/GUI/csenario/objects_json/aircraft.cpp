#include "aircraft.h"

Point::Point()
{

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

}


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


//    craft->set_id(value.toObject()["id"].toInt());
//    craft->set_model(value.toObject()["initial_data"].
//            toObject()["target_model_type"].toString());
//    craft->set_name(value.toObject()["initial_data"].
//            toObject()["target_name"].toString());
//    craft->set_properties(
//                value.toObject()["initial_data"].
//            toObject()["target_max_Nx"].toDouble(),
//            value.toObject()["initial_data"].
//            toObject()["target_max_Ny"].toDouble(),
//            value.toObject()["initial_data"].
//            toObject()["target_min_Nx"].toDouble(),
//            value.toObject()["initial_data"].
//            toObject()["target_max_M"].toDouble(),
//            value.toObject()["initial_data"].
//            toObject()["target_practical_roof"].toDouble());
//    QJsonArray array_points = value.toObject()["initial_data"].
//            toObject()["target_points"].toArray();
//    for (QJsonValue value_point : array_points)
//    {
//        Point p;
//        p.set_coordinates(
//                    value_point.toObject()["x"].toDouble(),
//                    value_point.toObject()["y"].toDouble(),
//                    value_point.toObject()["z"].toDouble());
//        p.set_velocity(value_point.toObject()["vel"].toDouble());
//        craft->append_point(p);
//    }


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

QTreeWidgetItem* Aircraft::get_item(int count)
{
    QStringList list;
//    list<<"ID: "+QString::number(id)
//       <<"x: "+QString::number(x)
//      <<"y: "+QString::number(y)
//     <<"z: "+QString::number(z);
//    list.append("Радиус действия (км): "+QString::number(radius));
//    list.append("Количество ЗУР: "+QString::number(count_ammo));
//    list.append("Время перезарядки (c): "+QString::number(cooldown));
    //    list.append("Направление оси вращения РЛС _X: 0");
    //    list.append("Направление оси вращения РЛС _Y: 0");
    //    list.append("Направление оси вращения РЛС _Z: 0");
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(0, "ПУ_"+QString::number(count));
    for (int ii=0;ii<list.size() ; ++ii)
    {
        QTreeWidgetItem* item_child = new QTreeWidgetItem();
        item->addChild(item_child);
        item_child->setText(0,list.at(ii));
    }
    return item;
}
