#ifndef COMBATCONTROLPOINT_H
#define COMBATCONTROLPOINT_H

#include <QJsonObject>
#include <QVector>
#include "launcher.h"
#include <QTreeWidget>

class CombatControlPoint
{
public:
    CombatControlPoint(QJsonObject initData);
    CombatControlPoint();
    CombatControlPoint(int id,
                       double x,
                       double y,
                       double z/*,
                       QVector<Launcher> *id_launchers*/);
    QJsonObject toJsonObject();
    void set_id(int id);
    void set_coordinates(double x,
                         double y,
                         double z);
    void clearData();
    double get_x(){return x;}
    double get_y(){return y;}
    QList<QTreeWidgetItem *> get_item();
private:
    int id;
    double x;
    double y;
    double z;
    //QVector<Launcher> *id_launchers;

};

#endif // COMBATCONTROLPOINT_H
