#include "PBU.h"

PBU::PBU(id_type id, MsgChannelCarrier& carrier)
    : Model{id, carrier}
{
    declareteQueue(msg_from_rlc);
}


PBU::~PBU() {}

bool PBU::init(const std::string &initial_data) {
    return true;
}

void PBU::firstStep() {
    GetRLIfromRadar();
    //FindIdenticalTracks();

}
//  std::map<id_type, std::map<int, RLCMsg>> all_traces;
void PBU::GetRLIfromRadar()
{
    double step_time = msg_from_rlc.front().time;
    while (!msg_from_rlc.empty())
    {
        if(id_table.empty())
        {
            void AddNewTarget();            
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
                        id_table[std::make_pair(msg_from_rlc.front().source_id,
                                                msg_from_rlc.front().message.target_id)] = target.second.ID;

                        history_id[target.second.ID].insert(std::make_pair(msg_from_rlc.front().source_id,
                                                                           msg_from_rlc.front().message.target_id));

                        targets_time[std::make_pair(msg_from_rlc.front().source_id,
                                                    msg_from_rlc.front().message.target_id)] = msg_from_rlc.front().time;

                        target.second.history_coords.push_back(msg_from_rlc.front().message.coordinates);
                        target.second.history_speed.push_back(msg_from_rlc.front().message.speed);

                        break;
                    }
                }
                void AddNewTarget();    // Такой цели не было обнаружено другими РЛС
            }
            else                        // Инфформация об данной цели уже приходила с РЛС k
            {
                id_type My_ID = id_table[std::make_pair(msg_from_rlc.front().source_id,
                                                       msg_from_rlc.front().message.target_id)];

                targets_time[std::make_pair(msg_from_rlc.front().source_id,
                                            msg_from_rlc.front().message.target_id)] = msg_from_rlc.front().time; // обновляем время


                targets[My_ID].history_coords.push_back(msg_from_rlc.front().message.coordinates);
                targets[My_ID].history_speed.push_back(msg_from_rlc.front().message.speed);
            }
        }
        msg_from_rlc.erase(msg_from_rlc.begin());
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


void PBU::step(double time) {
    //обработка сообщений
    //моделирование
    //отправка сообщений
}



