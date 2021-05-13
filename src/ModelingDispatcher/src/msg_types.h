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

struct TargetMsg : public BasePhysicsEntity {std::string type_model;};

struct RocketMsg : public BasePhysicsEntity
{
    bool is_explosion;
    bool is_target_destroyed;
};

struct Explosion
{
    vec3 crd_rct;
};

struct Trajectory
{
    vec3 target_coords;
    vec3 target_v;
    vec3 sigma;
    vec3 sigma_half_axis;
    int target_id;
};

struct TargetCoords
{
    vec3 target_coords;
    vec3 target_v;
    vec3 zur_coords;
    vec3 zur_v;
};

struct Rocket_Start
{
    bool is_rocket_started;
    vec3 rls_rocket_coords;
};

struct is_ready
{
    bool is_ready;
};

struct Fire
{
    int target_id;
    vec3 pu_target_coords;
};

#endif //MISSILESYSTEM_MSG_TYPES_H
