#ifndef MISSILESYSTEM_MODELINGDISPATCHER_H
#define MISSILESYSTEM_MODELINGDISPATCHER_H

#include <map>
#include "rapidjson/document.h"
#include "abstractmodel.h"
#include "modelfactory.h"

class ModelingDispatcher {
public:
    ModelingDispatcher(double delta_time, std::map<std::string, std::pair<int, ModelFactory*> >& factories);
    ~ModelingDispatcher();

    void run(std::string const& scenario);

    template <typename MT>
    MsgChannel<MT>& getChannel() { return carrier.get<MT>();}
private:
    double current_time{0.}, delta_time;

    MsgChannelCarrier carrier;
    std::map<int, std::vector<Model*> > models;

    std::map<std::string, std::pair<int, ModelFactory*> >& factories;

    void initModels(rapidjson::Document& doc);

    void step(double time);
};


#endif //MISSILESYSTEM_MODELINGDISPATCHER_H
