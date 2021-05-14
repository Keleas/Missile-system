#ifndef RADAR_H
#define RADAR_H

#include <QJsonObject>
#include <QTreeWidget>

class Radar
{
public:
    Radar(QJsonObject initData);
    Radar();
    Radar(int id,
          double x,
          double y,
          double z,
          int model,
          int count_channels_targets,
          int count_channels_zurs,
//          double rotate_x,
//          double rotate_y,
//          double rotate_z,
          double radius);

    QJsonObject toJsonObject();

    QTreeWidgetItem *get_item();

    void set_id(int id);
    void set_coordinates(double x,
                         double y,
                         double z);
    void set_model(int model);
    void set_properties(int count_channels_targets,
                        int count_channels_zurs,
                        double radius);

private:

    int id;
    double x;
    double y;
    double z;
    int model;
    int count_channels_targets;
    int count_channels_zurs;
//    double rotate_x;
//    double rotate_y;
//    double rotate_z;
    double radius;
};


#endif // RADAR_H
