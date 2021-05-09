#ifndef MISSILESYSTEM_MSG_TYPES_H
#define MISSILESYSTEM_MSG_TYPES_H

#include "msg_channel.h"
#include <array>

typedef std::array<double, 3> vec3;

enum class TargetStatus {is_not_fly, is_fly, is_destroy, is_done};

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

struct TargetMsg : public BasePhysicsEntity {};

struct RocketMsg : public BasePhysicsEntity
{
    bool is_explosion;
    bool is_target_destroyed;
};

struct Explosion
{
    vec3 crd_rct;
};

#endif //MISSILESYSTEM_MSG_TYPES_H
