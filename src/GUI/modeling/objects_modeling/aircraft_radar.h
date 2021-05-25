#ifndef AIRCRAFT_RADAR_H
#define AIRCRAFT_RADAR_H
#include "abs_moving_model.h"

class aircraft_radar: public abs_moving_model
{
public:
    aircraft_radar();
    void set_time_spotted(double _time){time_spotted = _time;}
private:
    double time_spotted;
};

#endif // AIRCRAFT_RADAR_H
