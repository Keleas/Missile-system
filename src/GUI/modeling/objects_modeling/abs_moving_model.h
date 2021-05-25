#ifndef ABS_MOVING_MODEL_H
#define ABS_MOVING_MODEL_H
#include <QString>
#include <QVector>
#include <QHash>
#include <QJsonObject>

class abs_moving_model
{
public:
    abs_moving_model();
    void set_id(int id);
    void append_point(double x,
                      double y,
                      double z);
    void set_name(QString name);
    void set_status(int status){status_modeling = status;}

    void set_graph(int number){number_graph=number;}
    int get_graph(){return number_graph;}

    int get_id(){return id;}

    QVector<double> get_vector_x(){return vector_x;}
    QVector<double> get_vector_y(){return vector_y;}
    QVector<double> get_vector_z(){return vector_z;}
    QVector<double> get_vector_range(){return vector_horizontal_range;}

protected:
    QString name;
    int id;
    int status_modeling = 1;

    int number_graph;

    struct Point
    {
        double x,
        y,
        z,
        horizontal_range;
        int status;
    };

    QMap<double, Point*> *points;

    QVector<double> vector_x,
    vector_y,
    vector_z,
    vector_horizontal_range;

};

#endif // ABS_MOVING_MODEL_H
