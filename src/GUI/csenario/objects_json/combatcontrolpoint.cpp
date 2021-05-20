#include "combatcontrolpoint.h"

CombatControlPoint::CombatControlPoint()
{
//    id = 54;
//    x =  600;
//    y =  700;
//    z =  400;
}
CombatControlPoint::CombatControlPoint(int id,
                                       double x,
                                       double y,
                                       double z
                                       /*QVector<Launcher> *id_launchers*/)
{
    this->id = id;
    this->x = x;
    this->x = y;
    this->x = z;
//    this->id_launchers=id_launchers;
}
CombatControlPoint::CombatControlPoint(QJsonObject initData)
{
    id = initData["id"].toInt();
    x =  initData["x"].toDouble();
    y =  initData["y"].toDouble();
    z =  initData["z"].toDouble();
//    QJsonArray array = initData["zur_id"].toArray();
//    for (QJsonValue value : array)
//    {
//        rokets.append(value.toInt());
//    }
    //id_launchers
}

QJsonObject CombatControlPoint::toJsonObject()
{
    QJsonObject pbuJsonObj
    {
        {"id", id},
        {"model_name", "PBU"}
    };
    QJsonObject pbuJsonInitData
    {
        {"x",x},
        {"y",y},
        {"z",z},
    };
    pbuJsonObj.insert("initial_data", QJsonValue(pbuJsonInitData));

    return pbuJsonObj;
}

void CombatControlPoint::set_id(int _id)
{
    id = _id;
}
void CombatControlPoint::set_coordinates(double _x,
                                         double _y,
                                         double _z)
{
    x =_x;
    y = _y;
    z = _z;
}

void CombatControlPoint::clearData()
{
    x=0;
    y=0;
    z=0;
    id=0;
}

QList<QTreeWidgetItem*> CombatControlPoint::get_item()
{
    QStringList list;
    list<<"ID: "+QString::number(id)
       <<"x: "+QString::number(x)
      <<"y: "+QString::number(y)
     <<"z: "+QString::number(z);

    QList<QTreeWidgetItem*> list_items;
    for (int ii=0;ii<list.size() ; ++ii)
    {
        QTreeWidgetItem* item_child = new QTreeWidgetItem();
        item_child->setText(0,list.at(ii));
        list_items.append(item_child);

    }
    return list_items;
}
