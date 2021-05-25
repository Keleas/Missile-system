#ifndef LAUNCHER_MODEL_H
#define LAUNCHER_MODEL_H
#include "abs_stationary_model.h"
#include "zur_model.h"

class launcher_model: public abs_stationary_model
{
public:
    launcher_model();
    launcher_model(QJsonObject initData);
    //void set_ammo(int ammo);
    void set_status(bool status);
    void set_ammo(int _ammo){ammo = _ammo;}

private:
    double radius;
    int ammo;
    bool status;
    QHash <int, zur_model> map_zurs;
};

#endif // LAUNCHER_MODEL_H
