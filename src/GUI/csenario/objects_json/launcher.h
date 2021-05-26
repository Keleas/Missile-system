#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <QJsonObject>
#include <QVector>
#include <QJsonArray>
#include <QTreeWidget>
#include <QtSql>


class Antiaircraft
{
public:
    Antiaircraft(QJsonObject initData,QSqlDatabase db);
    Antiaircraft();
    QJsonObject toJsonObject(QSqlDatabase db);
    QTreeWidgetItem *get_item(int count);
    void set_properties(double max_Nx,
                        double max_Ny,
                        double min_Nx,
                        double max_M,
                        double roof);
    void set_id(int id);
    void set_name(QString name);
    QString get_name(){return name;};
    int get_id(){return id;};
private:
    QString name;
    int id;
    double max_Nx;
    double max_Ny;
    double min_Nx;
    double max_M;
    double roof;
};

class Launcher
{
public:
    Launcher(QJsonObject initData, QSqlDatabase db);
    Launcher();

    QJsonObject toJsonObject();

    void set_id(int id);
    void set_coordinates(double x,
                         double y,
                         double z);
    void set_properties(double radius,
                        int count_ammo,
                        int cooldown);
    void append_zur(Antiaircraft* roket);
    QTreeWidgetItem *get_item(int count);
    int count_zur(){return count_ammo;};
    QVector<Antiaircraft*> get_zurs(){return rokets;};
    void set_name(QString _name){name=_name;}
    double get_x(){return x;}
    double get_y(){return y;}
    int get_id(){return id;};

private:
    int id;
    double x;
    double y;
    double z;
    double radius;
    int count_ammo;
    int cooldown;
    QString name;
    QVector<Antiaircraft*> rokets;
};



#endif // LAUNCHER_H
