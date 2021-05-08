#ifndef Model_H
#define Model_H

#include <list>
#include <iostream>
#include "channel_carrier.h"

template <typename MT>
/**
 * @brief The MessageQueueElement struct
 * Элемент очереди сообщений
 */
struct MessageQueueElement
{
    const id_type source_id; ///> id отправителя
    const double time; ///> модельное время отправки
    MT message; ///> само сообщение
};

/**
 * @brief The Model class Абстрактный класс модели
 * От него должны наследоваться все модели, чтобы иметь возможность отправлять и/или получать сообщения
 * Пример использования смотри в файлах testmodel.h, testmodel.cpp и main.cpp
 */
class Model
{
public:
    template <typename MT>
    using MessageQueue = std::list<MessageQueueElement<MT> >; ///тип очереди сообщений
    // При желании можно заменить на любой другой контейнер

    /**
     * @brief Model - конструктор
     * @param id - id моделируемого объекта
     * @param carrier - контейнер каналов сообщений
     */
    Model(id_type id, MsgChannelCarrier& carrier);
    virtual ~Model() {}

    virtual bool init(std::string const& initial_data) = 0;

    template <typename MT>
    /**
     * @brief send - отправка сообщения типа MT
     * @param time - текущее модельное время
     * @param message - сообщение
     */
    void send(double time, MT message);

    /**
     * @brief firstStep - первый шаг моделирования
     */
    virtual void firstStep() = 0;
    /**
     * @brief step - выполнить шаг моделирование
     * @param time - модельное время, на которое нужно продвинуться
     */
    virtual void step(double time) = 0;

private:
    MsgChannelCarrier& carrier;
protected:
    const id_type id; ///> id объекта моделирования

    template <typename MT>
    /**
     * @brief declareteQueue - декларировать очередь сообщений
     * @param queue - очередь, в которую будут складываться все сообщения заданного типа
     */
    void declareteQueue(MessageQueue<MT>& queue);

    template <typename MT>
    /**
     * @brief declareteQueue - декларировать очередь сообщений
     * @param queue - очередь, в которую будут складываться все сообщения заданного типа от заданных отправителей
     * @param source - id от кого получать сообщения
     */
    void declareteQueue(MessageQueue<MT>& queue, id_type source);
};

inline Model::Model(id_type id, MsgChannelCarrier& carrier)
    : carrier{carrier}, id{id} {}

template <typename MT>
void Model::send(double time, MT message)
{
    carrier.get<MT>().send(id, time, message);
}

template <typename MT>
void Model::declareteQueue(MessageQueue<MT> &queue)
{
    carrier.get<MT>().subscribe([&queue](id_type from, double time, MT mes)
    {
        queue.push_front({from, time, mes});
    });
}

template <typename MT>
void Model::declareteQueue(MessageQueue<MT> &queue, id_type source)
{
    carrier.get<MT>().subscribe([&queue](id_type from, double time, MT mes)
    {
        queue.push_front({from, time, mes});
    }, source);
}

#endif // Model_H
