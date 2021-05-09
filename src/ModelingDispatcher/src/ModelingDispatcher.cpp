#include "ModelingDispatcher.h"

ModelingDispatcher::ModelingDispatcher(double delta_time, std::map<std::string, std::pair<int, ModelFactory*> >& factories)
    : delta_time{delta_time}, factories{factories} {}

ModelingDispatcher::~ModelingDispatcher()
{
    for(auto& vec : models)
        for(auto& it : vec.second)
            delete it;
}

void ModelingDispatcher::run(std::string const& scenario)
{
    rapidjson::Document doc;
    doc.Parse(scenario.c_str());
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

        model = factories[model_name].second->newModel(id, carrier);
        model->init(object["initial_data"]);

        models[factories[model_name].first].push_back(model);
    }
}

void ModelingDispatcher::step(double time)
{
    for(auto& vec : models)
        for(auto& it : vec.second)
            it->step(time);
}
