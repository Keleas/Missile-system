#ifndef MISSILESYSTEM_PBU_H
#define MISSILESYSTEM_PBU_H

#include "channel_carrier.h"
#include "abstractmodel.h"
#include "msg_types.h"

class PBU : public Model
{
public:
    PBU(id_type id, MsgChannelCarrier& carrier);
    ~PBU();

//    bool init(std::string const& initial_data) override final;

    void firstStep() override final;

    void step(double time) final;
private:
    //MessageQueue<RLCMsg> msg_from_rlc;
};


#endif //MISSILESYSTEM_PBU_H
