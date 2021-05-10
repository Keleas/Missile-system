#include "PBU.h"

PBU::PBU(id_type id, MsgChannelCarrier& carrier, std::ostream& log)
    : Model{id, carrier, log}
{
    //declareteQueue(msg_from_rlc);
}


PBU::~PBU() {}

//bool PBU::init(const std::string &initial_data) {
//    return true;
//}

void PBU::firstStep() {

}

void PBU::step(double time) {
//обработка сообщений
//моделирование
//отправка сообщений
}



