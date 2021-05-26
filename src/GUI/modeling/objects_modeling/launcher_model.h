#ifndef LAUNCHER_MODEL_H
#define LAUNCHER_MODEL_H
#include "abs_stationary_model.h"
#include "zur_model.h"

struct Step_launcher
{
    int ammo_curr;
    int status_curr;
};

class launcher_model: public abs_stationary_model
{
public:
    launcher_model();
    launcher_model(QJsonObject initData);
    //void set_ammo(int ammo);
    void set_ammo(int _ammo){ammo = _ammo;}
    int get_ammo(){return ammo;}
    void append_step(double _step,
                     int ammo,
                     int status);
    QMap <double, Step_launcher*> get_steps(){return time_steps;}


private:

    double radius;
    int ammo;

    QMap <double, Step_launcher*> time_steps;

    QMap <int, zur_model> map_zurs;
};

#endif // LAUNCHER_MODEL_H
