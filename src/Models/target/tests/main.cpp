#include <iostream>

#include "airtarget.h"
#include "ModelingDispatcher.h"

const std::string scenario = "{"
                             "  \"scenario_name\": \"1Target3Points\","
                             "  \"end_time\": 1800.0,"
                             "  \"objects\": "
                             "      ["
                             "          {"
                             "              \"id\": 1,"
                             "              \"model_name\": \"AirTarget\","
                             "              \"initial_data\":"
                             "                  { \"target_name\": \"plane_1\","
                             "                   \"target_model_type\": \"Fighter\","
                             "                   \"target_max_Nx\": 3,"
                             "                   \"target_max_Ny\": 6,"
                             "                   \"target_max_M\": 2,"
                             "                   \"target_min_Nx\": -1.2,"
                             "                   \"target_points\": "
                             "                      ["
                             "                          {"
                                 "                      \"x\" : 0,"
                                 "                      \"y\" : 1000,"
                                 "                      \"z\" : 5000,"
                                 "                      \"vel\" : 300"
                                 "                      },"
                             "                          {"
                                 "                      \"x\" : 2000,"
                                 "                      \"y\" : 2000,"
                                 "                      \"z\" : 5000,"
                                 "                      \"vel\" : 300"
                                 "                      }"
                                 "                   ]"
"                                               }"
                             "          },"
                             "          {"
                             "              \"id\": 2,"
                             "              \"model_name\": \"AirTarget\","
                             "              \"initial_data\":"
                             "                  { \"target_name\": \"plane_2\","
                             "                   \"target_model_type\": \"Fighter\","
                             "                   \"target_max_Nx\": 3,"
                             "                   \"target_max_Ny\": 6,"
                             "                   \"target_max_M\": 2,"
                             "                   \"target_min_Nx\": -1.2,"
                             "                   \"target_points\": "
                             "                      ["
                             "                          {"
                                 "                      \"x\" : 100,"
                                 "                      \"y\" : 1100,"
                                 "                      \"z\" : 5000,"
                                 "                      \"vel\" : 300"
                                 "                      },"
                             "                          {"
                                 "                      \"x\" : 2100,"
                                 "                      \"y\" : 2300,"
                                 "                      \"z\" : 4900,"
                                 "                      \"vel\" : 300"
                                 "                      }"
                                 "                      ]"
"                                               }"
                             "          },"
                             "          {"
                             "              \"id\": 3,"
                             "              \"model_name\": \"AirTarget\","
                             "              \"initial_data\":"
                             "                  { \"target_name\": \"plane_3\","
                             "                   \"target_model_type\": \"Fighter\","
                             "                   \"target_max_Nx\": 3,"
                             "                   \"target_max_Ny\": 6,"
                             "                   \"target_max_M\": 2,"
                             "                   \"target_min_Nx\": -1.2,"
                             "                   \"target_points\": "
                             "                      ["
                             "                          {"
                                 "                      \"x\" : 200,"
                                 "                      \"y\" : 1200,"
                                 "                      \"z\" : 4900,"
                                 "                      \"vel\" : 250"
                                 "                      },"
                             "                          {"
                                 "                      \"x\" : 1600,"
                                 "                      \"y\" : 2300,"
                                 "                      \"z\" : 4800,"
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
    md.msgSubscribe<TargetMsg>(printMSG);
    std::cout << "Starting...\n";
    md.run(scenario);
    std::cout << "finished!\n";

    /*
    GeodezicCoodinates GD_Msc = GeodezicCoodinates(55, 37, 0);

    Vector3D crd(37035.885104, 574478.867425, -15932.8059282);
    //Vector3D crd(0, 0, 0);
    //Vector3D crd(233495.792456, 303480.14781, -11386.4586281);

    GeodezicCoodinates GD = GeocentricToGeodezic(PBUToGeo(GeodezicToGeoCentric(GD_Msc), crd));

    std::cout << GD.latitude << " " << GD.longitude << " " << GD.altitude;*/

    /* GC1(2551014.27811, 2641652.6159, 5209575.04365);
    GeocentricCoodinates GC2(2521759.87014, 2270602.78583, 5394218.20446);
    GeocentricCoodinates GC3(2587663.12314, 2329942.34136, 5325983.96688);

    GeodezicCoodinates GD_Msc = GeodezicCoodinates(55, 37, 0); //костыыыыль

    Vector3D p1 = GeoToPBU(GeodezicToGeoCentric(GD_Msc), GC1);
    Vector3D p2 = GeoToPBU(GeodezicToGeoCentric(GD_Msc), GC2);
    Vector3D p3 = GeoToPBU(GeodezicToGeoCentric(GD_Msc), GC3);

    std::cout << std::setprecision(12) << p1.x << " " << p1.y << " " << p1.z << "\n";
    std::cout << std::setprecision(12) << p2.x << " " << p2.y << " " << p2.z << "\n";
    std::cout << std::setprecision(12) << p3.x << " " << p3.y << " " << p3.z << "\n";
    */
}
