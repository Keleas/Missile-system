#include <iostream>

#include "rls.h"
#include "ModelingDispatcher.h"

const std::string scenario = "{"
                             "  \"scenario_name\": \"rls_init\","
                             "  \"end_time\": 100.0,"
                             "  \"objects\": "
                             "      ["
                             "          {"
                             "              \"id\": 1,"
                             "              \"model_name\": \"RLS\","
                             "              \"initial_data\":"
                             "                  { \"coords\": \"1.2\","
                             "                   \"observation_params\": \"3.2\","
                             "                   \"dispersion\": 1.0"
"                                               }"
                             "          }"
                             "      ]"
                             "}";

void printMSG(id_type id, double time, Trajectory msg)
{
    std::cout << "Message from " << id << " at time " << time <<std::endl;
    std::cout << "coord: " << msg.target_coords[0] << " " << msg.target_coords[1] << " " << msg.target_coords[2] << std::endl;
    std::cout << "vel: " << msg.target_v[0] << " " << msg.target_v[1] << " " << msg.target_v[2] << std::endl;
    std::cout << "sigma: " << msg.sigma[0] << " " << msg.sigma[1] << " " << msg.sigma[2] << std::endl;
    std::cout << "sigma_half_axis: " << msg.sigma_half_axis[0] << " " << msg.sigma_half_axis[1] << " " << msg.sigma_half_axis[2] << std::endl;
    std::cout << "target_id: " << msg.target_id << std::endl;
}

int main(int argc, char *argv[])
{
    std::map<std::string, std::pair<int, ModelFactory*> > factories;
    std::pair<int, ModelFactory*> fac1 = {1, new RLSFactory()};
    factories["RLS"] = fac1;

    ModelingDispatcher md(0.01, factories);
    md.getChannel<Trajectory>().subscribe(printMSG);
    std::cout << "Starting...\n";
    md.run(scenario);
    std::cout << "finished!\n";
}
