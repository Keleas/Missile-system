#include "rlc_stub.h"

RLCstub::RLCstub(id_type id, MsgChannelCarrier &carrier, std::ostream &log)
    : Model{id, carrier, log} {}

void RLCstub::step(double time)
{
    RLCMsg msg;
    while(!target_msgs.empty())
    {
        msg.time = target_msgs.front().time;
        msg.target_id = target_msgs.front().source_id;
        msg.coordinates = {target_msgs.front().message.coord[0], target_msgs.front().message.coord[1], target_msgs.front().message.coord[2]};
        msg.speed = {target_msgs.front().message.vels[0], target_msgs.front().message.vels[1], target_msgs.front().message.vels[2]};
        send<RLCMsg>(time, msg);
        target_msgs.pop_front();
    }
}


