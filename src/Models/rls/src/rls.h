#ifndef AIRTARGET_H
#define AIRTARGET_H

#include <string>
#include <fstream>

#include "abstractmodel.h"
#include "modelfactory.h"
#include "msg_types.h"


struct RLS_Params
{
    double COORDS;
    double OBSERVATION_PARAMS;
    double DISPERSION;
};

class RLS : public Model
{
public:
    RLS(id_type id, MsgChannelCarrier& carrier, std::ostream& log);

    void calculate(double dt);

    bool init(const rapidjson::Value &initial_data) override final;
    void firstStep() override final;
    void step(double time) override final;
    void endStep() override final;
    void write_to_csv();

private:
    int id;
    RLS_Params param;
    MessageQueue<Rocket_Start> recieve_pbu_msg;
};

inline void RLS::write_to_csv()
{
    std::string sep = ", ";

    log << "rls_id" << sep << "Target_id" << sep << "Target_coords" << "\n";
}

DEFAULT_MODEL_FACTORY(RLS)

#endif // AIRTARGET_H
