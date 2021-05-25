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

private:

    int id;
    double x;
    double y;
    double z;
    double rotate_x;
    double rotate_y;
    double rotate_z;

    QString model;

    double lambda,Dmax,Dmin,Tscan,Timp,V_res,asimres,elevres,asimrestracecf,
    elevrestracecf,elev1,elev2,Nasim,Nelev,Bandwidth, Noise, Gain, P_peak, Tr;

    double count_channels_targets; ///Ntraj
    double count_channels_zurs; ///Nmissiles;
};


#endif // RADAR_H
