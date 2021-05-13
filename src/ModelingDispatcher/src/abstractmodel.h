#ifndef Model_H
#define Model_H

#include <list>
#include <iostream>
#include <fstream>
#include "rapidjson/document.h"
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
 * Пример использования смотри в tests
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
     * @param log - поток для записи результатов
     */
    Model(id_type id, MsgChannelCarrier& carrier, std::ostream& log);
    virtual ~Model() {}

    /**
     * @brief Инициализация модкли
     * @param initial_data JSON-значение, содержащее данные инициализации модели
     * @return Истина, если инициализация прошла успешно, Ложь, в противном случае
     */
    virtual bool init(const rapidjson::Value& initial_data) = 0;

    template <typename MT>
    /**
     * @brief send - отправка сообщения типа MT
     * @param time - текущее модельное время
     * @param message - сообщение
     */
    void send(double time, MT message);

    virtual void firstStep() = 0; /// первый шаг моделирования
    /**
     * @brief step - выполнить шаг моделирование
     * @param time - модельное время, на которое нужно продвинуться
     */
    virtual void step(double time) = 0;

    virtual void endStep() = 0; /// последний шаг моделирования

private:
    MsgChannelCarrier& carrier;

    template<typename T>
    void writeLogArgs(const T& arg);

    template<typename T, typename... Args>
    void writeLogArgs(const T& arg1, const Args&... args);

    bool header_exist{false};
protected:
    const id_type id; ///> id объекта моделирования

    std::ostream& log; ///> поток записи результатов

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

    template<typename... Args>
    /**
     * @brief запись в файл результата в формате csv
     * @param time - модельное время
     * @param args - параметры, которые необходимо записать в верном порядке следования
     * @attention Перед записью должен быть задан заголовок csv-таблицы
     * @attention Для всех передоваемых параметров должен быть определен оператор <<
     * @attention time всегда записывается в первый столбец
     */
    void writeLog(double time, const Args&... args);

    template<typename... Args>
    /**
     * @brief Задает заголовок csv-таблицы для файла результата
     * @param column_names - имена столбцов таблицы в верном порядке
     * @attention Столбец time по умолчанию считпется первым столбцом. Добавлять еще один столбец тиме не нужно.
     */
    void setLogHeader(Args... column_names);
};

inline Model::Model(id_type id, MsgChannelCarrier& carrier, std::ostream& log)
    : carrier{carrier}, id{id}, log{log} {}

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

template<typename T, typename... Args>
void Model::writeLogArgs(const T &arg1, const Args&... args)
{
    log << arg1 << ",";
    writeLogArgs(args...);
}

template<typename T>
void Model::writeLogArgs(const T& arg)
{
    log << arg << "\n";
}

template<typename... Args>
void Model::writeLog(double time, const Args&... args)
{
    if(!header_exist)
        throw std::runtime_error("The log doesn't have a header");
    log << time << ",";
    writeLogArgs(args...);
}

template<typename... Args>
void Model::setLogHeader(Args... column_names) {
    if(header_exist)
        throw std::runtime_error("The log already has a header");
    writeLogArgs("time", column_names...);
    header_exist = true;
}

#endif // Model_H
