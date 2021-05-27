#include "radar_model.h"

radar_model::radar_model()
{

}

radar_model::~radar_model()
{
    vector_radius_max_range.clear();
    vector_radius_max_z.clear();
    vector_radius_max_x.clear();
    vector_radius_max_y.clear();
    vector_radius_min_x.clear();
    vector_radius_min_y.clear();
    vector_radius_min_range.clear();
    vector_radius_min_z.clear();
}

radar_model::radar_model(QJsonObject initData)
{
    id = initData["id"].toInt();
    //model = initData["model"].toString();

    x =  initData["x"].toDouble();
    y =  initData["y"].toDouble();
    z =  initData["z"].toDouble();

    horizontal_range = sqrt(pow(x,2)+pow(y,2));

    Dmax = initData["Dmax"].toDouble();
    Dmin = initData["Dmin"].toDouble();

    calculate_radius_max(Dmax);
    calculate_radius_min(Dmin);

}

void radar_model::set_radius(double radius)
{
    //this->radius = radius;
}


