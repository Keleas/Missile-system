#pragma once

#include <stdio.h>
#include <iostream>
#include <vector>

#define UPDATE_TIME 0.001

class PU { // Параметры пусковой установки
public:
    PU(float*);

    int get_pu_number();

    float* get_pu_loc();
    void set_pu_loc(float*);

    int get_zur_amount();
    void set_zur_amount(int);

    void start_rocket(float*); // ПБУ отдает команду пуска ракеты и ее отслеживания

    ~PU() {
        std::cout << "Object pu was deleted" << std::endl;
    }

private:

    int pu_number = 0;

    float pu_loc[3];

    int zur_amount = 0;
    //вектор ракет

};