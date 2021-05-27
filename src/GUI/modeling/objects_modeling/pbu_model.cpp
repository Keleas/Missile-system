#include "pbu_model.h"

pbu_model::pbu_model()
{

}

pbu_model::~pbu_model()
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

pbu_model::pbu_model(QJsonObject initData)
{
    id = initData["id"].toInt();
    //model = initData["model"].toString();

    x =  initData["x"].toDouble();
    y =  initData["y"].toDouble();
    z =  initData["z"].toDouble();
    horizontal_range = sqrt(pow(x,2)+pow(y,2));
}

//void pbu_model::
