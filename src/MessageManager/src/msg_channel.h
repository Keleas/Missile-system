#ifndef MSG_CHANNEL_H
#define MSG_CHANNEL_H

#include <vector>
#include <atomic>
#include <functional>

class MsgChannelCarrier;
class AnyMsgChannel;

using id_type = unsigned int;

#define SUPER_ID 1234567

template <typename MT>
/**
 * @brief The MsgChannel class
 * Канал для передачи сообщений определенного типа
 */
class MsgChannel
{
public:
    friend class MsgChannelCarrier;
    friend class AnyMsgChannel;

    using message_type = MT;
    using callback_type = std::function<void(id_type, double, message_type)>;/// тип функции-обработчика сообщений

    /**
     * @brief subscribe - подписаться на все сообщения
     * @param callback - функция-обработчик сообщения
     */
    void subscribe(callback_type &&callback);
    /**
     * @brief subscribe - подписаться на все сообщения от определенного id
     * @param callback - функция-обработчик сообщения
     * @param source - id от кого получать сообщения
     */
    void subscribe(callback_type &&callback, id_type source);

    /**
     * @brief subscribe - подписаться на сообщения адресованные определенному id
     * @param id - id адресата
     * @param callback - функция-обработчик сообщения
     */
    void subscribe(id_type id, callback_type &&callback);

    /**
     * @brief subscribe - подписаться на сообщения адресованные определенному id от определенного id
     * @param id - id адресата
     * @param callback - функция-обработчик сообщения
     * @param source - id от кого получать сообщения
     */
    void subscribe(id_type id, callback_type &&callback, id_type source);

    /**
     * @brief send - отправить сообщение всем
     * @param id - id отправителя
     * @param time - текущее модельное время
     * @param msg - сообщение
     */
    void send(id_type id, double time, message_type msg);

    /**
     * @brief send - отправить сообщение конкретному id
     * @param id - id отправителя
     * @param to - id получателя
     * @param time - текущее модельное время
     * @param msg - сообщение
     */
    void send(id_type id, id_type to, double time, message_type msg);

private:

    MsgChannel() = default; /// конструктор и деструктор приватные
    ~MsgChannel() {}

    struct id_exchanger
    {
        bool super_receiver; /// флаг возможности получения сообщений от всех отправителей вне зависимости от адресата
        id_type id{id_type()}; /// id получателя (не используется, если выставлен super_receiver)
        bool source_needed; /// флаг получения сообщений только от конкретного отправителя
        id_type source_id{id_type()}; /// id отправителя (не используется, если выставлен source_needed)
    };
    using callback_list_type = std::pair<id_exchanger, callback_type>;
    std::vector<callback_list_type> callback_list;///> список обработчиков

    MsgChannel(MsgChannel&) = delete; /// копирующий и перемещающий конструкторы удалены
    MsgChannel(MsgChannel&&) = delete;
};

template <typename MT>
void MsgChannel<MT>::subscribe(callback_type&& callback)
{
    callback_list_type tmp;
    tmp.first.super_receiver = true;
    tmp.first.source_needed = false;
    std::swap(tmp.second, callback);
    callback_list.push_back(tmp);
}

template <typename MT>
void MsgChannel<MT>::subscribe(callback_type&& callback, id_type source)
{
    callback_list_type tmp;
    tmp.first.super_receiver = true;
    tmp.first.source_needed = true;
    tmp.first.source_id = source;
    std::swap(tmp.second, callback);
    callback_list.push_back(tmp);
}

template <typename MT>
void MsgChannel<MT>::subscribe(id_type id, callback_type &&callback)
{
    callback_list_type tmp;
    tmp.first.super_receiver = false;
    tmp.first.id = id;
    tmp.first.source_needed = false;
    std::swap(tmp.second, callback);
    callback_list.push_back(tmp);
}

template <typename MT>
void MsgChannel<MT>::subscribe(id_type id, callback_type &&callback, id_type source)
{
    callback_list_type tmp;
    tmp.first.super_receiver = false;
    tmp.first.id = id;
    tmp.first.source_needed = true;
    tmp.first.source_id = source;
    std::swap(tmp.second, callback);
    callback_list.push_back(tmp);
}

template <typename MT>
void MsgChannel<MT>::send(id_type id, double time, message_type msg)
{
    for(auto& callback : callback_list)
        if(!callback.first.source_needed || callback.first.source_id == id)
            callback.second(id, time, msg);
}

template <typename MT>
void MsgChannel<MT>::send(id_type id, id_type to, double time, message_type msg)
{
    for(auto& callback : callback_list)
        if((callback.first.super_receiver || callback.first.id == to) &&
        (!callback.first.source_needed || callback.first.source_id == id))
            callback.second(id, time, msg);
}


#endif // MSG_CHANNEL_H
