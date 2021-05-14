#include <iostream>

#include "PBU.h"
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
                                 "                  \"x\" : 0,"
                                 "                  \"y\" : 0,"
                                 "                  \"z\" : 0"
                                 "               }"
                             "           }"
                             "      ]"
                             "}";

int main()
{
    return 0;
}
