#ifndef MISSILESYSTEM_MODELINGDISPATCHER_H
#define MISSILESYSTEM_MODELINGDISPATCHER_H

#include <map>
#include "rapidjson/document.h"
#include "abstractmodel.h"

class ModelingDispatcher {
public:
    ModelingDispatcher(double delta_time);
    ~ModelingDispatcher();

    void run(std::string const& scenario);
private:
    double current_time{0.}, delta_time;

    MsgChannelCarrier carrier;
    std::map<it_type, Model*> models;

    void initModels(rapidjson::Document& doc);
};


#endif //MISSILESYSTEM_MODELINGDISPATCHER_H
