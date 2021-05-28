#include <iostream>

#include "PBU.h"
#include "ModelingDispatcher.h"
#include <QFile>
#include <QTextStream>

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
                             "           },"
                             "            {"
                             "              \"id\": 2,"
                             "              \"model_name\": \"RLC\","
                             "              \"initial_data\": "
                             "                   {"
                             "               }"
                             "           }"
                             "      ]"
                             "}";



class RLS : public Model
{
public:
    RLS(id_type id, MsgChannelCarrier& carrier, std::ostream& log)
        : Model(id, carrier, log) {}
    ~RLS() override {}

    bool init(const rapidjson::Value& initial_data) override final{}

    void firstStep() override final
    {
        read_aircraft_csv("1Target3Points_AirTarget_1.csv", target1);
        read_aircraft_csv("1Target3Points_AirTarget_2.csv", target2);
        read_aircraft_csv("1Target3Points_AirTarget_3.csv", target3);
    }
    void step(double time) override final
    {
        if(!target1.empty())
        {
            send<RLCMsg>(target1.front().time, target1.front());            
            target1.pop_front();
        }
        if(!target2.empty())
        {
            send<RLCMsg>(target2.front().time,target2.front());
            target2.pop_front();
        }
        if(!target3.empty())
        {
            send<RLCMsg>(target3.front().time,target3.front());
            target3.pop_front();
        }
    }
    void endStep() override final {}

    void read_aircraft_csv(QString name_csv, std::list<RLCMsg>& msg_q)
    {
        QFile file(name_csv);
        file.open(QFile::ReadOnly | QFile::Text);
        QTextStream in(&file);
        QString line = in.readLine();
        id_type id;
        double time = 0.01;
        while (!in.atEnd())
        {
            line = in.readLine();
            id=line.split(',').at(1).toInt();
            std::vector<double> coords{line.split(',').at(2).toDouble(), line.split(',').at(3).toDouble(), line.split(',').at(4).toDouble()};
            std::vector<double> speed{line.split(',').at(5).toDouble(), line.split(',').at(6).toDouble(), line.split(',').at(7).toDouble()};

            RLCMsg msg{id,coords,speed,time};
            msg.time = time;
            msg_q.push_back(msg);

            time += time;
        }
        file.close();
    }

    std::list<RLCMsg> target1;
    std::list<RLCMsg> target2;
    std::list<RLCMsg> target3;
};
DEFAULT_MODEL_FACTORY(RLS)



int main()
{
    std::map<std::string, std::pair<int, ModelFactory*> > factories;
    std::pair<int, ModelFactory*> fac1 = {1, new PBUFactory()};
    std::pair<int, ModelFactory*> fac2 = {1, new RLSFactory()};
    factories["PBU"] = fac1;
    factories["RLC"] = fac2;

    ModelingDispatcher md(0.01, factories);
    md.run(scenario);

    return 0;
}
