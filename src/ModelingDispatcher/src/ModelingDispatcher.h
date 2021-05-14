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

#define MAX_LOGS 100 //Максимальное количество одновременно открытых файлов результатов

std::string get_current_dir();

/**
 * @brief Диспетчер моделирования
 */
class ModelingDispatcher {
public:
    /**
     * @brief Конструктор
     * @param delta_time шаг по времени
     * @param factories таблица фибрик моделей с приоритетом (имя модели -> (приоритет вызова, фабрика)).
     * Приоритет показывает в каком порядке будут вызоваться модели во время шага моделирования:
     * чем ниже, тем раньще вызовется модель
     * @attention таблица фабрик не очищается внутри класса, ее небходимо очищать отдельна после завершения работы диспетчера
     */
    ModelingDispatcher(double delta_time, std::map<std::string, std::pair<int, ModelFactory*> >& factories);
    ~ModelingDispatcher();

    /**
     * @brief Задает директорию, в которю будут записываться результаты (по умолчанию используется директория запуска)
     * @param result_directory путь к директории
     */
    void setResultDirectory(std::string const& result_directory);
    std::string getResultDirectory(); /// Возвращает путь к диретории рузультатов

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

    void clear(); /// Очистка моделей

    template <typename MT>
    /**
     * @brief Подписаться на сообщение заданного типа
     * Позволяет следить за сообщениями от различных моделей в процессе моделирования
     * @tparam MT тип сообщения
     * @param callback функция обработчик
     */
    void msgSubscribe(typename MsgChannel<MT>::callback_type&& callback);

private:
    double delta_time; //> шаг по времени

    std::string res_dir{get_current_dir()}; //> директория, в которую будут складываться результаты от моделей
    std::ofstream logs[MAX_LOGS]; //> потоки выводв в файлы рузультатов

    std::string scenario_name; //> имя сценария

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
void ModelingDispatcher::msgSubscribe(typename MsgChannel<MT>::callback_type&& callback)
{
    carrier.get<MT>().subscribe(std::move(callback));
}

#endif //MISSILESYSTEM_MODELINGDISPATCHER_H
