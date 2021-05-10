#ifndef AIRTARGET_H
#define AIRTARGET_H

#include <string>
#include <fstream>

#include "abstractmodel.h"
#include "modelfactory.h"
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
    AirTarget(id_type id, MsgChannelCarrier& carrier);

    void calculate(double dt);

    bool init(const rapidjson::Value &initial_data) override final;
    void firstStep() override final;
    void step(double time) override final;
    void endStep() override final {write_to_file("target_crd.txt", control_points);};

    TargetStatus get_status();
    Vector3D get_coords();

    void set_status(TargetStatus trg);

    int num_point_passed = 0;
    void write_to_file(std::string file_name, std::vector<TrajectoryPoint> points = {});
    void write_to_csv(bool fisrt_time=false);

private:
    std::string targetName;
    std::string targetModelType;
    AirTargetParams param;
    MessageQueue<Explosion> recieve_msg;
    Vector3D coords;
    TargetStatus status = TargetStatus::is_not_fly;

    std::vector<TrajectoryPoint> control_points;
    TrajData data;

    Vector3D NuCurNext;

    GeodezicCoodinates GD_Msc = GeodezicCoodinates(55, 37, 0); //����������

    void TransformForCalculate();

};

inline void AirTarget::write_to_file(std::string file_name, std::vector<TrajectoryPoint> points)
{
    std::ofstream ofs(file_name);

    int k = 0;

    for (int i = 0; i < data.nPoints; i++)
    {
        GeocentricCoodinates GC(data.xPos[i], data.yPos[i], data.zPos[i]);
        GeodezicCoodinates GD = GeocentricToGeodezic(GC);
        ofs << GD.latitude << " " << GD.longitude << " " << GD.altitude;
        if (!points.empty())
        {
            std::string s1 = std::to_string(points[k].initialPoint.x);
            std::string s2 = std::to_string(points[k].initialPoint.y);
            std::string s3 = std::to_string(points[k].initialPoint.z);

            std::string w1 = std::to_string(GC.x);
            std::string w2 = std::to_string(GC.y);
            std::string w3 = std::to_string(GC.z);

            if (s1 == w1 && s2 == w2 && s3 == w3)
            {
                ofs << " control_point";
                k++;
            }
        }
        ofs << "\n";
    }

    ofs.close();
}

inline void AirTarget::write_to_csv(bool fisrt_time)
{
    std::string name = "test.csv";
    std::string sep = ", ";

    if (fisrt_time)
    {
        std::ofstream ofs(name);
        ofs << "Target_type" << sep << "Id" << sep << "X" << sep << "Y" << sep
            << "Z" << sep << "Vx" << sep << "Vy" << sep << "Vz" << sep << "Elevation" << sep
            << "Azimut" << sep << "Status" << "\n";
    }
    else
    {
        std::ofstream ofs(name, std::ofstream::app);

        GeocentricCoodinates GC = {data.xPos.back(), data.yPos.back(), data.zPos.back()};
        //GeodezicCoodinates crd = GeocentricToGeodezic(GC);
        Vector3D crd = GeoToPBU(GeodezicToGeoCentric(GD_Msc), GC);

        ofs << targetModelType << sep << id << sep << crd.x << sep << crd.y << sep
            << crd.z << sep << data.xVel.back() << sep << data.yVel.back() << sep
            << data.zVel.back() << sep << data.angle_horizontal_plane.back() << sep
            << data.wayAngle.back() << sep << int(status) << "\n";
    }
}

DEFAULT_MODEL_FACTORY(AirTarget)

Vector3D GeoToLocal(GeodezicCoodinates GD, GeocentricCoodinates GC, GeocentricCoodinates GC0);
GeocentricCoodinates LocalToGeo(GeodezicCoodinates GD, Vector3D Loc, GeocentricCoodinates GC0);

#endif // AIRTARGET_H