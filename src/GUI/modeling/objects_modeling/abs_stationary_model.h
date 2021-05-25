#ifndef ABS_STATIONARY_MODEL_H
#define ABS_STATIONARY_MODEL_H
#include <QString>
#include <QJsonObject>

class abs_stationary_model
{
public:
    abs_stationary_model();

    void set_id(int id);
    void set_coordinates(double x,
                         double y,
                         double z);
    void set_name(QString name);

    double get_x(){return x;}
    double get_y(){return y;}
    double get_z(){return z;}
    double get_range(){return horizontal_range;}

protected:
    QString name;
    int id;

    double x;
    double y;
    double z;
    double horizontal_range;
};

#endif // ABS_STATIONARY_MODEL_H
