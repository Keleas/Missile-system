#ifndef MISSILESYSTEM_MSG_TYPES_H
#define MISSILESYSTEM_MSG_TYPES_H

#include "msg_channel.h"
#include <array>

typedef std::array<double, 3> vec3;

enum class TargetStatus {is_not_fly, is_fly, is_destroy, is_done};

enum class ZurStatus {is_not_fly, is_fly, is_done, is_not_done};

struct Entity
{
    std::string name;
};

struct BasePhysicsEntity : public Entity
{
    vec3 coord;
    vec3 vels;
    TargetStatus status;
};

struct TargetMsg : public BasePhysicsEntity {std::string type_model;};

struct ZurMSG : public Entity
{
    vec3 crd_zur;
    vec3 vels_zur;
    ZurStatus status;
};

struct PuToZurMsg : public Entity
{
    vec3 crd_pu;
    vec3 crd_target;
    double vel_target;
};

struct RocketMsg : public BasePhysicsEntity
{
    bool is_explosion;
    bool is_target_destroyed;
};

struct RLCMsg
{
    id_type target_id;
    std::vector<double> coordinates;
    std::vector<double> speed; 				//v_x, v_y, v_z
    double time;  				            //временная метка
};
struct PBUtoRLCMsg
{
    id_type zur_id;
};

struct PUtoPBUstartMsg
{
    id_type launcher_id;    
    vec3 coord;
    double range;
    int zur_num;
    bool status;
};

struct PUtoBPUMsg
{
    int zur_num;
    bool status;
};

struct PUMSGS
{
    vec3 target_coord;
    double target_speed;
};

struct PBUtoPUMsg : public PUMSGS
{
    id_type target_id;
//    PBUtoPUMsg(vec3 target_coord, vec3 target_speed){}
};

struct PUtoPBUzurIDMsg
{
    id_type target_id;
    id_type zur_id;
};

struct PUtoZURMsg : public PUMSGS
{
    vec3 pu_coord;
};

struct PBUtoZURMsg : public PUMSGS
{

};

struct Explosion
{
    vec3 crd_rct;
};

#endif //MISSILESYSTEM_MSG_TYPES_H
