#include "pbu_model.h"

pbu_model::pbu_model()
{

}

pbu_model::pbu_model(QJsonObject initData)
{
    id = initData["id"].toInt();
    //model = initData["model"].toString();

    x =  initData["x"].toDouble();
    y =  initData["y"].toDouble();
    z =  initData["z"].toDouble();
}

//void pbu_model::
