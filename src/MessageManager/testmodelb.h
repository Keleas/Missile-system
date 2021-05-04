#ifndef TESTMODELBASE_H
#define TESTMODELBASE_H

#include "abstractmodel.h"

class TestModelBase : public AbstractModel
{
public:
    TestModelBase(id_type id, MsgChannelCrrier& carrier);
    virtual ~TestModelBase() {}

    void printQueue();

protected:
    MessageQueue<int> int_queue;
    MessageQueue<std::string> str_queue;
    double t = 0;
};

class model1 : public TestModelBase
{
public:
    model1(id_type id, MsgChannelCrrier& carrier, id_type listen);
    virtual ~model1() {}

    virtual void firstStep() override;
    virtual void step(double time) override;
private:
};

class model2 : public TestModelBase
{
public:
    model2(id_type id, MsgChannelCrrier& carrier);
    virtual ~model2() {}

    virtual void firstStep() override;
    virtual void step(double time) override;
private:
};

#endif // TESTMODELBASE_H
