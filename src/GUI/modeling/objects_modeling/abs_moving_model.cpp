#include "abs_moving_model.h"
#include <cmath>
#include <QDebug>

abs_moving_model::abs_moving_model()
{

}

void abs_moving_model::set_id(int id)
{
    this->id = id;
}

void abs_moving_model::append_point(double _step,
                                    double _x,
                                    double _y,
                                    double _z,
                                    int _status)
{
    vector_x.append(_x);
    vector_y.append(_y);
    vector_z.append(_z);
    vector_horizontal_range.append(sqrt(pow(_x,2)+pow(_y,2)));

    Point_model* p= new Point_model;
    p->vector_point_range.append(sqrt(pow(_x,2)+pow(_y,2)));
    p->vector_point_x.append(_x);
    p->vector_point_y.append(_y);
    p->vector_point_z.append(_z);
    p->status=_status;
    points.insert(_step,p);
}

void abs_moving_model::set_name(QString name)
{
    this->name = name;
}
