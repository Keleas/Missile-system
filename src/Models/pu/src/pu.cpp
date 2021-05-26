#include "pu.h"

PU::PU(id_type id, MsgChannelCarrier &carrier, std::ostream& log)
    : Model{id, carrier, log}
{
    declareteQueue(msg_target_params);
}

bool PU::init(const rapidjson::Value& initial_data)
{
    pu_coords = {initial_data["x"].GetDouble(),
                 initial_data["y"].GetDouble(),
                 initial_data["z"].GetDouble()};

    rocket_count = initial_data["rockets_amount"].GetUint();
    range = initial_data["radius"].GetDouble();
    launch_time = initial_data["cooldown"].GetDouble();
//    pbu_id = initial_data["PBU_ID"].GetUint();
    pbu_id = 0;

    for (auto& v : initial_data["zur_id"].GetArray())
    {
        zur_ids.push_back(v["id"].GetUint());
    }
    return true;
}

void PU::firstStep()
{
    ready = true;
    launch_cooldown = 0;
    prev_time = 0;
    PUtoPBUstartMsg msg{id, pu_coords, range, rocket_count, ready};
    send<PUtoPBUstartMsg>(pbu_id,0,msg);
//    write_to_csv(true);
    setLogHeader("pu_id", "X", "Y", "Z", "Rocket count", "Range", "Ready");
}

void PU::step(double time)
{
    cooldown(time - prev_time);
    is_ready();
    launch_ZUR(time);
    step_msg(time);
//    write_to_csv(false);
    prev_time = time ;
    writeLog(time, id, pu_coords.at(0), pu_coords.at(1), pu_coords.at(2), rocket_count, range, ready);    
}

void PU::endStep()
{
//    write_to_csv(false);
}


void PU::is_ready()
{
    ready = (launch_cooldown<=0 &&  rocket_count > 0);
}

void PU::cooldown(double dt)
{
    if (launch_cooldown > 0)
        launch_cooldown -= dt;
    if (launch_cooldown < 0)
        launch_cooldown = 0;
}

void PU::launch_ZUR(double time)
{
    if (launch_cooldown<=0 &&  !msg_target_params.empty() && rocket_count > 0)
    {
        id_type zur_id=zur_ids.front();

        zur_ids.pop_front();
        PUtoPBUzurIDMsg msg_pbu_launch;
        msg_pbu_launch.zur_id = zur_id;
        msg_pbu_launch.target_id = msg_target_params.front().message.target_id;
        PUtoZURMsg msg_zur_launch;
        msg_zur_launch.target_coord = msg_target_params.front().message.target_coord;
        msg_zur_launch.target_speed = msg_target_params.front().message.target_speed;
        msg_zur_launch.pu_coord = {pu_coords.at(0),pu_coords.at(1),pu_coords.at(2)};
        msg_target_params.pop_front();
        send<PUtoPBUzurIDMsg>(pbu_id, time, msg_pbu_launch);
        send<PUtoZURMsg>(zur_id, time, msg_zur_launch);
        rocket_count -= 1;

        ready = 0;
        launch_cooldown=launch_time;
    }
}

void PU::step_msg(double time)
{
    PUtoBPUMsg msg{rocket_count, ready};
    send<PUtoBPUMsg>(pbu_id, time, msg);
}
