#ifndef ABS_MOVING_MODEL_H
#define ABS_MOVING_MODEL_H
#include <QString>
#include <QVector>
#include <QMap>
#include <QJsonObject>
//#include <QHash>



struct Point_model
{
    QVector<double> vector_point_x,
    vector_point_y,
    vector_point_z,
    vector_point_range;
    int status;
};

class abs_moving_model
{
public:
    abs_moving_model();
    void set_id(int id);
    void append_point(double _step,
                      double _x,
                      double _y,
                      double _z,
                      int _status);
    void set_name(QString name);
    void set_status(int status){status_modeling = status;}

    void set_graph(int number){number_graph=number;}
    int get_graph(){return number_graph;}

    int get_id(){return id;}

    QMap<double, Point_model*> get_points(){return points;}

    QVector<double> get_vector_x(){return vector_x;}
    QVector<double> get_vector_y(){return vector_y;}
    QVector<double> get_vector_z(){return vector_z;}
    QVector<double> get_vector_range(){return vector_horizontal_range;}

    QString get_name(){return name;}

    ~abs_moving_model();

protected:


    QString name;
    int id;
    int status_modeling = 1;
    int number_graph;

    QMap<double, Point_model*> points;

    QVector<double> vector_x,
    vector_y,
    vector_z,
    vector_horizontal_range;

};

#endif // ABS_MOVING_MODEL_H
