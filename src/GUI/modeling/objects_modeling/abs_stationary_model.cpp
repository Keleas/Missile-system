#include "abs_stationary_model.h"
#include <cmath>
#include <QDebug>

abs_stationary_model::abs_stationary_model()
{

}

abs_stationary_model::~abs_stationary_model()
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
    horizontal_range = sqrt(pow(this->x,2)+pow(this->y,2));
}

void abs_stationary_model::set_name(QString name)
{
    this->name = name;
}

void abs_stationary_model::calculate_radius_max(double radius)
{
    for (double t=0; t<2*3.14; t+=0.01)
    {
        vector_radius_max_x.append(radius*(cos(t))+x);
        vector_radius_max_y.append(radius*(sin(t))+y);
    }
    for (double t=0; t<3.14; t+=0.01)
    {
        vector_radius_max_range.append(radius*(cos(t))+horizontal_range);
        vector_radius_max_z.append(radius*(sin(t))+z);
    }
}

void abs_stationary_model::calculate_radius_min(double radius)
{
    for (double t=0; t<2*3.14; t+=0.01)
    {
        vector_radius_min_x.append(radius*(cos(t))+x);
        vector_radius_min_y.append(radius*(sin(t))+y);
    }
    for (double t=0; t<3.14; t+=0.01)
    {
        vector_radius_min_range.append(radius*(cos(t))+horizontal_range);
        vector_radius_min_z.append(radius*(sin(t))+z);
    }
}
