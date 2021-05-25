#ifndef ZUR_H
#define ZUR_H

#include "airtarget.h"

#define square_destroy_range 2500

class zur : public Model
{
public:
    zur(id_type id, MsgChannelCarrier& carrier, std::ostream& log);

    bool init(const rapidjson::Value &initial_data) override final;
    void firstStep() override final;
    void step(double time) override final;
    void endStep() override final {write_to_file("rocket_crd.txt");};

    void write_to_file(std::string file_name);
    void write_to_csv(bool fisrt_time=false);

    void set_status(ZurStatus trg);
    ZurStatus get_status();
    Vector3D get_coords();

    MessageQueue<PuToZurMsg> recieve_msg_pu;
    MessageQueue<RLSToZurMsg> recieve_msg_rls;

private:
    void calculate(double dt, std::vector<TrajectoryPoint> control_points);
    void pursuit(double dt);
    void toss_rocket(double dt);

    std::string rocketName;
    std::string rocketModelType;

    AbstractTargetParams param;
    Vector3D coords;
    ZurStatus status = ZurStatus::is_not_fly;

    TrajectoryPoint start_point;
    TrajData data;

    Vector3D NuCurNext;

    GeodezicCoodinates GD_Msc = GeodezicCoodinates(55, 37, 0); //костыыыыль

    bool is_tossed = false;

};

#endif // ZUR_H
