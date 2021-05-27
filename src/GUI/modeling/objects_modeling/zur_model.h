#ifndef ZUR_MODEL_H
#define ZUR_MODEL_H
#include "abs_moving_model.h"

class zur_model: public abs_moving_model
{
public:
    zur_model();
    ~zur_model();
    zur_model(QJsonObject initData);
    int get_id(){return id;}
private:
    bool ready = false;
};

#endif // ZUR_MODEL_H
