#include <iostream>
#include <fstream>
#include <streambuf>

#include "PBU.h"
#include "pu.h"
#include "airtarget.h"
#include "zur.h"
#include "rlc_stub.h"
#include "ModelingDispatcher.h"



int main()
{
    std::ifstream ifs("C:\\Qt_project\\GUI\\exec\\Тест2.json");
    std::string scenario;
    std::copy(std::istream_iterator<char>(ifs), std::istream_iterator<char>(), std::back_insert_iterator<std::string>(scenario));
    ifs.close();

    std::map<std::string, std::pair<int, ModelFactory*> > factories;
    std::pair<int, ModelFactory*> fac1 = {3, new PBUFactory()};
    std::pair<int, ModelFactory*> fac2 = {2, new RLCstubFactory()};
    std::pair<int, ModelFactory*> fac3 = {4, new PUFactory()};
    std::pair<int, ModelFactory*> fac4 = {1, new AirTargetFactory()};
    std::pair<int, ModelFactory*> fac5 = {1, new zurFactory()};

    factories["PBU"] = fac1;
    factories["RLS"] = fac2;
    factories["PU"] = fac3;
    factories["AirTarget"] = fac4;
    factories["ZUR"] = fac5;

    ModelingDispatcher md(0.01, factories);
    md.run(scenario);

    for(auto& it : factories)
        delete it.second.second;

    return 0;
}
