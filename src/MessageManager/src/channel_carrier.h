#ifndef CHANNEL_CRRIER_H
#define CHANNEL_CRRIER_H

#include <vector>
#include "any_channel.h"

/**
 * @brief The MsgChannelCarrier class контейнер для каналов сообщений
 * Только посредством экземпляра данного класса можно создовать новые каналы и получать к ним доступ
 */
class MsgChannelCarrier
{
public:
    MsgChannelCarrier() = default;
    ~MsgChannelCarrier();

    template <typename MT>
    /**
     * @brief get - возвращает каналл сообщений заданного типа. Если каналла нет, создает его
     * @return каналл сообщений заданного типа
     */
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
    return *(channels[i]->cast<MT>());
}

inline MsgChannelCarrier::~MsgChannelCarrier()
{
    for(auto const& it: channels)
        delete it;
}

#endif // CHANNEL_CRRIER_H
