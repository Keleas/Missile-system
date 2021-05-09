#include <iostream>

#include "airtarget.h"
#include "ModelingDispatcher.h"

const std::string scenario = "{"
                             "  \"end_time\": 10000.0,"
                             "  \"objects\": "
                             "      ["
                             "          {"
                             "              \"id\": 1,"
                             "              \"model_name\": \"AirTarget\","
                             "              \"initial_data\":"
                             "                  { \"target_name\": \"plane_1\","
                             "                   \"target_max_Nx\": 3,"
                             "                   \"target_max_Ny\": 6,"
                             "                   \"target_max_M\": 2,"
                             "                   \"target_min_Nx\": -1.2,"
                             "                   \"target_points\": "
                             "                      ["
                             "                          {"
                                 "                      \"x\" : 2551014.27811,"
                                 "                      \"y\" : 2641652.6159,"
                                 "                      \"z\" : 5209575.04365,"
                                 "                      \"vel\" : 300"
                                 "                      },"
                             "                          {"
                                 "                      \"x\" : 2521759.87014,"
                                 "                      \"y\" : 2270602.78583,"
                                 "                      \"z\" : 5394218.20446,"
                                 "                      \"vel\" : 300"
                                 "                      },"
                             "                          {"
                                 "                      \"x\" : 2587663.12314,"
                                 "                      \"y\" : 2329942.34136,"
                                 "                      \"z\" : 5325983.96688,"
                                 "                      \"vel\" : 300"
                                 "                      }"
                                 "                      ]"
"                                               }"
                             "          }"
                             "      ]"
                             "}";

void printMSG(id_type id, double time, TargetMsg msg)
{
    std::cout << "Message from " << id << " at time " << time <<std::endl;
    std::cout << "coord: " << msg.coord[0] << " " << msg.coord[1] << " " << msg.coord[2] << std::endl;
    std::cout << "vel: " << msg.vels[0] << " " << msg.vels[1] << " " << msg.vels[2] << std::endl;
    std::cout << "name: " << msg.name << std::endl;
}

int main(int argc, char *argv[])
{
    std::map<std::string, std::pair<int, ModelFactory*> > factories;
    std::pair<int, ModelFactory*> fac1 = {1, new AirTargetFactory()};
    factories["AirTarget"] = fac1;

    ModelingDispatcher md(0.01, factories);
    md.getChannel<TargetMsg>().subscribe(printMSG);
    std::cout << "Starting...\n";
    md.run(scenario);
    std::cout << "finished!\n";

    /*GeodezicCoodinates start (55, 45, 10000);
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

    std::cout << data1.nPoints;*/

//    QFile file("results.txt");
//    file.open(QIODevice::Append);
//    QTextStream io(&file);
//
//    for (int i = 0; i < data1.nPoints; i++)
//    {
//        io << data1.xPos[i] << " " << data1.yPos[i] << " " << data1.zPos[i] << "\n";
//    }
//
//    file.close();
}
