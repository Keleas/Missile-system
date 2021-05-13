#include <iostream>

#include "PBU.h"
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
                             "               ["
                             "                 {"
                             "                    \"pu_id\": \"1\","
                             "                    \"zur_id\": "
                             "                       ["
                             "                            3, 45, 12, 14 "
                             "                       ],"
                             "                    \"coordinates\": "
                             "                          ["
                             "                            37.885104, 57.867425, -15.8059282 "
                             "                          ]"
                             "                  }"
                             "               ]"
                             "           }"
                             "      ]"
                             "}";

int main()
{
    return 0;
}
