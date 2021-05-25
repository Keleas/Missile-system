#include "PBU.h"

PBU::PBU(id_type id, MsgChannelCarrier& carrier, std::ostream& log)
    : Model{ id, carrier, log}
{
    declareteQueue(msg_from_rlc);
    declareteQueue(msg_from_pu_start);
    declareteQueue(msg_from_pu);
    declareteQueue(msg_from_pu_zur);
}

PBU::~PBU() {}

bool PBU::init(const rapidjson::Value &initial_data)
{
    pbu_coords = std::vector<double>({initial_data["x"].GetDouble(),
                                      initial_data["y"].GetDouble(),
                                      initial_data["z"].GetDouble()});
    return true;
}

void PBU::firstStep()
{
    setLogHeader("target_id", "X", "Y", "Z", "Vx", "Vy", "Vz", "time_detect");

    FirstStepFromPU();
}

void PBU::step(double time)
{
    GetIdZur();                                                             // получить ID пущенных ЗУР если такие имеются
    GetRLIfromRadar();                                                      // получение информации о целях
    TargetDistribution(time);                                                   // целераспределение

    for(const auto& it : targets)
    {
        writeLog(time, it.first,
                it.second.coords[0], it.second.coords[1], it.second.coords[2],
                it.second.speed[0], it.second.speed[1], it.second.speed[2],
                it.second.time);
    }
}

void PBU::Target::CalculateParametrs()
{
    if(history_coords.empty() && history_speed.empty())
    {
        if(first_step)
            first_step = false;                                     // для первого шага

        return;
    }

    if(first_step)
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
            coords[i] /= (history_coords.size() + 1);
            speed[i]  /= (history_speed.size() + 1);
        }
        first_step = false;
    }
    else
    {
        coords.clear();
        coords.resize(3);
        speed.clear();
        speed.resize(3);

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
            coords[i] /= history_coords.size();
            speed[i]  /= history_speed.size();
        }
    }

    history_coords.clear();
    history_speed.clear();
}

bool PBU::CheckTrack(const RLCMsg& t1, const Target& t2)
{
    return ((t1.coordinates[0] - t2.coords[0]) * (t1.coordinates[0] - t2.coords[0]) +
            (t1.coordinates[1] - t2.coords[1]) * (t1.coordinates[1] - t2.coords[1]) +
            (t1.coordinates[2] - t2.coords[2]) * (t1.coordinates[2] - t2.coords[2]) <= 2500) &&

            ((t1.speed[0] * t1.speed[0]) - (t2.speed[0] * t2.speed[0]) +
            (t1.speed[1] * t1.speed[1]) - (t2.speed[1] * t2.speed[1]) +
            (t1.speed[2] * t1.speed[2]) - (t2.speed[2] * t2.speed[2]) <= 400);
}

void PBU::UpdateTables(int target_id)
{
    id_table[std::make_pair(msg_from_rlc.front().source_id,
                            msg_from_rlc.front().message.target_id)] = target_id;

    history_id[target_id].insert(std::make_pair(msg_from_rlc.front().source_id,
                                                msg_from_rlc.front().message.target_id));

    targets_time[std::make_pair(msg_from_rlc.front().source_id,
                                msg_from_rlc.front().message.target_id)] = msg_from_rlc.front().time;
}

void PBU::AddNewTarget()
{
    UpdateTables(target_counter);

    targets.insert({target_counter, Target(target_counter, msg_from_rlc.front().message)});
    ++target_counter;
}


void PBU::GetRLIfromRadar()
{
    std::cout<<"*********************"<<'\n';
    if(!msg_from_rlc.empty())
    {
        double step_time = msg_from_rlc.front().time;

        while (!msg_from_rlc.empty())
        {
            if(id_table.empty())
            {
                AddNewTarget();
            }
            else
            {
                if(id_table.count(std::make_pair(msg_from_rlc.front().source_id,
                                                 msg_from_rlc.front().message.target_id)) == 0) // Если данные о цели с РЛС k еще не приходили
                {
                    for(auto& target : targets) // Если цель была обнаружена другими РЛС
                    {
                        if(CheckTrack(msg_from_rlc.front().message, target.second))
                        {
                            UpdateTables(target.second.ID);

                            target.second.history_coords.push_back(msg_from_rlc.front().message.coordinates);
                            target.second.history_speed.push_back(msg_from_rlc.front().message.speed);

                            break;
                        }
                    }
                    AddNewTarget();         // Такой цели не было обнаружено другими РЛС
                }
                else                        // Инфформация о данной цели уже приходила с РЛС k (обнавление данных)
                {
                    id_type My_ID = id_table[std::make_pair(msg_from_rlc.front().source_id,
                                                            msg_from_rlc.front().message.target_id)];

                    targets_time[std::make_pair(msg_from_rlc.front().source_id,
                                                msg_from_rlc.front().message.target_id)] = msg_from_rlc.front().time; // обновляем время


                    targets[My_ID].history_coords.push_back(msg_from_rlc.front().message.coordinates);
                    targets[My_ID].history_speed.push_back(msg_from_rlc.front().message.speed);
                }
            }
            msg_from_rlc.pop_front();
        }

        /*******************************В этом блоке происходит поиск тех целей, которые не были обнавленны на данном шаге****************************************/

        for(auto& item : targets_time) // Смотрим по времени, какие данные обновились за этот шаг
        {
            if(item.second != step_time)
            {
                std::pair<id_type, id_type> ID_from_rlc = item.first;
                int  My_ID = id_table[item.first];

                id_table.erase(ID_from_rlc);      // удаляем умоминания из таблицы соответсвия

                history_id[My_ID].erase(ID_from_rlc.first);
                if(history_id.count(My_ID) == 0)
                {
                    targets.erase(My_ID);
                }

                targets_time.erase(item.first);
            }
        }
        for(auto& item : targets)
            item.second.CalculateParametrs();                       // Пересчитываем координаты
    }
}

void PBU::FirstStepFromPU()
{
    while (!msg_from_pu_start.empty())
    {
        pu_base[msg_from_pu_start.front().source_id] = msg_from_pu_start.front().message;
        msg_from_pu_start.pop_front();
    }
}

void PBU::TargetDistribution(double time)
{
    for(auto& target: targets)
    {
        for(auto& launcher: pu_base)
        {
            if(launcher.second.status == true && launcher.second.zur_num > 0)
            {
                PBUtoPUMsg msg{{target.second.coords[0],target.second.coords[1],target.second.coords[2]},
                               {target.second.speed[0],target.second.speed[1],target.second.speed[2]}};

                send<PBUtoPUMsg>(launcher.first, time, msg);
                --launcher.second.zur_num;
                break;
            }
        }
    }
}

void PBU::GetIdZur()
{
    while (!msg_from_pu_zur.empty())
    {
        PBUtoRLCMsg msg {msg_from_pu_zur.front().message.zur_id};
        send<PBUtoRLCMsg>(msg_from_pu_zur.front().time, msg);
        msg_from_pu_zur.pop_front();
    }
}
void PBU::endStep() {}

//double CalculateDistanse(const std::vector<double>& a, const std::vector<double>& b)
//{
//    return sqrt((a[0] - b[0]) * (a[0] - b[0]) +
//            (a[1] - b[1]) * (a[1] - b[1]) +
//            (a[2] - b[2]) * (a[2] - b[2]));
//}


