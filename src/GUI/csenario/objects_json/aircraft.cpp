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

QTreeWidgetItem* Point::get_item(int count)
{
        QList<QString> list;
        list<<"#"+QString::number(count)
            <<"x: "+QString::number(x)
            <<"y: "+QString::number(y)
            <<"z: "+QString::number(z)
            <<"Скорость: "+QString::number(velocity);
        QTreeWidgetItem* item = new QTreeWidgetItem();

        item->setText(0,list.at(0));
        for (int ii=1;ii<list.size() ; ++ii)
        {
             QTreeWidgetItem* item_child = new QTreeWidgetItem();
             item_child->setText(0,list.at(ii));
             item->addChild(item_child);
        }
    return item;
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
        Point *p = new Point(value.toObject());
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
    for (Point* p : points)
        aircraft_points.append(p->toJsonObject());


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



void Aircraft::append_point(Point* _point)
{
    points.append(_point);
}

QTreeWidgetItem* Aircraft::get_item(int count)
{
    QStringList list;
    list<<"ID: "+QString::number(id)
       <<"Модель: "+target_model_name
      <<"Имя модели: "+target_name;

    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(0, "ЛА_"+QString::number(count));
    for (int ii=0;ii<list.size() ; ++ii)
    {
         QTreeWidgetItem* item_child = new QTreeWidgetItem();
         item->addChild(item_child);
         item_child->setText(0,list.at(ii));
    }
    return item;
}

QVector<double> Aircraft::get_vector_x()
{    QVector<double> points_x;
    for(Point *p : points)
    {
        points_x.append(p->get_x());
    }
    return points_x;
}

QVector<double> Aircraft::get_vector_y()
{    QVector<double> points_y;
    for(Point *p : points)
    {
        points_y.append(p->get_y());
    }
    return points_y;
}
