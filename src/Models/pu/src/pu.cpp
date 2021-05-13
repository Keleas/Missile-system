#include "pu.h"


PU::PU(id_type id, MsgChannelCarrier &carrier, std::ostream& log)
    : Model{id, carrier, log}
{
    declareteQueue(recieve_ready_msg);
    declareteQueue(recieve_fire_msg);
}

bool PU::init(const rapidjson::Value& initial_data)
{
    param.COORDS = initial_data["coords"].GetDouble();
    param.ROCKETS_AMOUNT =  initial_data["rockets_amount"].GetInt();
    param.IS_READY = initial_data["is_ready"].GetBool();
    return 0;
}

void PU::firstStep()
{
    write_to_csv();
}

void PU::step(double time)
{
    if (!recieve_fire_msg.empty())
    {
        Rocket_Start msg;
        msg.is_rocket_started = true;
        msg.rls_rocket_coords = { param.COORDS, param.COORDS, param.COORDS };

        send<Rocket_Start>(time, msg);
    }
    if (!recieve_ready_msg.empty())
    {
        is_ready msg;
        msg.is_ready = param.IS_READY;

        send<is_ready>(time, msg);
    }
    calculate(time);

    is_ready msg;
    msg.is_ready = param.IS_READY;

    send<is_ready>(time, msg);

    write_to_csv();
}

void PU::calculate(double time)
{
    // update all
}

void PU::endStep()
{
    write_to_csv();
}
