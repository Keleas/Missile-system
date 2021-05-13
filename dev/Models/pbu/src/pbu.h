#include "channel_carrier.h"
#include "abstractmodel.h"
#include "msg_types.h"
#include "modelfactory.h"
#include <map>

struct PBU_Params
{
    double COORDS;
};

class PBU : public Model
{
public:
    PBU(id_type id, MsgChannelCarrier& carrier, std::ostream& log);
    ~PBU() override;

    void calculate(double dt);

    bool init(const rapidjson::Value& initial_data) override final;

    void firstStep() override final;

    void step(double time) final;

    void endStep() override final;

    void write_to_csv();

    void GetRLIfromRadar();  // Третичная обработка

private:

    int id;

    PBU_Params param;

    MessageQueue<Trajectory> traj_msg_from_rlc;

    /*class Target
    {
    public:
        Target();
        Target(int id, const Trajectory& msg)
            : coords({ {msg.coordinates[0],msg.coordinates[1],msg.coordinates[2]} }),
            speed({ {msg.speed[0],msg.speed[1],msg.speed[2]} }),
            ID(ID),
            time(msg.time)
        {}
        //        Target& operator=(const RLCMsg& msg);

        void CalculateParametrs();

        std::vector<std::vector<double>> history_coords;
        std::vector<std::vector<double>> history_speed;

        std::vector<double> coords;
        std::vector<double> speed;

        id_type ID;
        double time = 0;
    };

    bool CheckTrack(const RLCMsg& t1, const Target& t2);
    void AddNewTarget();


    std::map<std::pair<id_type, id_type>, int> id_table;            // key - <first - rls_id, second - target_id>, value - My_id
    std::map<int, std::map<id_type, id_type>> history_id;           // key - My_id, value - <first - rls_id, second - target_id>
    std::map<std::pair<id_type, id_type>, double> targets_time;     // key - <first - rls_id, second - target_id>, value - time
    std::map<id_type, Target> targets;                              // key - My_id, value - Target
    int target_counter = 1;

    std::map<id_type, std::map<id_type, bool>> pu_base;
    std::map<id_type, std::vector<double>> pu_coords;*/
};

inline void PBU::write_to_csv()
{
    std::string sep = ", ";

    log << "rls_id" << sep << "Target_id" << sep << "Target_coords" << "\n";
}

DEFAULT_MODEL_FACTORY(PBU)