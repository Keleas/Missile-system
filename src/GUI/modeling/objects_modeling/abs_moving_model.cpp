#include "abs_moving_model.h"

abs_moving_model::abs_moving_model()
{

}

void abs_moving_model::set_id(int id)
{
    this->id = id;
}

void abs_moving_model::set_point(double x,
                                 double y,
                                 double z)
{
    Point point;
    point.x = x;
    point.y = y;
    point.z = z;
    point.horizontal_range = sqrt(pow(x,2)+pow(y,2));
    points.append(point);
}

void abs_moving_model::set_name(QString name)
{
    this->name = name;
}
