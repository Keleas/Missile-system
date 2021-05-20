#include "channel_carrier.h"
#include "abstractmodel.h"
#include "msg_types.h"
#include "modelfactory.h"
#include <map>

class PBU : public Model
{
public:
    PBU(id_type id, MsgChannelCarrier& carrier, std::ostream& log);
    ~PBU() override;

    //void calculate(double dt);

    bool init(const rapidjson::Value& initial_data) override final;

    void firstStep() override final;

    void step(double time) final;

    void endStep() override final;

    void write_to_csv();

private:
    MessageQueue<RLCMsg> msg_from_rlc;                  // очередь сообщений от РЛС

    MessageQueue<PUtoPBUstartMsg> msg_from_pu_start;    // очередь сообщений от ПУ (для FirstStep)
    MessageQueue<PUtoPBUzurIDMsg> msg_from_pu_zur;      // очередь сообщений от ПУ (получения ID ЗУР)
    MessageQueue<PUtoPBUstartMsg> msg_from_pu;          // очередь сообщений от ПУ (обновление данных о состояниии ПУi)

    class Target
    {
    public:
        Target();
        Target(int id, const RLCMsg& msg)
            : coords({ {msg.coordinates[0],msg.coordinates[1],msg.coordinates[2]} }),
            speed({ {msg.speed[0],msg.speed[1],msg.speed[2]} }),
            ID(id), time(msg.time), first_step(true)
        {}
        //        Target& operator=(const RLCMsg& msg);

        void CalculateParametrs();

        std::vector<std::vector<double>> history_coords;
        std::vector<std::vector<double>> history_speed;

        std::vector<double> coords;
        std::vector<double> speed;

        id_type ID;
        double time = 0;
        bool first_step;
    };

    class PU {
    public:
        PU();
        PU(const PUtoPBUstartMsg& msg)
            : zur_num(msg.zur_num), status(msg.status),
            coords({ msg.coord[0], msg.coord[0], msg.coord[0] })
        {}

        int zur_num;
        bool status;
        std::vector<double> coords;
    };

    /*double CalculateDistanse(const std::vector<double>& a,
                             const std::vector<double>& b);*/

    void GetRLIfromRadar();                                         // Третичная обработка
    bool CheckTrack(const RLCMsg& t1, const Target& t2);            // Критерий сравнения целей

    void UpdateTables(int target_id);                               // обновление id_table, history_id, targets_time
    void AddNewTarget();

    void FirstStepFromPU();                                         //На первом шаге мод. получить от пу координаты и id

    void GetIdZur();                                                //Получить от ПУ id запущенного ЗУР
    void TargetDistribution();                                      //Дать команду об уничтожении цели i устаноке j


    std::map<std::pair<id_type, id_type>, int> id_table;            // key - <first - rls_id, second - target_id>, value - My_id
    std::map<int, std::map<id_type, id_type>> history_id;           // key - My_id, value - <first - rls_id, second - target_id>
    std::map<std::pair<id_type, id_type>, double> targets_time;     // key - <first - rls_id, second - target_id>, value - time
    std::map<id_type, Target> targets;                              // key - My_id, value - Target
    int target_counter = 1;                                         // счетчик целей

    std::map<id_type, PU> pu_base;                                  // key - My_id, value - PU
    std::map<id_type, std::vector<double>> pu_coords;

    std::vector<double> pbu_coords;
    double time;                                                    // время данного шага, используется для отправки сообщений
};

inline void PBU::write_to_csv()
{
    std::string sep = ", ";

    log << id << sep << pbu_coords[0] << sep << pbu_coords[1] << sep << pbu_coords[2];
    for (const auto& it : targets)
    {
        log << sep << it.second.coords[0] << sep << it.second.coords[1] << sep << it.second.coords[2]
            << sep << it.second.speed[0] << sep << it.second.speed[1] << sep << it.second.speed[2]
            << sep << it.second.time << sep << it.second.ID << "\n";
    }
}

DEFAULT_MODEL_FACTORY(PBU)