#include "testmodel.h"

TestModelBase::TestModelBase(id_type id, MsgChannelCarrier &carrier, std::ostream& log)
    : Model{id, carrier, log} {}

/**
 * @brief TestModelBase::printQueue
 * печать очередей
 */
void TestModelBase::printQueue()
{
    log << "int:\n";
    while(!int_queue.empty())
    {
        log << "\tfrom: " << int_queue.front().source_id;
        log << "\ttime: " << int_queue.front().time;
        log << "\tmessage: " << int_queue.front().message;
        log << std::endl;
        int_queue.pop_front();
    }
    log << "str:\n";
    while(!str_queue.empty())
    {
        log << "\tfrom: " << str_queue.front().source_id;
        log << "\ttime: " << str_queue.front().time;
        log << "\tmessage: " << str_queue.front().message;
        log << std::endl;
        str_queue.pop_front();
    }
}


model1::model1(id_type id, MsgChannelCarrier& carrier, std::ostream& log)
    : TestModelBase{id, carrier, log}
{
    declareteQueue(str_queue); //декларация очереди сообщений типа string от всех
    declareteQueue(int_queue, 33);//очерередь сообщений типа int также используется для получения сообщений от отправителя с id=33
}

void model1::firstStep()
{
    /**
     * просто отправляет model1 start
     */
    send<std::string>(0, "model1 start");
}

void model1::step(double time)
{
    /**
      * увиличивает свое время и отправляет два сообщения: типа int и типа string
      */
    t += time;
    send<int>(t, t * 2);
    send<std::string>(t, "model1");
}

bool model1::init(const rapidjson::Value &initial_data) {
    id_type listen = initial_data["listen"].GetUint();
    declareteQueue(int_queue, listen); //декларация очереди сообщений от отправителя с id = listen типа int
    return true;
}

model2::model2(id_type id, MsgChannelCarrier& carrier, std::ostream& log)
    : TestModelBase{id, carrier, log}
{
    declareteQueue(int_queue); //декларация очереди сообщщений типа int от всех
    declareteQueue(str_queue); //декларация очереди сообщщений типа string от всех
}

void model2::firstStep()
{
    /**
     * просто отправляет model2 start
     */
    send<std::string>(0, "model2 start");
}

void model2::step(double time)
{
    /**
      * увиличивает свое время и отправляет два сообщения: типа int и типа string
      */
    t += time;
    send<int>(t, t);
    send<std::string>(t, "model2");
}
