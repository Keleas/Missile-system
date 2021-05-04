#include <QCoreApplication>
#include <iostream>
#include <QFile>

#include "airtarget.h"

int main(int argc, char *argv[])
{
    GeodezicCoodinates start (55, 45, 10000);
    double vel1 = 200;
    GeodezicCoodinates finish (55, 45.2, 10000);
    double vel2 = 300;

    TrajectoryPoint point_start(GeodezicToGeoCentric(start), vel1);
    TrajectoryPoint point_finish(GeodezicToGeoCentric(finish), vel2);

    std::vector<TrajectoryPoint> points;
    points.push_back(point_start);
    points.push_back(point_finish);

    AirTargetParams params;
    params.MAX_MAH = 2;
    params.MAX_NORMAL_OVERLOAD = 6;
    params.MAX_TRANSVERSE_OVERLOAD = 2;
    params.MIN_TRANSVERSE_OVERLOAD = -1.2;

    AirTarget target1 ("plane1", params);

    TrajData data1;

    target1.calculate(points, data1);

    std::cout << data1.nPoints;

    QFile file("results.txt");
    file.open(QIODevice::Append);
    QTextStream io(&file);

    for (int i = 0; i < data1.nPoints; i++)
    {
        io << data1.xPos[i] << " " << data1.yPos[i] << " " << data1.zPos[i] << "\n";
    }

    file.close();
}
