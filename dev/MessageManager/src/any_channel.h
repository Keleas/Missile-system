#ifndef ANY_CHANNEL_H
#define ANY_CHANNEL_H

#include <typeinfo>
#include "msg_channel.h"

/**
 * @brief The AnyMsgChannel class
 * Вспомогательный класс для хранения канала сообщений любого типа
 */
class AnyMsgChannel
{
private:
    friend class MsgChannelCarrier;
    template <typename MT>
    /**
     * @brief AnyMsgChannel
     * @param channel - канал сообщений любого типа
     */
    AnyMsgChannel(MsgChannel<MT>* channel)
        : _holder{new channel_holder<MT>(channel)} {}
    ~AnyMsgChannel() { delete _holder; }

    template <typename U>
    /**
     * @brief cast - приводит канал сообщений к заданному типу, иначе кидает runtime_error
     * @return канал сообщений, приведенный к заданному типу
     */
    MsgChannel<U>* cast() const
    {
        if(typeid(U) != _holder->type_info())
            throw std::runtime_error("Bad any cast");
        return static_cast<channel_holder<U>*>(_holder)->_channel;
    }

    struct base_channel_holder
    {
        virtual ~base_channel_holder() {}
        virtual const std::type_info& type_info() const = 0;
    };

    template <typename MT>
    struct channel_holder : base_channel_holder
    {
        channel_holder(MsgChannel<MT>* channel) : _channel {channel} {}
        ~channel_holder() { delete (_channel); }
        const std::type_info& type_info() const
        {
            return typeid(mt);
        }
        MsgChannel<MT> *_channel;
        MT mt;
    };

    base_channel_holder* _holder;
};

#endif // ANY_CHANNEL_H
