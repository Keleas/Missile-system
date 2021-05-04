#pragma once

#include <stdio.h>
#include <iostream>
#include <vector>
#include "rls.h"
#include "pu.h"

#define UPDATE_TIME 0.001
#define BUFFER_LENGTH 300


class PBU {
public:
    PBU(float*, std::vector < RLS* >, std::vector < PU* >);

    void update_traces_array();

    void update();

    // -------------------- PBU params --------------------
    
    void set_pbu_loc(float *);
    float* get_pbu_loc();

    // -------------------- RLS --------------------

    int get_rls_amount();

    std::vector < RLS* > get_rls_vector();

    void add_rls(RLS*);
    void remove_rls(RLS*);

    // -------------------- PU --------------------

    int get_pu_amount();

    std::vector < PU* > get_pu_vector();

    void add_pu(int, float*, int);

    void remove_pu(PU*);
    
    int select_launcher(int); // ������� �������� ��������� ��� ������ ���� �

    void rocket_launch(int, int); // ������� ������ �� �� � �� ���� �

    // -------------------- Traces --------------------

    void set_trace(float*);

    std::vector < TRACE* > get_traces();

    void update_traces(); // ����������� �������� ����� �� ������ �� ���� ���

    void start_rocket(float*); // ��� ������ ������� ����� ������ � �� ������������

    bool check_hit(int); // ��� ��������� ������ ���� �

    ~PBU() {
        std::cout << "Object pbu was deleted" << std::endl;
    }

private:

    int rls_amount = 0;

    float pbu_loc[3];

    std::vector < TRACE > traces_vector;

    std::vector < PU* > pu_vector;

    std::vector < RLS* > rls_vector;

};