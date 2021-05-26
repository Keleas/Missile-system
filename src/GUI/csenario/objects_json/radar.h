#ifndef RADAR_H
#define RADAR_H

#include <QJsonObject>
#include <QTreeWidget>
#include <QtSql>

class Radar
{
public:
    Radar(QJsonObject initData);
    Radar();


    QJsonObject toJsonObject();

    QTreeWidgetItem *get_item(int count);

    void set_id(int id);
    void set_coordinates(double x,
                         double y,
                         double z);
    void set_model(QString model);
    void set_is_pisets_kolya(QString model,QSqlDatabase db);
    void set_rotates(double _rotate_x,
                     double _rotate_y,
                     double _rotate_z);
    void set_name(QString _name){name=_name;}

    int get_graph(){return number_graph;}
    void set_graph(int number){number_graph = number;}

    double get_x(){return x;}
    double get_y(){return y;}

    int get_id(){return id;};
    QVector<double> get_rad_min_x(){return vector_radius_min_x;}
    QVector<double> get_rad_min_y(){return vector_radius_min_y;}
    QVector<double> get_rad_max_x(){return vector_radius_max_x;}
    QVector<double> get_rad_max_y(){return vector_radius_max_y;}

private:

    int id;
    double x;
    double y;
    double z;
    double rotate_x;
    double rotate_y;
    double rotate_z;

    QString model;
    QString name;

    double lambda,Dmax,Dmin,Tscan,Timp,V_res,asimres,elevres,asimrestracecf,
    elevrestracecf,elev1,elev2,Nasim,Nelev,Bandwidth, Noise, Gain, P_peak, Tr;

    double count_channels_targets; ///Ntraj
    double count_channels_zurs; ///Nmissiles;

    int number_graph;

    void calculate_radius(double radius_min, double radius_max);

    QVector<double> vector_radius_min_x,vector_radius_min_y,
    vector_radius_max_x,vector_radius_max_y;
};


#endif // RADAR_H
