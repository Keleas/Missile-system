#include <iostream>

#include "pbu.h"
#include "ModelingDispatcher.h"

const std::string scenario = "{"
                             "  \"scenario_name\": \"pbu_init\","
                             "  \"end_time\": 100.0,"
                             "  \"objects\": "
                             "      ["
                             "          {"
                             "              \"id\": 1,"
                             "              \"model_name\": \"PBU\","
                             "              \"initial_data\":"
                             "                  { \"coords\": 1.2"
                             "                  }"
                             "          }"
                             "      ]"
                             "}";

void printMSG(id_type id, double time, Fire msg)
{
    std::cout << "Message from " << id << " at time " << time <<std::endl;
    std::cout << "coord: " << msg.pu_target_coords[0] << " " << msg.pu_target_coords[1] << " " << msg.pu_target_coords[2] << std::endl;
    std::cout << "target_id: " << msg.target_id << std::endl;
}

int main(int argc, char *argv[])
{
    std::map<std::string, std::pair<int, ModelFactory*> > factories;
    std::pair<int, ModelFactory*> fac1 = {1, new PBUFactory()};
    factories["PBU"] = fac1;

    ModelingDispatcher md(0.01, factories);
    md.getChannel<Fire>().subscribe(printMSG);
    std::cout << "Starting...\n";
    md.run(scenario);
    std::cout << "finished!\n";
}
