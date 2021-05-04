#include <stdio.h>
#include <iostream>
#include "rls.h"

#define UPDATE_TIME 0.001

RLS::RLS(int number, float* args)
{
    RLS::PARAMS* params = new RLS::PARAMS();
    RLS::set_params(number, args);
}

// -------------------- Locator params --------------------

RLS::PARAMS RLS::get_params()
{
    return params;
}

void RLS::set_params(int rls_number, float* args)
{
    RLS::params.rls_number = rls_number;

    for (int i = 0; i < 3; ++i) {
        if (args[i] != NULL)
            RLS::params.loc[i] = args[i];
    }

    for (int i = 0; i < 6; ++i) {
        if (args[3 + i] != NULL)
            RLS::params.observation_params[i] = args[3 + i];

    }
    if (args[9] != NULL)
        RLS::params.dispersion = args[9];
}

void RLS::update() {
    
    RLS::update_targets();
    
    //some code ... // сканирование просранства и тд

    RLS::update_traces();

    //send_msg(RLS::get_traces());
}

void RLS::update_targets()
{
}

void RLS::add_target(int number, float* location, float* velocity, float epr)
{
    targets_vector = get_targets();
    TARGET* tmp_target = new TARGET(number, location, velocity, epr);
    targets_vector.push_back(tmp_target);
}

std::vector<TARGET*> RLS::get_targets()
{
    return targets_vector;
}

void RLS::send_rocket_coords(int)
{
    //coords = find_target_coords(int);
    //send_mes(int, coords);
}

bool RLS::find_rocket(float*)
{
    // Создание канала связи с ракетой
    return false;
}

bool RLS::is_traces()
{
    return RLS::traces_vector.size() ? true : false;
}

void RLS::add_trace(float* trace_coords)
{
    std::vector < TRACE > traces = RLS::get_traces();
    
    TRACE trace;

    RLS::traces_vector.push_back(trace);
}

std::vector<TRACE> RLS::get_traces()
{
    return RLS::traces_vector;
}

void RLS::update_traces()
{
}

RLS::~RLS() {
    std::cout << "Object rls was deleted" << std::endl;
}
