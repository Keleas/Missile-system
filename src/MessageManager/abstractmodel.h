#ifndef ABSTRACTMODEL_H
#define ABSTRACTMODEL_H

#include <list>
#include "channel_crrier.h"

template <typename MT>
struct MessageQueueElement
{
    const id_type source_id;
    const double time;
    MT message;
};

class AbstractModel
{
public:
    template <typename MT>
    using MessageQueue = std::list<MessageQueueElement<MT> >;

    AbstractModel(id_type id, MsgChannelCrrier& carrier);
    virtual ~AbstractModel() {}

    template <typename MT>
    void send(double time, MT message);

    virtual void firstStep() = 0;
    virtual void step(double time) = 0;

private:
    MsgChannelCrrier& carrier;
protected:
    const id_type id;

    template <typename MT>
    void declareteQueue(MessageQueue<MT>& queue);

    template <typename MT>
    void declareteQueue(MessageQueue<MT>& queue, id_type source);
};

inline AbstractModel::AbstractModel(id_type id, MsgChannelCrrier& carrier)
    : carrier{carrier}, id{id} {}

template <typename MT>
void AbstractModel::send(double time, MT message)
{
    carrier.get<MT>().send(id, time, message);
}

template <typename MT>
void AbstractModel::declareteQueue(MessageQueue<MT> &queue)
{
    carrier.get<MT>().subscribe([&queue](id_type from, double time, MT mes)
    {
        queue.push_front({from, time, mes});
    });
}

template <typename MT>
void AbstractModel::declareteQueue(MessageQueue<MT> &queue, id_type source)
{
    carrier.get<MT>().subscribe([&queue](id_type from, double time, MT mes)
    {
        queue.push_front({from, time, mes});
    }, source);
}

#endif // ABSTRACTMODEL_H
