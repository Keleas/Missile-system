#ifndef RADAR_MODEL_H
#define RADAR_MODEL_H
#include "abs_stationary_model.h"


class radar_model: public abs_stationary_model
{
public:
    radar_model();
    void set_radius(double radius);

private:
    double radius;
};

#endif // RADAR_MODEL_H
