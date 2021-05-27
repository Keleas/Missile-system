#ifndef AIRCRAFT_PBU_H
#define AIRCRAFT_PBU_H
#include "abs_moving_model.h"


class aircraft_pbu: public abs_moving_model
{
public:
    aircraft_pbu();
    ~aircraft_pbu();
    void set_time_spotted(double _time){time_spotted = _time;}
private:
    double time_spotted;
};

#endif // AIRCRAFT_PBU_H
