#ifndef AIRTARGET_H
#define AIRTARGET_H

#include <string>
#include <fstream>

#include "abstractmodel.h"
#include "modelfactory.h"
#include "msg_types.h"
#include <map>

struct PU_Params
{
    double COORDS;
    int ROCKETS_AMOUNT;
    bool IS_READY;
};

class PU : public Model
{
public:
    PU(id_type id, MsgChannelCarrier& carrier, std::ostream& log);


    bool init(const rapidjson::Value &initial_data) override final;
    void firstStep() override final;
    void step(double time) override final;
    void endStep() override final;
    void write_to_csv(bool fisrt_time);

private:
    id_type id;
    vec3 pu_coords;
    int rocket_count;
    double range;
    bool ready;

    std::vector<id_type> zur_ids;

    float launch_cooldown;
    float launch_time;
    double prev_time;

    MessageQueue<PBUtoPUMsg> msg_target_params;


    void is_ready();
    void cooldown(double dt);
    void launch_ZUR(double time);
    void step_msg(double time);
};

inline void PU::write_to_csv(bool fisrt_time)
{
    std::string sep = ", ";

    if (fisrt_time)
    {
        log << "pu_id" << sep
            << "X" << sep
            << "Y" << sep
            << "Z" << sep
            << "Rocket count" << sep
            << "Range" << sep
            << "Ready" << "\n";
    }
    else
    {
        log << id << sep
            << pu_coords.at(1) << sep
            << pu_coords.at(2) << sep
            << pu_coords.at(3) << sep
            << rocket_count << sep
            << range << sep
            << ready << "\n";
    }
}

DEFAULT_MODEL_FACTORY(PU)

#endif // AIRTARGET_H
