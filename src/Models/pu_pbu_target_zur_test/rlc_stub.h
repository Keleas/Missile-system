#ifndef RLC_STUB_H
#define RLC_STUB_H

#include "abstractmodel.h"
#include "modelfactory.h"
#include "msg_types.h"

class RLCstub : public Model
{
public:
    RLCstub(id_type id, MsgChannelCarrier& carrier, std::ostream& log);
    ~RLCstub() override {}

    bool init(const rapidjson::Value& initial_data) override final {};

    void firstStep() override final {};
    void step(double time) override final;
    void endStep() override final {};

private:
    MessageQueue<TargetMsg> target_msgs;
};

DEFAULT_MODEL_FACTORY(RLCstub)

#endif
