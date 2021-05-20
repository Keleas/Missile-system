#include "pu.h"


PU::PU(id_type id, MsgChannelCarrier &carrier, std::ostream& log)
    : Model{id, carrier, log}
{
    declareteQueue(msg_target_params);
}

bool PU::init(const rapidjson::Value& initial_data)
{
    pu_coords = {initial_data["X"].GetDouble(),
                 initial_data["Y"].GetDouble(),
                 initial_data["Z"].GetDouble()};

    rocket_count = initial_data["Rocket_count"].GetDouble();
    range = initial_data["Range"].GetDouble();
    launch_time = initial_data["Colldown"].GetDouble();

    for (auto& v : initial_data["ZUR_ids"].GetArray())
    {
        zur_ids.push_back(v["ZUR_id"].GetInt());
    }
    return 0;


}

void PU::firstStep()
{
    ready = true;
    launch_cooldown=0;
    prev_time=0;
    PUtoPBUstartMsg msg{id, pu_coords, rocket_count, ready};
    send<PUtoPBUstartMsg>(0,msg);
    write_to_csv(true);
}

void PU::step(double time)
{
    cooldown(time - prev_time);
    is_ready();
    launch_ZUR(time);
    step_msg(time);
    write_to_csv(false);
    prev_time = time ;
}



void PU::endStep()
{
    write_to_csv(false);
}


void PU::is_ready()
{
    ready = (launch_cooldown<=0 &&  rocket_count > 0);
}

void PU::cooldown(double dt)
{
    if (launch_cooldown > 0)
        launch_cooldown -=dt;
    if (launch_cooldown < 0)
        launch_cooldown = 0;
}

void PU::launch_ZUR(double time)
{
    if (launch_cooldown<=0 &&  !msg_target_params.empty())
    {
        id_type zur_id=zur_ids.at(rocket_count);
        PUtoPBUzurIDMsg msg_pbu_launch{zur_id};
        PUtoZURMsg msg_zur_launch{msg_target_params.front().message.target_coord,
                                  msg_target_params.front().message.target_speed,
                                  {pu_coords.at(1),pu_coords.at(2),pu_coords.at(3)}};

        send<PUtoPBUzurIDMsg>(time, msg_pbu_launch);
        send<PUtoZURMsg>(zur_id, time, msg_zur_launch);
        rocket_count -= 1;

        ready = 0;
        launch_cooldown=launch_time;
    }
}

void PU::step_msg(double time)
{
    PUtoBPUMsg msg{rocket_count, ready};
    send<PUtoBPUMsg>(time, msg);
}
