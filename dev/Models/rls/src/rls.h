#ifndef AIRTARGET_H
#define AIRTARGET_H

#include <string>
#include <fstream>

#include "abstractmodel.h"
#include "modelfactory.h"
#include "msg_types.h"

#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "omp.h"
#include "MFR_V2_Cycle_types.h"
#include "MFR_V2_Cycle.h"
#include "MFR_V2_Cycle_emxAPI.h"
#include "MFR_V2_Cycle_terminate.h"
#include "MFR_V2_GenerateMFRType.h"
#include "MFR_V2_GenerateTrajectoryType.h"
#include "rt_nonfinite.h"


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
    MessageQueue<Rocket_Start> recieve_pbu_msg;
    MessageQueue<TargetMsg> recieve_target_msg;

    struct2_T MSG;
    struct0_T TG;
    struct1_T MFR;
};

inline void RLS::write_to_csv()
{
    std::string sep = ", ";

    log << "rls_id" << sep << "Target_id" << sep << "Target_coords" << "\n";
}

DEFAULT_MODEL_FACTORY(RLS)

#endif // AIRTARGET_H
