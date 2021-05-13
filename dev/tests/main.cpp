#include <iostream>
#include "rls.h"
#include "pbu.h"
#include "airtarget.h"
#include "ModelingDispatcher.h"

const std::string scenario = "{"
                            "  \"scenario_name\": \"2_objects\","
                            "  \"end_time\": 100.0,"
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
                            "                      }"
                            "          },"
                            "          {"
                            "              \"id\": 2,"
                            "              \"model_name\": \"RLS\","
                            "              \"initial_data\":"
                            "                  { \"coords\": 1.2,"
                            "                   \"observation_params\": 3.2,"
                            "                   \"dispersion\": 1.0"
                            "                                               }"
                            "          },"
                            "          {"
                            "              \"id\": 3,"
                            "              \"model_name\": \"PBU\","
                            "              \"initial_data\":"
                            "                  { \"coords\": 1.7"
                            "                  }"
                            "          }"
 /*                           "          {"
                            "              \"id\": 2,"
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
                            "                      \"y\" : 0,"
                            "                      \"z\" : 0,"
                            "                      \"vel\" : 100"
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
                            "                      }"
                            "          }"*/
                            "      ]"
                            "}";

void printMSG(id_type id, double time, TargetMsg msg)
{
    std::cout << "Message from " << id << " at time " << time << std::endl;
    std::cout << "coord: " << msg.coord[0] << " " << msg.coord[1] << " " << msg.coord[2] << std::endl;
    std::cout << "vel: " << msg.vels[0] << " " << msg.vels[1] << " " << msg.vels[2] << std::endl;
    std::cout << "name: " << msg.name << std::endl;
}

void print_traj_MSG(id_type id, double time, Trajectory msg)
{
    std::cout << "Message from " << id << " at time " << time << std::endl;
    std::cout << "coord: " << msg.target_coords[0] << " " << msg.target_coords[1] << " " << msg.target_coords[2] << std::endl;
    std::cout << "vel: " << msg.target_v[0] << " " << msg.target_v[1] << " " << msg.target_v[2] << std::endl;
    std::cout << "sigma: " << msg.sigma[0] << " " << msg.sigma[1] << " " << msg.sigma[2] << std::endl;
    std::cout << "sigma_half_axis: " << msg.sigma_half_axis[0] << " " << msg.sigma_half_axis[1] << " " << msg.sigma_half_axis[2] << std::endl;
    std::cout << "target_id: " << msg.target_id << std::endl;
}

void printFireMSG(id_type id, double time, Fire msg)
{
    std::cout << "Message from " << id << " at time " << time << std::endl;
    std::cout << "coord: " << msg.pu_target_coords[0] << " " << msg.pu_target_coords[1] << " " << msg.pu_target_coords[2] << std::endl;
    std::cout << "target_id: " << msg.target_id << std::endl;
}

int main(int argc, char* argv[])
{
    std::map<std::string, std::pair<int, ModelFactory*> > factories;
    std::pair<int, ModelFactory*> fac1 = { 1, new AirTargetFactory() };
    factories["AirTarget"] = fac1;

    std::pair<int, ModelFactory*> fac2 = { 2, new RLSFactory() };
    factories["RLS"] = fac2;

    std::pair<int, ModelFactory*> fac3 = { 3, new PBUFactory() };
    factories["PBU"] = fac3;

    ModelingDispatcher md(0.01, factories);
    md.getChannel<Fire>().subscribe(printFireMSG);
    //md.getChannel<Trajectory>().subscribe(print_traj_MSG);
    std::cout << "Starting...\n";
    md.run(scenario);
    std::cout << "finished!\n";
}
