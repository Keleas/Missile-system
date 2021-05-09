#include "PBU.h"

PBU::PBU(id_type id, MsgChannelCarrier& carrier)
    : Model{id, carrier}
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



