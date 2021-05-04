#ifndef AIRTARGET_H
#define AIRTARGET_H

#include "TrajData.h"
#include <string>

constexpr double g = 9.81;

struct AirTargetParams
{
    double MAX_TRANSVERSE_OVERLOAD;
    double MAX_NORMAL_OVERLOAD;
    double MAX_MAH;
    double MIN_TRANSVERSE_OVERLOAD;
};

class AirTarget
{
public:
    AirTarget(std::string targetName_, AirTargetParams param_);
    std::vector<double> NuCurLast;
    std::vector<double> NuCurNextLast;
    std::vector<double> AccelsLast;
    double NormLast;
    double TransLast;
    double HorizLast;
    double BankLast;
    double WayLast;

    void calculate(const std::vector<TrajectoryPoint> &points, TrajData &data, int num_iter = -1, std::vector<double> cur_vec_vel = {},
                   std::vector<double> next_vec_vel_ = {}, std::vector<double> AccelsLast_ = {}, double NormLast_ = 0, double TransLast_ = 0,
                   double HorizLast_ = 0, double BankLast_ = 0, double WayLast_ = 0);

private:
    std::string targetName;
    AirTargetParams param;
};

Vector3D GeoToLocal(GeodezicCoodinates GD, GeocentricCoodinates GC, GeocentricCoodinates GC0);
GeocentricCoodinates LocalToGeo(GeodezicCoodinates GD, Vector3D Loc, GeocentricCoodinates GC0);

#endif // AIRTARGET_H
