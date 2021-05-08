#ifndef TESTMODELBASE_H
#define TESTMODELBASE_H

#include "../src/abstractmodel.h"

/**
 * @brief The TestModelBase class
 * Пример использования AbstaractModel.
 * Класс содержит две очереди сообщений: типа int и типа string.
 * Этот класс промежуточный, нужен только для объявления методы печати очередей.
 */
class TestModelBase : public Model
{
public:
    TestModelBase(id_type id, MsgChannelCarrier& carrier);
    virtual ~TestModelBase() {}

    virtual bool init(std::string const& initial_data) override { return true; }

    void printQueue();///> Печать очередей

protected:
    MessageQueue<int> int_queue;/// Очередь типа int
    MessageQueue<std::string> str_queue;/// Очередь типа string
    double t = 0;
};

/**
 * @brief The model1 class
 * Пример модели
 */
class model1 : public TestModelBase
{
public:
    model1(id_type id, MsgChannelCarrier& carrier, id_type listen);
    virtual ~model1() {}

    virtual void firstStep() override;
    virtual void step(double time) override;
private:
};

class model2 : public TestModelBase
{
public:
    model2(id_type id, MsgChannelCarrier& carrier);
    virtual ~model2() {}

    virtual void firstStep() override;
    virtual void step(double time) override;
private:
};

#endif // TESTMODELBASE_H
