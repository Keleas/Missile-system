#include <iostream>

#include "pu.h"
#include "ModelingDispatcher.h"

const std::string scenario = "{"
                             "  \"scenario_name\": \"PUstation\","
                             "  \"end_time\": 3.0,"
                             "  \"objects\": "
                             "      ["
                             "          {"
                             "              \"id\": 1,"
                             "              \"model_name\": \"PU\","
                             "              \"initial_data\": "
                             "                   {"
                                 "                  \"X\" : 3,"
                                 "                  \"Y\" : 4,"
                                 "                  \"Z\" : 0,"
                                 "                  \"Range\" : 100,"
                                 "                  \"Rocket_count\" : 4,"
                                 "                  \"Cooldown\" : 5,"
                                 "                   \"ZUR_ids\": "
                                 "                      [1001, 1002, 1003, 1004],"
                                 "                   \"PBU_ID\": 10"
                             "                    }"
                             "          }"
                             "      ]"
                             "}";

std::ostream & operator<<(std::ostream& os, PUtoBPUMsg m)
{
    os << "(STATUS: " << m.status << ", ZUR_NUM: " << m.zur_num << ")";
    return os;
}

std::ostream & operator<<(std::ostream& os, PUtoPBUstartMsg m)
{
    os << "(STATUS: " << m.status << ", ZUR_NUM: " << m.zur_num << ", COORDS: " << "(" << m.coord[0] <<
    ", " << m.coord[1] << ", " << m.coord[2] << "), LAUNCHER_ID: " << m.launcher_id << ")";
    return os;
}

template <typename MT>
void print_msg(id_type id, double time, MT mes)
{
    std::cout << "Message from " << id << " at time " << time << ": " << mes << std::endl;
}

int main()
{
    std::map<std::string, std::pair<int, ModelFactory*> > factories;
    std::pair<int, ModelFactory*> fac1 = {1, new PUFactory()};
    factories["PU"] = fac1;
    ModelingDispatcher md(0.01, factories);

    md.msgSubscribe<PUtoBPUMsg>(print_msg<PUtoBPUMsg>);
    md.msgSubscribe<PUtoPBUstartMsg>(print_msg<PUtoPBUstartMsg>);

    std::cout << "[pu]Starting...\n";
    md.run(scenario);
    std::cout << "[pu]finished!\n";

    std::cout<<"test";
    return 0;
}
