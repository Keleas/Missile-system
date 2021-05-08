#include <iostream>
#include "channel_carrier.h"

void int_process_1(id_type id, double time, int msg)
{
    std::cout << "1\tTIME: " << time << "\t message from " << id << ": " << msg << std::endl;
}

void int_process_2(id_type id, double time, int msg)
{
    std::cout << "2\tTIME: " << time << "\t message from " << id << ": " << msg << std::endl;
}

void str_process(id_type id, double time, std::string const& msg)
{
    std::cout << "str\tTIME: " << time << "\t message from " << id << ": " << msg << std::endl;
}

int main()
{
    MsgChannelCarrier carrier;
    carrier.get<int>().subscribe(int_process_1);
    carrier.get<int>().subscribe(int_process_2, 1);
    carrier.get<std::string>().subscribe(str_process);

    for(int i = 0; i < 10; ++i)
    {
        carrier.get<int>().send(i % 2, i, i);
        carrier.get<std::string>().send(i % 2, i, "message " + std::to_string(i));
    }
}