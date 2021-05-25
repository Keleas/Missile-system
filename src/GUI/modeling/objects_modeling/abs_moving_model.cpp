#include "abs_moving_model.h"

abs_moving_model::abs_moving_model()
{

}

void abs_moving_model::set_id(int id)
{
    this->id = id;
}

void abs_moving_model::append_point(double x,
                                    double y,
                                    double z)
{
    vector_x.append(x);
    vector_y.append(y);
    vector_z.append(z);
    vector_horizontal_range.append(sqrt(pow(x,2)+pow(y,2)));
}

void abs_moving_model::set_name(QString name)
{
    this->name = name;
}
