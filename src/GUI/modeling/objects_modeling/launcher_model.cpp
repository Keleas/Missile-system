#include "launcher_model.h"

launcher_model::launcher_model()
{

}


launcher_model::launcher_model(QJsonObject initData)
{
    id = initData["id"].toInt();
    x =  initData["x"].toDouble();
    y =  initData["y"].toDouble();
    z =  initData["z"].toDouble();
    radius = initData["radius"].toDouble();
    ammo = initData["rockets_amount"].toInt();



    //QJsonArray array = initData["zur_id"].toArray();
}
