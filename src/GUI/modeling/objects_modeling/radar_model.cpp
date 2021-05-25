#include "radar_model.h"

radar_model::radar_model()
{

}


radar_model::radar_model(QJsonObject initData)
{
    id = initData["id"].toInt();
    //model = initData["model"].toString();

    x =  initData["x"].toDouble();
    y =  initData["y"].toDouble();
    z =  initData["z"].toDouble();

    Dmax = initData["Dmax"].toDouble();
    Dmin = initData["Dmin"].toDouble();

}

void radar_model::set_radius(double radius)
{
    //this->radius = radius;
}


