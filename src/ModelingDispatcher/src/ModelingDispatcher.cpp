#include "ModelingDispatcher.h"
#include "string"

std::string get_current_dir() {
    char buff[FILENAME_MAX]; //create string buffer to hold path
    GetCurrentDir( buff, FILENAME_MAX );
    std::string current_working_dir(buff);
    return current_working_dir;
}

ModelingDispatcher::ModelingDispatcher(double delta_time, std::map<std::string, std::pair<int, ModelFactory*> >& factories)
    : delta_time{delta_time}, factories{factories} {}

ModelingDispatcher::~ModelingDispatcher()
{
    clear();
}

void ModelingDispatcher::run(std::string const& scenario)
{
    rapidjson::Document doc;
    doc.Parse(scenario.c_str());

    if(!doc.HasMember("scenario_name"))
        throw std::invalid_argument("Scenario name must be specified");

    scenario_name = doc["scenario_name"].GetString();

//    system(("mkdir " + scenario_name).c_str());

    if(!doc.HasMember("end_time"))
        throw std::invalid_argument("Scenario does not contain end_time");

    double  end_time = doc["end_time"].GetDouble();
    initModels(doc);

    for (auto &vec : models)
        for (auto &it : vec.second)
            it->firstStep();

    double time = delta_time;
    while(time < end_time)
    {
        for (auto &vec : models)
            for (auto &it : vec.second)
                it->step(time);
            time += delta_time;
    }

    for (auto &vec : models)
        for (auto &it : vec.second)
            it->endStep();
}

void ModelingDispatcher::initModels(rapidjson::Document &doc)
{
    if(!doc.HasMember("objects"))
        throw std::invalid_argument("Scenario does not contain objects");

    Model *model;
    id_type id;
    std::string model_name;
    std::string log_path;
    const rapidjson::Value& objects = doc["objects"];
    for(rapidjson::SizeType i = 0; i < objects.Size(); ++i)
    {
        const rapidjson::Value& object = objects[i];

        if(!object.HasMember("id"))
            throw std::invalid_argument(std::to_string(i) + ": Object must have id");
        id = object["id"].GetUint();


        if(!object.HasMember("model_name"))
            throw std::invalid_argument(std::to_string(i) + ": Models name must be specified");
        model_name = object["model_name"].GetString();
        if(factories.find(model_name) == factories.end())
            throw std::runtime_error(std::to_string(i) +  ": Unknown model name '" + model_name + "'");


        if(!object.HasMember("initial_data"))
            throw std::invalid_argument(std::to_string(i) + ": Initial data not found");

        log_path = res_dir + PathDelimiter + scenario_name + "_" + model_name + "_" + std::to_string(id) + ".csv";

        logs[i].open(log_path);
        model = factories[model_name].second->newModel(id, carrier, logs[i]);
        model->init(object["initial_data"]);

        models[factories[model_name].first].push_back(model);
    }
}

void ModelingDispatcher::clear()
{
    for(auto& vec : models)
        for(auto& it : vec.second)
            delete it;
    models.clear();

    for(unsigned int i = 0; i < MAX_LOGS; ++i)
        if(logs[i].is_open())
            logs[i].close();

    scenario_name = "";
}

void ModelingDispatcher::setResultDirectory(const std::string &result_directory) {
    res_dir = result_directory;
}

std::string ModelingDispatcher::getResultDirectory() {
    return res_dir;
}
