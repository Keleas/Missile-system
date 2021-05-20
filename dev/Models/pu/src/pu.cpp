#include "pu.h"


PU::PU(id_type id, MsgChannelCarrier &carrier, std::ostream& log)
    : Model{id, carrier, log}
{
    declareteQueue(recieve_fire_msg);
}

bool PU::init(const rapidjson::Value& initial_data)
{    
    unit_coordinates.X = initial_data["X"].GetDouble();
    unit_coordinates.Y =  initial_data["Y"].GetDouble();
    unit_coordinates.Z = initial_data["Z"].GetDouble();
    return 0;
}

bool PU::is_ready()                   //return
{
    return (no_launch_time >= cooldown && rocket_count >= 1);
}

void PU::Launch_the_Rocket(float X, float Y, float Z)
//Launch_the_Rocket(X,Y,Z)  
{
    Coordinates target_coordinats;
    target_coordinats.X = X;
    target_coordinats.Z = Z;
    target_coordinats.Y = Y;
    launch_queue.push_back(target_coordinats);
}

Launcher_Status PU::Louncher_Unit_Status()
{
    Launcher_Status status;
    status.ready = ready;
    status.rocket_count = rocket_count;
    status.cooldown = Cooldown();
    return status;
}

float PU::Cooldown()
{
    float cd = cooldown - no_launch_time;
    if (cd > 0)
        return cd;
    else
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
        //Rocket_Start msg;
        //msg.is_rocket_started = true;
        //msg.rls_rocket_coords = { param.COORDS, param.COORDS, param.COORDS };

        ready = is_ready();
        if (ready && !launch_queue.empty())
        {
            Coordinates target_coordinats = launch_queue.front();
            launch_queue.pop_front();
            int id_rocket = 0;
            ///        ZUR rocket = ZUR_constractor(id_rocket,unit_coordinates,target_coordinats,)
            ///        rockets.push_back(rocket);
            no_launch_time = 0;
            rocket_count -= 1;
            ready = 0;
        }

        //send<Rocket_Start>(time, msg);

    }



    /*is_ready msg;
    msg.is_ready = param.IS_READY;

    send<is_ready>(time, msg);*/

    write_to_csv();
}

void PU::endStep()
{
    write_to_csv();
}
