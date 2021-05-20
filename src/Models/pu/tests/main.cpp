#include <iostream>

#include "pu.h"
#include "ModelingDispatcher.h"

const std::string scenario = "{"
                             "  \"scenario_name\": \"PUstation\","
                             "  \"end_time\": 1800.0,"
                             "  \"objects\": "
                             "      ["
                             "          {"
                             "              \"id\": 1,"
                             "              \"model_name\": \"PBU\","
                             "              \"initial_data\": "
                             "                   {"
                                 "                  \"X\" : 3,"
                                 "                  \"Y\" : 4,"
                                 "                  \"Z\" : 0,"
                                 "                  \"Range\" : 100,"
                                 "                  \"Rocket Count\" : 4,"
                                 "                  \"Cooldown\" : 100,"
                                 "                   \"ZUR_ids\": "
                                 "                      ["
                             "                          {"
                                 "                      \"ZUR_id\" : 1001"
                                 "                      },"
                             "                          {"
                                 "                      \"ZUR_id\" : 1002"
                                 "                      },"
                             "                          {"
                                 "                      \"ZUR_id\" : 1003"
                                 "                      },"
                             "                          {"
                                 "                      \"ZUR_id\" : 1004"
                                 "                      }"
                                 "                      ]"
                             "                    }"
                             "          }"
                             "      ]"
                             "}";

int main()
{
    std::map<std::string, std::pair<int, ModelFactory*> > factories;
    std::pair<int, ModelFactory*> fac1 = {1, new PUFactory()};
    factories["PU"] = fac1;
    ModelingDispatcher md(0.01, factories);
    std::cout << "[pu]Starting...\n";
    md.run(scenario);
    std::cout << "[pu]finished!\n";

    std::cout<<"test";
    return 0;
}
