#include "aircraft_model.h"

aircraft_model::aircraft_model()
{

}

aircraft_model::~aircraft_model()
{
    vector_horizontal_range.clear();
    vector_x.clear();
    vector_y.clear();
    vector_z.clear();
    points.clear();
}


aircraft_model::aircraft_model(QJsonObject initData)
{
    id = initData["id"].toInt();
    //model = initData["model"].toString();
    name = initData["target_name"].toString();
    name_model = initData["target_model_type"].toString();
}
