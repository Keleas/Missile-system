#include "rls.h"


RLS::RLS(id_type id, MsgChannelCarrier &carrier, std::ostream& log)
    : Model{id, carrier, log}
{
    declareteQueue(recieve_pbu_msg);
    declareteQueue(recieve_target_msg);
}

bool RLS::init(const rapidjson::Value& initial_data)
{
    param.COORDS = initial_data["coords"].GetDouble();
    param.OBSERVATION_PARAMS = initial_data["observation_params"].GetDouble();
    param.DISPERSION = initial_data["dispersion"].GetDouble();
    return true;
}

void RLS::firstStep()
{
    write_to_csv();
}

void RLS::step(double time)
{
    if (!recieve_target_msg.empty())
    {
        Trajectory traj_msg;
        traj_msg.target_coords = recieve_target_msg.front().message.coord;
        traj_msg.target_v = recieve_target_msg.front().message.vels;
        traj_msg.sigma = { 7.0, 8.0, 9.0 };
        traj_msg.sigma_half_axis = { 10.0, 11.0, 12.0 };
        traj_msg.target_id = recieve_target_msg.front().source_id;
        
        recieve_target_msg.pop_front();

        //find target
        calculate(time);        

        send<Trajectory>(time, traj_msg);
    }

    TargetCoords target_msg;
    target_msg.target_coords = { 1.0, 2.0, 3.0 };
    target_msg.target_v = { 4.0, 5.0, 6.0 };
    target_msg.zur_coords = { -7.0, -8.0, -9.0 };
    target_msg.zur_v = { -10.0, -11.0, -12.0 };

    send<TargetCoords>(time, target_msg);

    write_to_csv();
}

void RLS::calculate(double time)
{
    // update all
}

void RLS::endStep()
{
    write_to_csv();
}