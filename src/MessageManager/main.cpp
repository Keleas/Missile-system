#include <iostream>
#include "channel_crrier.h"
#include "testmodelb.h"

int main()
{
    MsgChannelCrrier carrier;
    model1 m1(1, carrier, 2);
    model2 m2(2, carrier);
    for(unsigned long i = 0; i < 10; ++i)
    {
        m1.step(1);
        m2.step(1);
        carrier.get<int>().send(33, i * 100, 321 - i * 4);
    }
    m1.printQueue();
    m2.printQueue();
    return 0;
}
