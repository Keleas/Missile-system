#include "rls.h"


RLS::RLS(id_type id, MsgChannelCarrier &carrier, std::ostream& log)
    : Model{id, carrier, log}
{
    declareteQueue(recieve_pbu_msg);
}

bool RLS::init(const rapidjson::Value& initial_data)
{
    param.COORDS = initial_data["coords"].GetDouble();
    param.OBSERVATION_PARAMS =  initial_data["observation_params"].GetDouble();
    param.DISPERSION =  initial_data["dispersion"].GetDouble();
}

void RLS::firstStep()
{
    write_to_csv();
}

void RLS::step(double time)
{
    if (!recieve_pbu_msg.empty())
    {
        //find rocket
    }
    calculate(time);

    Trajectory msg;
    msg.target_coords = { 1.0, 2.0, 3.0 };
    msg.target_v = { 4.0, 5.0, 6.0 };
    msg.sigma = { 7.0, 8.0, 9.0 };
    msg.sigma_half_axis = { 10.0, 11.0, 12.0 };
    msg.target_id = 1;

    send<Trajectory>(time, msg);

    TargetCoords msg;
    msg.target_coords = { 1.0, 2.0, 3.0 };
    msg.target_v = { 4.0, 5.0, 6.0 };
    msg.zur_coords = { -7.0, -8.0, -9.0 };
    msg.zur_v = { -10.0, -11.0, -12.0 };

    send<TargetCoords>(time, msg);

    write_to_csv();
}

void RLS::calculate(double time)
{
    // update all
}
