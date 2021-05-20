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
                             "                  { \"X\": 1.2,"
                             "                    \"Y\": 1.3,"
                             "                    \"Z\": 1.5"
                             "                  }"
                             "          }"
                             "      ]"
                             "}";

void printMSG_PU(id_type id, double time, PBUtoPUMsg msg)
{
    std::cout << "Message from " << id << " at time " << time <<std::endl;
    std::cout << "coord: " << msg.target_coord[0] << " " << msg.target_coord[1] << " " << msg.target_coord[2] << std::endl;
    std::cout << "speed: " << msg.target_speed[0] << " " << msg.target_speed[1] << " " << msg.target_speed[2] << std::endl;

}

void printMSG_RLS(id_type id, double time, PBUtoRLCMsg msg)
{
    std::cout << "Message from " << id << " at time " << time << std::endl;
    std::cout << "zur_id: " << msg.zur_id << std::endl;
}

int main(int argc, char *argv[])
{
    std::map<std::string, std::pair<int, ModelFactory*> > factories;
    std::pair<int, ModelFactory*> fac1 = {1, new PBUFactory()};
    factories["PBU"] = fac1;

    ModelingDispatcher md(0.01, factories);
    md.getChannel<PBUtoPUMsg>().subscribe(printMSG_PU);
    md.getChannel<PBUtoRLCMsg>().subscribe(printMSG_RLS);
    std::cout << "Starting...\n";
    md.run(scenario);
    std::cout << "finished!\n";
}
