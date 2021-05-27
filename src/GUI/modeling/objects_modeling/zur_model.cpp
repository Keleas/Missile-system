#include "zur_model.h"

zur_model::zur_model()
{

}

zur_model::~zur_model()
{
    vector_horizontal_range.clear();
    vector_x.clear();
    vector_y.clear();
    vector_z.clear();
    points.clear();
}

zur_model::zur_model(QJsonObject initData)
{
    id = initData["id"].toInt();
    name =  initData["target_name"].toString();
}
