#ifndef MISSILESYSTEM_MODELINGDISPATCHER_H
#define MISSILESYSTEM_MODELINGDISPATCHER_H

#include <map>
#include <fstream>
#include "rapidjson/document.h"
#include "abstractmodel.h"
#include "modelfactory.h"

#ifdef WIN32
#include <direct.h>
#define GetCurrentDir _getcwd
#define PathDelimiter "\\"
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#define PathDelimiter "/"
#endif

#define MAX_LOGS 100

std::string get_current_dir();

/**
 * @brief Диспетчер моделирования
 */
class ModelingDispatcher {
public:
    /**
     * @brief Конструктор
     * @param delta_time шаг по времени
     * @param factories фибрики моделей (имя модели -> (приоритет вызова, фабрика)).
     * Приоритет показывает в каком порядке будут вызоваться модели во время шага моделирования:
     * чем ниже, тем раньще вызовется модель
     */
    ModelingDispatcher(double delta_time, std::map<std::string, std::pair<int, ModelFactory*> >& factories);
    ~ModelingDispatcher();

    void setResultDirectory(std::string const& result_directory);
    std::string getResultDirectory();

    /**
     * @brief запуск моделирования
     * @param scenario сценарий имитационного моделирования - JSON-строка вида:
     * {
     *  "scenario_name": имя сценария
     *  "end_time": предельное время моделирования
     *  "objects" :
     *      [
     *          описание объектов моделирования :
     *      {
     *          "id": id объекта моделирования
     *          "model_name": имя модели
     *          "initial_data": JSON-объект, содержащий данные инициализации модели
     *      }
     *      ]
     * }
     */
    void run(std::string const& scenario);

    /**
     * @brief Очистка моделей
     */
    void clear();

    template <typename MT>
    void msgSubscribe(std::function<void(id_type, double, MT)>&& callback);
private:
    double delta_time; //> шаг по времени

    std::string res_dir{get_current_dir()};
    std::ofstream logs[MAX_LOGS];

    std::string scenario_name;

    MsgChannelCarrier carrier; //> для передачи сообщений
    std::map<int, std::vector<Model*> > models; //> модели : (приоритет -> массив моделей)

    std::map<std::string, std::pair<int, ModelFactory*> >& factories; //> ссылка на таблицу фабрик

    /**
     * @brief Инициализация моделей
     * @param doc JSON-документ содержащий сценарий ИМ
     */
    void initModels(rapidjson::Document& doc);
};

template <typename MT>
void ModelingDispatcher::msgSubscribe(std::function<void(id_type, double, MT)>&& callback)
{
    carrier.get<MT>().subscribe(callback);
}

#endif //MISSILESYSTEM_MODELINGDISPATCHER_H
