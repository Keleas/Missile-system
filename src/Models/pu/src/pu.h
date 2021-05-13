#ifndef AIRTARGET_H
#define AIRTARGET_H

#include <string>
#include <fstream>

#include "abstractmodel.h"
#include "modelfactory.h"
#include "msg_types.h"


struct PU_Params
{
    double COORDS;
    int ROCKETS_AMOUNT;
    bool IS_READY;
};

class PU : public Model
{
public:
    PU(id_type id, MsgChannelCarrier& carrier, std::ostream& log);

    void calculate(double dt);

    bool init(const rapidjson::Value &initial_data) override final;
    void firstStep() override final;
    void step(double time) override final;
    void endStep() override final;
    void write_to_csv();

private:
    int id;
    PU_Params param;
    MessageQueue<is_ready> recieve_ready_msg;
    MessageQueue<Fire> recieve_fire_msg;
};

inline void PU::write_to_csv()
{
    std::string sep = ", ";

    log << "pu_id" << sep << "Target_id" << sep << "Target_coords" << "\n";
}

DEFAULT_MODEL_FACTORY(PU)

#endif // AIRTARGET_H
