#include "launcher_model.h"
#include <QDebug>

launcher_model::launcher_model()
{

}

launcher_model::~launcher_model()
{
    time_steps.clear();
    vector_radius_max_range.clear();
    vector_radius_max_z.clear();
    vector_radius_max_x.clear();
    vector_radius_max_y.clear();
    vector_radius_min_x.clear();
    vector_radius_min_y.clear();
    vector_radius_min_range.clear();
    vector_radius_min_z.clear();
}

launcher_model::launcher_model(QJsonObject initData)
{
    id = initData["id"].toInt();
    x =  initData["x"].toDouble();
    y =  initData["y"].toDouble();
    z =  initData["z"].toDouble();
    radius = initData["radius"].toDouble();
    ammo = initData["rockets_amount"].toInt();
    horizontal_range = sqrt(pow(x,2)+pow(y,2));
    calculate_radius_max(radius);
}

void launcher_model::append_step(double _step,
                                 int ammo,
                                 int status)
{
    Step_launcher* s= new Step_launcher;
    s->ammo_curr = ammo;
    s->status_curr = status;
    time_steps.insert(_step,s);
//    qDebug()<<time_steps.last()->ammo_curr<<" step "<<_step;
}