#ifndef ABS_STATIONARY_MODEL_H
#define ABS_STATIONARY_MODEL_H
#include <QString>
#include <QJsonObject>
#include <QVector>

class abs_stationary_model
{
public:
    abs_stationary_model();

    void set_id(int id);
    void set_coordinates(double x,
                         double y,
                         double z);
    void set_name(QString name);
    QString get_name(){return name;}

    double get_x(){return x;}
    double get_y(){return y;}
    double get_z(){return z;}
    double get_range(){return horizontal_range;}

    QVector<double> get_rad_min_x(){return vector_radius_min_x;}
    QVector<double> get_rad_min_y(){return vector_radius_min_y;}
    QVector<double> get_rad_min_z(){return vector_radius_min_z;}
    QVector<double> get_rad_min_range(){return vector_radius_min_range;}

    QVector<double> get_rad_max_x(){return vector_radius_max_x;}
    QVector<double> get_rad_max_y(){return vector_radius_max_y;}
    QVector<double> get_rad_max_z(){return vector_radius_max_z;}
    QVector<double> get_rad_max_range(){return vector_radius_max_range;}

    void set_graph(int number){number_graph=number;}
    int get_graph(){return number_graph;}

    ~abs_stationary_model();

protected:

    QString name;
    int id;

    double x;
    double y;
    double z;
    double horizontal_range;

    double radius_min, radius_max;

    QVector<double> vector_radius_min_x,vector_radius_min_y,vector_radius_min_z,vector_radius_min_range,
    vector_radius_max_x,vector_radius_max_y,vector_radius_max_z,vector_radius_max_range;

    void calculate_radius_max(double radius);
    void calculate_radius_min(double radius);

    int number_graph;
};

#endif // ABS_STATIONARY_MODEL_H
