#pragma once

#include <stdio.h>
#include <iostream>
#include <vector>

#define UPDATE_TIME 0.001

class ZUR { // Параметры ракеты
public:
    ZUR(int, bool);

    int get_zur_number();

    bool get_is_ready();
    void set_is_ready(bool);

    float* get_coords();
    void set_coords(float*);

    void start_rocket(float*); // старт ракеты

    void update();

    ~ZUR() {
        std::cout << "Object zur was deleted" << std::endl;
    }

private:

    int zur_number = 0;

    bool is_ready = true;

    float coords[3];

};