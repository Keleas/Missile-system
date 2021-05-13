#ifndef MISSILESYSTEM_PBU_H
#define MISSILESYSTEM_PBU_H

#include "channel_carrier.h"
#include "abstractmodel.h"
#include "msg_types.h"
#include <map>





class PBU : public Model
{
public:
    PBU(id_type id, MsgChannelCarrier& carrier);
    ~PBU();

    bool init(std::string const& initial_data) override final;

    void firstStep() override final;

    void step(double time) final;

    void GetRLIfromRadar();

private:
    MessageQueue<RLCMsg> msg_from_rlc;


    int target_counter = 1;

    class Target
    {
    public:
        Target();
        Target(int id, const RLCMsg& msg)
            : coords({{msg.coordinates[0],msg.coordinates[1],msg.coordinates[2]}}),
              speed({{msg.speed[0],msg.speed[1],msg.speed[2]}}),
              ID(ID),
              time(msg.time)
        {}

        //        Target& operator=(const RLCMsg& msg);

        void CalculateParametrs()
        {
            for(size_t i = 0; i < history_coords.size(); i++)
            {
                for(size_t j = 0; j < 3; j++ )
                {
                    coords[j] += history_coords[i][j];
                    speed[j] += history_speed[i][j];
                }
            }
            for(size_t i = 0; i < history_coords.size(); i++)
            {
                coords[i] = (coords[i] / history_coords.size());
                speed[i] = (speed[i] / history_speed.size());
            }

            history_coords.erase(history_coords.begin(), history_coords.end());
            history_speed.erase(history_speed.begin(), history_speed.end());

            history_coords.resize(0);
            history_speed.resize(0);
        }
        //std::map<id_type, id_type> history_id; // first - id_rlc, second - id_target

        std::vector<std::vector<double>> history_coords;
        std::vector<std::vector<double>> history_speed;

        std::vector<double> coords;
        std::vector<double> speed;

        id_type ID;
        double time = 0;
    };

    bool CheckTrack(const RLCMsg& t1, const Target& t2)
    {

        return ((t1.coordinates[0] - t2.coords[0]) * (t1.coordinates[0] - t2.coords[0]) +
                (t1.coordinates[1] - t2.coords[1]) * (t1.coordinates[1] - t2.coords[1]) +
                (t1.coordinates[2] - t2.coords[2]) * (t1.coordinates[2] - t2.coords[2]) <= 2500) ||

                ((t1.speed[0] * t1.speed[0]) - (t2.speed[0] * t2.speed[0]) +
                (t1.speed[1] * t1.speed[1]) - (t2.speed[1] * t2.speed[1]) +
                (t1.speed[2] * t1.speed[2]) - (t2.speed[2] * t2.speed[2]) <= 400);
    }

    void AddNewTarget()
    {
        id_table[std::make_pair(msg_from_rlc.front().source_id,
                                msg_from_rlc.front().message.target_id)] = target_counter;

        history_id[target_counter].insert(std::make_pair(msg_from_rlc.front().source_id,
                                                         msg_from_rlc.front().message.target_id));

        targets_time[std::make_pair(msg_from_rlc.front().source_id,
                                    msg_from_rlc.front().message.target_id)] = msg_from_rlc.front().time;
        targets.insert({target_counter, Target(target_counter, msg_from_rlc.front().message)});
        ++target_counter;
    }


    std::map<std::pair<id_type, id_type>, int> id_table;
    std::map<int, std::map<id_type, id_type>> history_id;
    std::map<std::pair<id_type, id_type>, double> targets_time;
    std::map<id_type, Target> targets;


    //std::map<id_type, std::map<id_type, RLCMsg>> all_traces; // key - rls_id, key2 - target_id
    //std::vector<std::vector<std::pair<int,int>>> identical_tracks; // <pair<rlc_id,target_id>, map<rlc_id,target_id>>

};


//struct RLCMsg
//{
//
//    vec3 coordinates;
//    vec3 speed; 				//v_x, v_y, v_z
//    double time;              //временная метка
//    double v_r;      			// скорость на лакатор
//};


#endif //MISSILESYSTEM_PBU_H
