#include "testmodelb.h"

TestModelBase::TestModelBase(id_type id, MsgChannelCrrier &carrier)
    : AbstractModel{id, carrier} {}

void TestModelBase::printQueue()
{
    std::cout << "int:\n";
    while(!int_queue.empty())
    {
        std::cout << "\tfrom: " << int_queue.front().source_id;
        std::cout << "\ttime: " << int_queue.front().time;
        std::cout << "\tmessage: " << int_queue.front().message;
        std::cout << std::endl;
        int_queue.pop_front();
    }
    std::cout << "str:\n";
    while(!str_queue.empty())
    {
        std::cout << "\tfrom: " << str_queue.front().source_id;
        std::cout << "\ttime: " << str_queue.front().time;
        std::cout << "\tmessage: " << str_queue.front().message;
        std::cout << std::endl;
        str_queue.pop_front();
    }
}

model1::model1(id_type id, MsgChannelCrrier& carrier, id_type listen)
    : TestModelBase{id, carrier}
{
    declareteQueue(int_queue, listen);
    declareteQueue(str_queue);
    declareteQueue(int_queue, 33);
}

void model1::firstStep()
{
    send<std::string>(0, "model1 start");
}

void model1::step(double time)
{
    t += time;
    send<int>(t, t * 2);
    send<std::string>(t, "model1");
}

model2::model2(id_type id, MsgChannelCrrier& carrier)
    : TestModelBase{id, carrier}
{
    declareteQueue(int_queue);
    declareteQueue(str_queue);
}

void model2::firstStep()
{
    send<std::string>(0, "model2 start");
}

void model2::step(double time)
{
    t += time;
    send<int>(t, t);
    send<std::string>(t, "model2");
}
