#ifndef RADAR_MODEL_H
#define RADAR_MODEL_H
#include "abs_stationary_model.h"
#include "aircraft_radar.h"


class radar_model: public abs_stationary_model
{
public:
    radar_model();
    radar_model(QJsonObject initData);
    void set_radius(double radius);

    void append_aircraft(aircraft_radar* craft){};

private:
    double Dmax;
    double Dmin;

    QHash <int, aircraft_radar*> hash_aircrafts_radar;
};

#endif // RADAR_MODEL_H
