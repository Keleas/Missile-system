#include <iostream>

#include "airtarget.h"
#include "ModelingDispatcher.h"

const std::string scenario = "{"
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
                                 "                      \"x\" : 37035.885104,"
                                 "                      \"y\" : 574478.867425,"
                                 "                      \"z\" : -15932.8059282,"
                                 "                      \"vel\" : 300"
                                 "                      },"
                             "                          {"
                                 "                      \"x\" : 345000.604917,"
                                 "                      \"y\" : 295751.039344,"
                                 "                      \"z\" : -6164.34553825,"
                                 "                      \"vel\" : 300"
                                 "                      },"
                             "                          {"
                                 "                      \"x\" : 233495.792456,"
                                 "                      \"y\" : 303480.14781,"
                                 "                      \"z\" : -11386.4586281,"
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
