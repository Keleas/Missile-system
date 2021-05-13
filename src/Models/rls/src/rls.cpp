#include "rls.h"


RLS::RLS(id_type id, MsgChannelCarrier &carrier, std::ostream& log)
    : Model{id, carrier, log}
{
    declareteQueue(recieve_pbu_msg);
}

bool RLS::init(const rapidjson::Value& initial_data)
{
    std::cout << "params" << std::endl;
    std::cout << initial_data["coords"].GetDouble() << std::endl;
    param.COORDS = initial_data["coords"].GetDouble();
    
    std::cout << param.COORDS << std::endl; 
    param.OBSERVATION_PARAMS = initial_data["observation_params"].GetDouble();
    param.DISPERSION = initial_data["dispersion"].GetDouble();
    std::cout << param.OBSERVATION_PARAMS << std::endl;
    std::cout << param.DISPERSION << std::endl;
    return true;
}

void RLS::firstStep()
{
    std::cout << "Message from " << " at time " << std::endl;
    write_to_csv();
}

void RLS::step(double time)
{
    if (!recieve_pbu_msg.empty())
    {
        //find rocket
    }
    calculate(time);

    Trajectory traj_msg;
    traj_msg.target_coords = { 1.0, 2.0, 3.0 };
    traj_msg.target_v = { 4.0, 5.0, 6.0 };
    traj_msg.sigma = { 7.0, 8.0, 9.0 };
    traj_msg.sigma_half_axis = { 10.0, 11.0, 12.0 };
    traj_msg.target_id = 1;

    send<Trajectory>(time, traj_msg);

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