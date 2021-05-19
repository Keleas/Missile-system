#include <iostream>
#include "channel_carrier.h"
#include "testmodel.h"
#include "ModelingDispatcher.h"

const std::string scenario = "{"
                             "  \"scenario_name\": \"test_scenario\","
                             "  \"end_time\": 10.0,"
                             "  \"objects\": "
                             "      ["
                             "          {"
                             "              \"id\": 1,"
                             "              \"model_name\": \"model1\","
                             "              \"initial_data\": { \"listen\": 2 }"
                             "          },"
                             "          {"
                             "              \"id\": 2,"
                             "              \"model_name\": \"model2\","
                             "              \"initial_data\": null"
                             "          }"
                             "      ]"
                             "}";

void print_msg(id_type from, double time, std::string const& msg)
{
    std::cout << "Message from " << from << " at " << time << ": " << msg << std::endl;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    std::map<std::string, std::pair<int, ModelFactory*> > factories;
    std::pair<int, ModelFactory*> fac1 = {1, new model1Factory()};
    std::pair<int, ModelFactory*> fac2 = {2, new model2Factory()};
    factories["model1"] = fac1;
    factories["model2"] = fac2;

    ModelingDispatcher md(1.0, factories);

    md.msgSubscribe<std::string>(print_msg);

    md.run(scenario);

    for(auto& it : factories)
        delete it.second.second;
    return 0;
}
