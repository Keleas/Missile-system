#include "launcher.h"

Antiaircraft::Antiaircraft()
{

}


Antiaircraft::Antiaircraft(QJsonObject initData, QSqlDatabase db)
{
    id = initData["id"].toInt();
    name =initData["name"].toString();

    QSqlQuery query(db);
    QString select = "SELECT nx_max, ny_max, nx_min, m_max, "
                     "practical_roof FROM aircrafts WHERE type = 'ЗУР'";

    if(!query.exec(select))
    {
        qDebug()<<query.lastError()<<"select ЗУР";
    }
    query.exec(select);
    while (query.next())
    {
        max_Nx = query.value(0).toDouble();
        max_Ny= query.value(1).toDouble();
        min_Nx= query.value(2).toDouble();
        max_M= query.value(3).toDouble();
        roof=query.value(4).toDouble();
    }

}

QJsonObject Antiaircraft::toJsonObject(QSqlDatabase db)
{

    QSqlQuery query(db);
    QString select = "SELECT nx_max, ny_max, nx_min, m_max, "
                     "practical_roof FROM aircrafts WHERE type = 'ЗУР'";

    if(!query.exec(select))
    {
        qDebug()<<query.lastError()<<"select ЗУР";
    }
    query.exec(select);
    while (query.next())
    {
        max_Nx = query.value(0).toDouble();
        max_Ny= query.value(1).toDouble();
        min_Nx= query.value(2).toDouble();
        max_M= query.value(3).toDouble();
        roof=query.value(4).toDouble();
    }

    QJsonObject launcherJsonObj
    {
        {"id", id},
        {"model_name", "ZUR"}
    };
    QJsonObject launcherJsonInitData
    {
        {"rocket_name",name},
        {"rocket_max_Nx",max_Nx},
        {"rocket_max_Ny",max_Ny},
        {"rocket_min_Nx",min_Nx},
        {"rocket_max_M",max_M},
        {"rocket_practical_roof",roof}
    };
    launcherJsonObj.insert("initial_data", QJsonValue(launcherJsonInitData));
    return launcherJsonObj;
}

void Antiaircraft::set_id(int _id)
{
    id = _id;
}


void Antiaircraft::set_name(QString _name)
{
    name = _name;
}

void Antiaircraft::set_properties(double _max_Nx,
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

QTreeWidgetItem* Antiaircraft::get_item(int count)
{

    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setText(0, "ЗУР_"+QString::number(count)+ ": id: " +QString::number(id));
//    for (int ii=0;ii<list.size() ; ++ii)
//    {
//        QTreeWidgetItem* item_child = new QTreeWidgetItem();
//        item->addChild(item_child);
//        item_child->setText(0,list.at(ii));
//    }
//    QTreeWidgetItem* item_child = new QTreeWidgetItem();
//    item->addChild(item_child);
//    item_child->setText(0,"ЗУР");
//    for (Antiaircraft* ii : rokets)
//    {
//        QTreeWidgetItem* item_roket = new QTreeWidgetItem();
//        item_child->addChild(item_roket);
//        item_roket->setText(0,ii->get_name()+": ID_"+ii->get_id());
//    }

    return item;
}

//--------------------------------------------------

Launcher::Launcher()
{

}

///@note доделать ???
Launcher::Launcher(QJsonObject initData, QSqlDatabase db)
{
    id = initData["id"].toInt();
    x =  initData["x"].toDouble();
    y =  initData["y"].toDouble();
    z =  initData["z"].toDouble();
    radius = initData["radius"].toDouble();
    count_ammo = initData["rockets_amount"].toInt();
    cooldown = initData["cooldown"].toInt();
    name = initData["name"].toString();

    QJsonArray array = initData["zur_id"].toArray();
    for (QJsonValue value : array)
    {
       Antiaircraft *p = new Antiaircraft(value.toObject(),db);
       rokets.append(p);
    }
    calculate_radius(radius);
}

QJsonObject Launcher::toJsonObject()
{
    QJsonObject launcherJsonObj
    {
        {"id", id},
        {"model_name", "PU"}
    };
    QJsonArray zur_id;
    for (Antiaircraft *roket : rokets)
    {
        QJsonObject zur
        {
            {"name", roket->get_name()},
            {"id", roket->get_id()}
        };
        zur_id.append(QJsonValue(zur));
    }
    ///@note переделать
    QJsonObject launcherJsonInitData
    {
        {"x",x},
        {"y",y},
        {"z",z},
        {"radius",radius},
        {"rockets_amount",count_ammo},
        {"cooldown",cooldown},
        {"name",name},
        {"zur_id",QJsonValue(zur_id)},
        {"pbu_id", 0}
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
    calculate_radius(radius);
}

void Launcher::append_zur(Antiaircraft *roket)
{
    rokets.append(roket);
}

QTreeWidgetItem* Launcher::get_item(int count)
{
    QTreeWidgetItem* item = new QTreeWidgetItem();
    QList<QString> list;
    list<<"ID: "+QString::number(id)
       <<"x: "+QString::number(x)
      <<"y: "+QString::number(y)
     <<"z: "+QString::number(z)
    <<"Радиус действия (м): "+QString::number(radius)
    <<"Количество ЗУР: "+QString::number(count_ammo)
    <<"Время перезарядки (c): "+QString::number(cooldown);

    item->setText(0, "ПУ_"+QString::number(count));

    for (int ii=0;ii<list.size() ; ++ii)
    {
         QTreeWidgetItem* item_child = new QTreeWidgetItem();
         item->addChild(item_child);
         item_child->setText(0,list.at(ii));
    }


    return item;
}

void Launcher::calculate_radius(double radius)
{
    for (double t=0; t<2*3.14; t+=0.01)
    {
        vector_radius_x.append(radius*(cos(t))+x);
        vector_radius_y.append(radius*(sin(t))+y);
    }
}
