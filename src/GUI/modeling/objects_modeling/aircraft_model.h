#ifndef AIRCRAFT_MODEL_H
#define AIRCRAFT_MODEL_H
#include "abs_moving_model.h"


class aircraft_model: public abs_moving_model
{
public:
    aircraft_model();
    aircraft_model(QJsonObject initData);
private:
    QString name_model;

};

#endif // AIRCRAFT_MODEL_H
