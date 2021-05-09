#ifndef AIRTARGET_H
#define AIRTARGET_H

#include <string>

#include "abstractmodel.h"
#include "TrajData.h"
#include "msg_types.h"

constexpr double g = 9.81;

struct AirTargetParams
{
    double MAX_TRANSVERSE_OVERLOAD;
    double MAX_NORMAL_OVERLOAD;
    double MAX_MAH;
    double MIN_TRANSVERSE_OVERLOAD;
};

class AirTarget : public Model
{
public:
    AirTarget(std::string targetName_, AirTargetParams param_);

    void calculate(int num_iter);

    bool init(std::string const& initial_data) override final;
    void firstStep() override final;
    void step(double time) override final;

    TargetStatus get_status();
    Vector3D get_coords();

    void set_status(TargetStatus trg);

    int num_point_passed = 0;

private:
    std::string targetName;
    AirTargetParams param;
    MessageQueue<Explosion> recieve_msg;
    Vector3D coords;
    TargetStatus status = TargetStatus::is_not_fly;

    std::vector<TrajectoryPoint> control_points;
    TrajData data;

    std::vector<double> NuCurLast = {0, 0, 0};
    std::vector<double> NuCurNextLast = {0, 0, 0};
    std::vector<double> AccelsLast = {0, 0, 0};
    double NormLast = 0;
    double TransLast = 0;
    double HorizLast = 0;
    double BankLast = 0;
    double WayLast = 0;
};

Vector3D GeoToLocal(GeodezicCoodinates GD, GeocentricCoodinates GC, GeocentricCoodinates GC0);
GeocentricCoodinates LocalToGeo(GeodezicCoodinates GD, Vector3D Loc, GeocentricCoodinates GC0);

#endif // AIRTARGET_H
