#include <stdio.h>
#include <iostream>
#include "pbu.h"
#include "trace.h"

PBU::PBU(float* loc, std::vector<RLS*> rls_vector, std::vector<PU*> pu_vector)
{
    for (int i = 0; i < 3; ++i) {
        if (loc[i] != NULL)
            PBU::pbu_loc[i] = loc[i];
    }

    PBU::pu_vector = pu_vector;

    PBU::rls_vector = rls_vector;
}

void PBU::update_traces_array()
{
    std::vector < RLS* > rls_vec = get_rls_vector();

    for (int i = 0; i < rls_vec.size(); ++i) {
        std::vector < TRACE > rls_traces = rls_vec.at(i)->get_traces();
        for (int j = 0; j < rls_traces.size(); ++j) {
            TRACE tmp_trace = rls_traces.at(j);
            //rls_vec.push_back(tmp_trace);

        }
    }
    
}
