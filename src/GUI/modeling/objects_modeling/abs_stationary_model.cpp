#include "abs_stationary_model.h"

abs_stationary_model::abs_stationary_model()
{

}

void abs_stationary_model::set_id(int id)
{
    this->id = id;
}

void abs_stationary_model::set_coordinates(double x,
                                           double y,
                                           double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
    horizontal_range = sqrt(pow(x,2)+pow(y,2));
}

void abs_stationary_model::set_name(QString name)
{
    this->name = name;
}
