#ifndef ABS_STATIONARY_MODEL_H
#define ABS_STATIONARY_MODEL_H
#include <QString>

class abs_stationary_model
{
public:
    abs_stationary_model();

    void set_id(int id);
    void set_coordinates(double x,
                         double y,
                         double z);
    void set_name(QString name);
protected:
    QString name;
    int id;

    double x;
    double y;
    double z;
    double horizontal_range;
};

#endif // ABS_STATIONARY_MODEL_H
