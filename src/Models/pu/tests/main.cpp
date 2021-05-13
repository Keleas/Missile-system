#include <iostream>

#include "pu.h"
#include "ModelingDispatcher.h"

const std::string scenario = "{"
                             "  \"scenario_name\": \"pu_init\","
                             "  \"end_time\": 100.0,"
                             "  \"objects\": "
                             "      ["
                             "          {"
                             "              \"id\": 1,"
                             "              \"model_name\": \"PU\","
                             "              \"initial_data\":"
                             "                  { \"coords\": 1.2,"
                             "                   \"rockets_amount\": 3,"
                             "                   \"is_ready\": true"
"                                               }"
                             "          }"
                             "      ]"
                             "}";

void printMSG(id_type id, double time, is_ready msg)
{
    std::cout << "Message from " << id << " at time " << time <<std::endl;
    std::cout << "is_ready: " << msg.is_ready << std::endl;
}

int main(int argc, char *argv[])
{
    std::map<std::string, std::pair<int, ModelFactory*> > factories;
    std::pair<int, ModelFactory*> fac1 = {1, new PUFactory()};
    factories["PU"] = fac1;

    ModelingDispatcher md(0.01, factories);
    md.getChannel<is_ready>().subscribe(printMSG);
    std::cout << "Starting...\n";
    md.run(scenario);
    std::cout << "finished!\n";
}
