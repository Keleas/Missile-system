#ifndef MISSILESYSTEM_MODELFACTORY_H
#define MISSILESYSTEM_MODELFACTORY_H

#include "abstractmodel.h"

class ModelFactory
{
public:
    ModelFactory() = default;
    ~ModelFactory() {}

    virtual Model* newModel(id_type id, MsgChannelCarrier& carrier) = 0;
};

#define DEFAULT_MODEL_FACTORY(model)                                                    \
    class model##Factory : public ModelFactory                                          \
    {                                                                                   \
    public:                                                                             \
        virtual Model* newModel(id_type id, MsgChannelCarrier& carrier) override final  \
            { return new model(id, carrier); }                                          \
    };
#endif //MISSILESYSTEM_MODELFACTORY_H
