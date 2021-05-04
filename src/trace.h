#pragma once

#include <stdio.h>
#include <iostream>
#include <vector>

struct TRACE {  // Цель с измеряемыми параметрами
    int target_number = 0;
    float R = 0;
    float beta = 0;
    float eps = 0;
    float v_r = 0;
    float epr = 0; // эпр

    std::string target_type = "plain"; // цели или ракета

    int rls = 0;

    float rls_loc[3] = {0 , 0, 0};
};