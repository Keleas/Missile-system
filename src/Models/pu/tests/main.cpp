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
                             "                  \"Cooldown\" : 0.05,"
                             "                   \"ZUR_ids\": "
                             "                      [1001, 1002, 1003, 1004],"
                             "                   \"PBU_ID\": 10"
                             "                    }"
                             "          }"
                             "      ]"
                             "}";

//class PBU : public Model
//{
//public:
//    PBU(id_type id, MsgChannelCarrier& carrier, std::ostream& log)
//        : Model(id, carrier, log) {}
//    ~PBU() override {}

//    bool init(const rapidjson::Value& initial_data) override final{}

//    void firstStep() override final
//    {

//    }
//    void step(double time) override final
//    {
//        PBUtoPUMsg pbumsg;
//        pbumsg.target_coord = {100,101,102};
//        pbumsg.target_speed = {10,11,12};

//        PBUtoPUMsg msg;
//        msg.target_coord = {100,101,102};
//        msg.target_speed = {1,11,12};
//        if (time == 0.05)
//        {
//            send<PBUtoPUMsg>(1,time,pbumsg);
//            send<PBUtoPUMsg>(1,time,msg);
//        }
//    }
//    void endStep() override final {}
//};

//DEFAULT_MODEL_FACTORY(PBU)
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
