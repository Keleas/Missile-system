#ifndef MISSILESYSTEM_MODELFACTORY_H
#define MISSILESYSTEM_MODELFACTORY_H

#include "abstractmodel.h"

/**
 * @brief Класс абстрактной фабрики модели
 */
class ModelFactory
{
public:
    ModelFactory() = default;
    virtual ~ModelFactory() {}

    /**
     * Фабричный метод
     * @param id
     * @param carrier
     * @return
     */
    virtual Model* newModel(id_type id, MsgChannelCarrier& carrier, std::ostream& log) = 0;
};

/**
 * Создает фабрику моделей, в которй только вызывается new
 * Класс фабрики будет иметь имя *имя класса модели* + Factory
 */
#define DEFAULT_MODEL_FACTORY(model)                                                                                     \
    class model##Factory : public ModelFactory                                                                           \
    {                                                                                                                    \
    public:                                                                                                              \
        virtual Model* newModel(id_type id, MsgChannelCarrier& carrier, std::ostream& log) override final    \
            { return new model(id, carrier, log); }                                                                      \
    };
#endif //MISSILESYSTEM_MODELFACTORY_H
