#include "ModelingDispatcher.h"

ModelingDispatcher::ModelingDispatcher(double delta_time)
    : delta_time{delta_time} {}

ModelingDispatcher::~ModelingDispatcher()
{
    for(auto& it : models)
        delete it.second;
}

void ModelingDispatcher::run(std::string const& scenario)
{
    rapidjson::Document doc;
    doc.Parse(scenario);
    if(!doc.HasMember("end_time"))
        throw std::invalid_argument("Scenario does not contain end_time");
    double  end_time = doc["end_time"].GetDouble();
    initModels(doc);
}

void ModelingDispatcher::initModels(rapidjson::Document &doc)
{
    if(!doc.HasMember("objecs"))
        throw std::invalid_argument("Scenario does not contain objects");

    const rapidjson::Value& objects = doc["objects"];
    for(rapidjson::SizeType i = 0; i < objects.Size(); ++i)
    {
        const rapidjson::Value& object = objects[i];
        if(!object.HasMember("id"))
            throw std::invalid_argument("Object must have id");
        if(object.HasMember("model_name"))
            throw std::invalid_argument("Models name must be specified");

    }
}

