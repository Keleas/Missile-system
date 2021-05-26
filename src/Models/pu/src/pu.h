#ifndef PU_H
#define PU_H

#include <string>
#include <fstream>

#include "abstractmodel.h"
#include "modelfactory.h"
#include "msg_types.h"
#include <map>

class PU : public Model
{
public:
    PU(id_type id, MsgChannelCarrier& carrier, std::ostream& log);


    bool init(const rapidjson::Value &initial_data) override final;
    void firstStep() override final;
    void step(double time) override final;
    void endStep() override final;
//    void write_to_csv(bool fisrt_time);

private:
    id_type pbu_id;
    vec3 pu_coords;
    int rocket_count;
    double range;
    bool ready;

    std::list<id_type> zur_ids;

    double launch_cooldown;
    double launch_time;
    double prev_time;

    MessageQueue<PBUtoPUMsg> msg_target_params;


    void is_ready();
    void cooldown(double dt);
    void launch_ZUR(double time);
    void step_msg(double time);
};


DEFAULT_MODEL_FACTORY(PU)

#endif // AIRTARGET_H

