#include "zur_model.h"

zur_model::zur_model()
{

}

zur_model::zur_model(QJsonObject initData)
{
    id = initData["id"].toInt();
    name =  initData["target_name"].toString();
}
