#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <QJsonObject>
#include <QVector>
#include <QJsonArray>

class Launcher
{
public:
    Launcher(QJsonObject initData);
    Launcher();
    Launcher(int id,
             double x,
             double y,
             double z,
             double radius,
             int count_ammo,
             int cooldown
             //,
             //QVector<int> rokets
             );
    QJsonObject toJsonObject();

    void set_id(int id);
    void set_coordinates(double x,
                         double y,
                         double z);
    void set_properties(double radius,
                        int count_ammo,
                        int cooldown);
private:
    int id;
    double x;
    double y;
    double z;
    double radius;
    int count_ammo;
    int cooldown;
    //QVector<int> rokets;
};

class Antiaircraft
{
public:
    Antiaircraft(QJsonObject initData);
    Antiaircraft();
    Antiaircraft(int id,
                 //QString target_name,
                 QString target_model_name,
                 double max_Nx,
                 double max_Ny,
                 double min_Nx,
                 double max_M,
                 double roof);
    QJsonObject toJsonObject();
private:
    //QString target_name = "plane_";
    QString target_model_name;
    int id;
    double max_Nx;
    double max_Ny;
    double min_Nx;
    double max_M;
    double roof;
};

#endif // LAUNCHER_H
