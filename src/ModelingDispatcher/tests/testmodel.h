#ifndef TESTMODELBASE_H
#define TESTMODELBASE_H

#include "abstractmodel.h"
#include "modelfactory.h"

/**
 * @brief The TestModelBase class
 * Пример использования AbstaractModel.
 * Класс содержит две очереди сообщений: типа int и типа string.
 * Этот класс промежуточный, нужен только для объявления методы печати очередей.
 */
class TestModelBase : public Model
{
public:
    TestModelBase(id_type id, MsgChannelCarrier& carrier, std::ostream& log);
    virtual ~TestModelBase() {}

    virtual bool init(const rapidjson::Value& initial_data) override { return true; }

    virtual void endStep() override { printQueue(); }

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
    model1(id_type id, MsgChannelCarrier& carrier, std::ostream& log);
    virtual ~model1() {}

    virtual bool init(const rapidjson::Value& initial_data) override final;

    virtual void firstStep() override;
    virtual void step(double time) override;
private:
};

class model2 : public TestModelBase
{
public:
    model2(id_type id, MsgChannelCarrier& carrier, std::ostream& log);
    virtual ~model2() {}

    virtual void firstStep() override;
    virtual void step(double time) override;
private:
};

DEFAULT_MODEL_FACTORY(model1)
DEFAULT_MODEL_FACTORY(model2)

#endif // TESTMODELBASE_H
