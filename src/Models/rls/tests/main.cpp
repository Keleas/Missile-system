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
                             "                  { \"lambda\": 0.03,"
                             "                   \"Dmax\": 75000,"
                             "                   \"Dmin\": 7419.9,"
                             "                   \"Tscan\": 0.00050035,"
                             "                   \"Timp\": 4.5e-05,"
                             "                   \"V_res\": 20,"
                             "                   \"asim_res\": 0.0237,"
                             "                   \"elev_res\": 0.0194,"
                             "                   \"asim_res_trace_cf\": 0.1,"
                             "                   \"elev_res_trace_cf\": 0.1,"
                             "                   \"elev1\": 0,"
                             "                   \"elev2\": 1.0472,"
                             "                   \"Nasim\": 267,"
                             "                   \"Nelev\": 55,"
                             "                   \"Bandwidth\": 444440,"
                             "                   \"Noise\": 1.9574e-15,"
                             "                   \"Gain\": 21961,"
                             "                   \"P_peak\": 9488400,"
                             "                   \"Tr\": 6,"
                             "                   \"Ntraj\": 64,"
                             "                   \"Nmissiles\": 64,"
                             "                   \"n\": [0, 0, 1],"
                             "                   \"Loc\": [-1596, 4361, 0]"
                             "                   }"
                             "          }"
                             "      ]"
                             "}";



int main(int argc, char *argv[])
{
    std::map<std::string, std::pair<int, ModelFactory*> > factories;
    std::pair<int, ModelFactory*> fac1 = {1, new RLSFactory()};
    factories["RLS"] = fac1;

    ModelingDispatcher md(0.01, factories);
    std::cout << "Starting...\n";
    md.run(scenario);
    std::cout << "finished!\n";
}
