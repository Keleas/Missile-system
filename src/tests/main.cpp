#include "rls.h"
#include "pbu.h"
#include "pu.h"
#include "zur.h"
#include "airtarget.h"
#include "ModelingDispatcher.h"

#include <iostream>
#include <fstream>
#include <streambuf>

int main(int argc, char* argv[])
{
    std::ifstream ifs("C:\\Users\\DanilMakhotkin\\Documents\\Homeworks\\almaz\\final\\Missile-system\\src\\tests\\test3.json");
    std::string scenario;
    std::string tmp;
    while (std::getline(ifs, tmp))
        scenario += tmp;
    ifs.close();

    std::map<std::string, std::pair<int, ModelFactory*> > factories;
    std::pair<int, ModelFactory*> fac1 = { 4, new PBUFactory() };
    std::pair<int, ModelFactory*> fac2 = { 2, new RLSFactory() };
    std::pair<int, ModelFactory*> fac3 = { 3, new PUFactory() };
    std::pair<int, ModelFactory*> fac4 = { 1, new AirTargetFactory() };
    std::pair<int, ModelFactory*> fac5 = { 5, new zurFactory() };

    factories["PBU"] = fac1;
    factories["RLS"] = fac2;
    factories["PU"] = fac3;
    factories["AirTarget"] = fac4;
    factories["ZUR"] = fac5;

    ModelingDispatcher md(0.01, factories);

    std::cout << "Starting...\n";
    md.run(scenario);
    std::cout << "finished!\n";

    for (auto& it : factories)
        delete it.second.second;

    return 0;
}
