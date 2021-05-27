#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include <QJsonObject>
#include <QVector>
#include <QString>
#include <QJsonArray>
#include <QTreeWidget>

class Point
{
public:
    Point(QJsonObject initData);
    QJsonObject toJsonObject();
    Point();
    Point(double x,
          double y,
          double z,
          double velocity);
    void set_point(int point);
    void set_coordinates(double x,
                         double y,
                         double z);
    void set_velocity(double velocity);

    QTreeWidgetItem *get_item(int count);

    double get_x(){return x;}
    double get_y(){return y;}
private:
    int point;
    double x;
    double y;
    double z;
    double velocity;
};

class Aircraft
{
public:
    Aircraft(QJsonObject initData);
    Aircraft();
//    Aircraft(QString target_name,
//             QString target_model_name,
//             int id,
//             double max_Nx,
//             double max_Ny,
//             double min_Nx,
//             double max_M,
//             double roof,
//             QVector<Point> points);
    QJsonObject toJsonObject();

    void set_id(int id);
    void set_name(QString target_name);
    void set_model(QString target_model_name);
    void set_properties(double max_Nx,
                        double max_Ny,
                        double min_Nx,
                        double max_M,
                        double roof);

    QVector<Point*> get_points(){return points;}

    void append_point(Point* _point);

    QTreeWidgetItem *get_item(int count);

    int get_graph(){return number_graph;}
    void set_graph(int number){number_graph = number;}

    QVector<double> get_vector_x();
    QVector<double> get_vector_y();

    int get_id(){return id;};

private:

    int number_graph;
    QString target_name = "plane_";
    QString target_model_name;
    int id;
    double max_Nx;
    double max_Ny;
    double min_Nx;
    double max_M;
    double roof;    
    QVector<Point*> points;

};



#endif // AIRCRAFT_H