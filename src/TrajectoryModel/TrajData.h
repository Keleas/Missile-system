#ifndef TRAJDATA_H
#define TRAJDATA_H

#include <vector>
#include <Vector3D.h>

struct TrajectoryPoint
{

    Vector3D initialPoint;

    double initialVel;

    TrajectoryPoint() = default;
    TrajectoryPoint(double _x, double _y, double _z, double _vel);
    TrajectoryPoint(GeocentricCoodinates _point, double _vel);
};

inline TrajectoryPoint::TrajectoryPoint(double _x, double _y, double _z, double _vel) :
    initialPoint(_x, _y, _z), initialVel(_vel) {}

inline TrajectoryPoint::TrajectoryPoint(GeocentricCoodinates _point, double _vel) :
    initialPoint(_point), initialVel(_vel) {}

struct TrajData
{
    int nPoints = 0;
    std::vector<double> times;
    std::vector<double> xPos;
    std::vector<double> yPos;
    std::vector<double> zPos;
    std::vector<double> xVel;
    std::vector<double> yVel;
    std::vector<double> zVel;
    std::vector<double> xAcc;
    std::vector<double> yAcc;
    std::vector<double> zAcc;
    std::vector<double> bankAngle;
    std::vector<double> angle_horizontal_plane;
    std::vector<double> wayAngle;
    std::vector<double> transverseOverload;
    std::vector<double> normalOverload;

    void resize(int n);
    void insert(int pos, std::vector<Vector3D> _points, std::vector<Vector3D> _vel,
                std::vector<Vector3D> _acc, std::vector<double> _bankAngle, std::vector<double> _horizontal_plane,
                std::vector<double> wayAngle, std::vector<double> _transverseOverload, std::vector<double> _normalOverload,
                double dt);
};

inline void TrajData::resize(int n)
{
    nPoints = n;
    times.resize(n);
    xPos.resize(n);
    yPos.resize(n);
    zPos.resize(n);
    xVel.resize(n);
    yVel.resize(n);
    zVel.resize(n);
    xAcc.resize(n);
    yAcc.resize(n);
    zAcc.resize(n);
    bankAngle.resize(n);
    angle_horizontal_plane.resize(n);
    wayAngle.resize(n);
    transverseOverload.resize(n);
    normalOverload.resize(n);
}

inline void TrajData::insert(int pos, std::vector<Vector3D> _points, std::vector<Vector3D> _vel,
                             std::vector<Vector3D> _acc, std::vector<double> _bankAngle,
                             std::vector<double> _horizontal_plane, std::vector<double> _wayAngle,
                             std::vector<double> _transverseOverload,
                             std::vector<double> _normalOverload, double dt)
{
    resize(pos + _points.size());

    for (int i = pos; i < nPoints; i++)
    {
        times[i] = i * dt;
        xPos[i] = _points[i-pos].x;
        yPos[i] = _points[i-pos].y;
        zPos[i] = _points[i-pos].z;
        xVel[i] = _vel[i-pos].x;
        yVel[i] = _vel[i-pos].y;
        zVel[i] = _vel[i-pos].z;
        xAcc[i] = _acc[i-pos].x;
        yAcc[i] = _acc[i-pos].y;
        zAcc[i] = _acc[i-pos].z;
        bankAngle[i] = _bankAngle[i-pos];
        angle_horizontal_plane[i] = _horizontal_plane[i-pos];
        wayAngle[i] = _wayAngle[i-pos];
        transverseOverload[i] = _transverseOverload[i-pos];
        normalOverload[i] = _normalOverload[i-pos];
    }
}

#endif // TRAJDATA_H
