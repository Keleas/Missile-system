#pragma once

#include <stdio.h>
#include <iostream>
#include "rls.h"
//#include "pbu.h"
//#include "pu.h"


int main()
{
    // Создаем РЛС

    float params_array[11] = { 0, 0, 0, 0, 0, 45, 1, 400, 30, 40, 1 };
    //RLS *rls_1 = new RLS(params_array); //rls_number, x, y, z, alpha, beta, r_min, r_max, theta, delta, gamma

    // Создаем ПУ

    //float params_array[4] = { 0, 0, 0, 0 };
    //PU::PU* pu_1 = new PU::PU(params_array); //rls_number, x, y, z, alpha, beta, r_min, r_max, theta, delta, gamma

    // Создаем ПБУ и передаем РЛС и ПУ в подчинение ПБУ




    void update_targets();

    //delete rls_1;

    return 0;
}