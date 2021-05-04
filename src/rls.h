#pragma once
#include <stdio.h>
#include <iostream>
#include <vector>
#include "trace.h"
#include "target.h"

#define UPDATE_TIME 0.001
#define BUFFER_LENGTH 300


class RLS {
    public:
        RLS(int, float*);

        // -------------------- Locator params --------------------
        
        struct PARAMS {
            int rls_number = 0;

            float loc[3] = {0, 0, 0};

            float observation_params[6] = {0, 0, 0, 0, 0, 0};

            float dispersion = 0;
        };

        PARAMS get_params();

        void set_params(int, float*);

        void update();

        // -------------------- Targets --------------------

        void update_targets(); // Диспетчер вызывает update и обновляет список всех целей и их координаты в среде

        void add_target(int, float*, float*, float);

        std::vector < TARGET* > get_targets();

        // -------------------- Traces --------------------

        void send_rocket_coords(int); // передача на ракету координат ракеты и цели

        bool find_rocket(float*); // ПБУ отдает команду на РЛС - отследить ракету

        // определение сбития внутри update

        bool is_traces();

        void add_trace(float*);

        std::vector < TRACE > get_traces();

        void update_traces();

        ~RLS();

    private:

        PARAMS params;

        std::vector < TARGET* > targets_vector;

        std::vector < TRACE > traces_vector;

};