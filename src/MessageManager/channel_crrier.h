#ifndef CHANNEL_CRRIER_H
#define CHANNEL_CRRIER_H

#include <map>
#include <iostream>
#include "any_channel.h"

class MsgChannelCarrier
{
public:
    MsgChannelCarrier() = default;
    ~MsgChannelCarrier();

    template <typename MT>
    MsgChannel<MT>& get();

private:
    std::vector<AnyMsgChannel*> channels;

    MsgChannelCarrier(MsgChannelCarrier&) = delete;
    MsgChannelCarrier(MsgChannelCarrier&&) = delete;
};

template<typename MT>
MsgChannel<MT> &MsgChannelCarrier::get()
{
    static unsigned int i = channels.size();
    if(i >= channels.size())
        channels.push_back(new AnyMsgChannel(new MsgChannel<MT>()));
    std::cout << i << " " << channels.size() << std::endl;
    return *(channels[i]->cast<MT>());
}

inline MsgChannelCarrier::~MsgChannelCarrier()
{
    for(auto const& it: channels)
        delete it;
}

#endif // CHANNEL_CRRIER_H
