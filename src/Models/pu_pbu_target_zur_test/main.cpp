#include <iostream>
#include <fstream>
#include <streambuf>

#include "PBU.h"
#include "pu.h"
#include "airtarget.h"
#include "zur.h"
#include "rlc_stub.h"
#include "ModelingDispatcher.h"


void print_PBUtoZURMsg(id_type from, double time, PBUtoZURMsg msg)
{
    std::cout << "PBUtoZURMsg from " << from << " at " << time << " (coords: ("
              << msg.target_coord[0] << ", " << msg.target_coord[1] << ", " << msg.target_coord[2] << "), speed: " << msg.target_speed << ")\n";
}

void print_PUtoPBUzurIDMsg(id_type from, double time, PUtoPBUzurIDMsg msg)
{
     std::cout << "PUtoPBUzurIDMsg from " << from << " at " << time << "(" << msg.zur_id << ", " << msg.target_id << ")\n";
}


int main()
{
    std::ifstream ifs("C:\\Qt_project\\GUI2\\exec\\test3.json");
    std::string scenario;
    std::string tmp;
    while(std::getline(ifs, tmp))
        scenario += tmp;
    ifs.close();
//    std::cout << scenario << std::endl;

    std::map<std::string, std::pair<int, ModelFactory*> > factories;
    std::pair<int, ModelFactory*> fac1 = {4, new PBUFactory()};
    std::pair<int, ModelFactory*> fac2 = {2, new RLCstubFactory()};
    std::pair<int, ModelFactory*> fac3 = {3, new PUFactory()};
    std::pair<int, ModelFactory*> fac4 = {1, new AirTargetFactory()};
    std::pair<int, ModelFactory*> fac5 = {5, new zurFactory()};

    factories["PBU"] = fac1;
    factories["RLS"] = fac2;
    factories["PU"] = fac3;
    factories["AirTarget"] = fac4;
    factories["ZUR"] = fac5;

    ModelingDispatcher md(0.01, factories);
    md.msgSubscribe<PBUtoZURMsg>(print_PBUtoZURMsg);
    md.run(scenario);

    for(auto& it : factories)
        delete it.second.second;

    return 0;
}
