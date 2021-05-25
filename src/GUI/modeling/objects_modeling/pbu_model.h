#ifndef PBU_MODEL_H
#define PBU_MODEL_H
#include "abs_stationary_model.h"


class pbu_model: public abs_stationary_model
{
public:
    pbu_model();
    pbu_model(QJsonObject initData);
    void set_data(int id, double x, double y);

private:
    int id;
    double x;
    double y;
    double z =0;
    double dal = 0;
};

#endif // PBU_MODEL_H
