#include <iostream>
#include "rls.h"
#include "pbu.h"
#include "pu.h"
#include "zur.h"
#include "airtarget.h"
#include "ModelingDispatcher.h"

int dispetcher_start(int argc, char* argv[])
{
    std::map<std::string, std::pair<int, ModelFactory*> > factories;
    std::pair<int, ModelFactory*> fac1 = { 1, new AirTargetFactory() };
    factories["AirTarget"] = fac1;

    std::pair<int, ModelFactory*> fac2 = { 2, new RLSFactory() };
    factories["RLS"] = fac2;

    std::pair<int, ModelFactory*> fac3 = { 3, new PBUFactory() };
    factories["PBU"] = fac3;

    std::pair<int, ModelFactory*> fac4 = { 4, new PUFactory() };
    factories["PU"] = fac4;

    std::pair<int, ModelFactory*> fac5 = { 5, new zurFactory() };
    factories["zur"] = fac5;

    ModelingDispatcher md(0.01, factories);

    std::cout << "Starting...\n";
    //md.run(scenario);
    std::cout << "finished!\n";

    return 0;
}
