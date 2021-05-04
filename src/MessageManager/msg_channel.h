#ifndef MSG_CHANNEL_H
#define MSG_CHANNEL_H

#include <vector>
#include <atomic>
#include <functional>

class MsgChannelCrrier;
class AnyMsgChannel;

using id_type = unsigned int;

template <typename MT>
class MsgChannel
{
public:
    friend class MsgChannelCrrier;
    friend class AnyMsgChannel;

    using message_type = MT;
    using callback_type = std::function<void(id_type, double, message_type)>;

    void subscribe(callback_type &&callback);
    void subscribe(callback_type &&callback, id_type source);

    void send(id_type id, double time, message_type msg);

private:

    MsgChannel() = default;
    ~MsgChannel() {}

    struct id_exchanger
    {
        bool source_neded;
        id_type source_id{id_type()};
    };
    using callback_list_type = std::pair<id_exchanger, callback_type>;
    std::vector<callback_list_type> callback_list;

    MsgChannel(MsgChannel&) = delete;
    MsgChannel(MsgChannel&&) = delete;
};

template <typename MT>
void MsgChannel<MT>::subscribe(callback_type&& callback)
{
    callback_list_type tmp;
    tmp.first.source_neded = false;
    std::swap(tmp.second, callback);
    callback_list.push_back(tmp);
}

template <typename MT>
void MsgChannel<MT>::subscribe(callback_type&& callback, id_type source)
{
    callback_list_type tmp;
    tmp.first.source_neded = true;
    tmp.first.source_id = source;
    std::swap(tmp.second, callback);
    callback_list.push_back(tmp);
}

template <typename MT>
void MsgChannel<MT>::send(id_type id, double time, message_type msg)
{
    for(auto& callback : callback_list)
        if(!callback.first.source_neded || callback.first.source_id == id)
            callback.second(id, time, msg);
}

#endif // MSG_CHANNEL_H
