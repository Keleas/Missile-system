#ifndef ABS_MOVING_MODEL_H
#define ABS_MOVING_MODEL_H
#include <QString>
#include <QVector>

class abs_moving_model
{
public:
    abs_moving_model();
    void set_id(int id);
    void set_point(double x,
                   double y,
                   double z);
    void set_name(QString name);
protected:
    QString name;
    int id;

    struct Point
    {
        double x;
        double y;
        double z;
        double horizontal_range;
    };

    QVector<Point> points;

};

#endif // ABS_MOVING_MODEL_H
