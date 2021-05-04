#pragma once

#include <stdio.h>
#include <iostream>
#include <vector>

#define UPDATE_TIME 0.001
#define BUFFER_LENGTH 300


class TARGET { // Цель в среде моделировани с задаваемыми параметрами
public:
    TARGET(int, float*, float*, float);

    int get_number();
    void set_number(int);

    float* get_coords();
    void set_coords(float*);

    float* get_velocity();
    void set_velocity(float*);

    float get_epr();
    void set_epr(float);

    ~TARGET() {
        std::cout << "Object target was deleted" << std::endl;
    }

private:

    int number = 0;
    float coords[3];
    float velocity[3];
    float epr;
};