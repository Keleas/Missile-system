#ifndef RADAR_MODEL_H
#define RADAR_MODEL_H
#include "abs_stationary_model.h"


class radar_model: public abs_stationary_model
{
public:
    radar_model();
    radar_model(QJsonObject initData);
    void set_radius(double radius);

private:
    double Dmax;
    double Dmin;

};

#endif // RADAR_MODEL_H
