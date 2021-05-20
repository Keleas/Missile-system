#ifndef LAUNCHER_MODEL_H
#define LAUNCHER_MODEL_H
#include "abs_stationary_model.h"

class launcher_model: public abs_stationary_model
{
public:
    launcher_model();
    void set_radius(double radius);
    void set_ammo(int ammo);
    void set_status(bool status);

private:
    double radius;
    int ammo;
    bool status;
};

#endif // LAUNCHER_MODEL_H
