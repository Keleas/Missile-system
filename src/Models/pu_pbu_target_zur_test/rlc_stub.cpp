#include "rlc_stub.h"

RLCstub::RLCstub(id_type id, MsgChannelCarrier &carrier, std::ostream &log)
    : Model{id, carrier, log}
{
    declareteQueue(target_msgs);
}

void RLCstub::step(double time)
{
    RLCMsg msg;
    while(!target_msgs.empty())
    {
        msg.time = target_msgs.front().time;
        msg.target_id = target_msgs.front().source_id;
        msg.coordinates = {target_msgs.front().message.coord[0], target_msgs.front().message.coord[1], target_msgs.front().message.coord[2]};
        msg.speed = {target_msgs.front().message.vels[0], target_msgs.front().message.vels[1], target_msgs.front().message.vels[2]};

        if (target_msgs.front().message.status != TargetStatus::is_fly)
        {
            std::cout << int(target_msgs.front().message.status) << std::endl;
        }

        if (target_msgs.front().message.status == TargetStatus::is_fly)
            send<RLCMsg>(time, msg);

        target_msgs.pop_front();
    }
}


