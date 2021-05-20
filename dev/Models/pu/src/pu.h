#include <string>
#include <fstream>
#include <deque>
#include <set>
#include <sstream>

#include "abstractmodel.h"
#include "modelfactory.h"
#include "msg_types.h"

struct Coordinates      //coordinates
{
    float X;
    float Y;
    float Z;
};

struct Launcher_Status
{
    bool ready;
    int rocket_count;
    float cooldown;
};

class PU : public Model
{
public:
    PU(id_type id, MsgChannelCarrier& carrier, std::ostream& log);

    bool init(const rapidjson::Value &initial_data) override final;
    void firstStep() override final;
    void step(double time) override final;
    void endStep() override final;
    void write_to_csv();

    bool is_ready();                  //return
    void Launch_the_Rocket(float X, float Y, float Z);
    Launcher_Status Louncher_Unit_Status();
    float Cooldown();



    /*class Id_Gen            //missile id generator 
    {
        int i = 0;
    public:
        int generate()
        {
            int id = i;
            i += 1;
            return id;
        }
    };*/

private:

    int id;
    Coordinates unit_coordinates;
    int rocket_count = 4;
    float range = 100; //100 km   int?
    bool ready = 1;
    // no logs
    float cooldown = 5;  //5 seconds
    float no_launch_time = 5;


    std::deque<Coordinates> launch_queue;

    MessageQueue<PBUtoPUMsg> recieve_fire_msg;
};

inline void PU::write_to_csv()
{
    std::string sep = ", ";

    log << id << sep << unit_coordinates.X << sep << unit_coordinates.Y << sep << unit_coordinates.Z << sep << rocket_count << sep << range << sep << ready << "\n";
}

DEFAULT_MODEL_FACTORY(PU)