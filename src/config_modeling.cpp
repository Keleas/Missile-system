#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <ctime>

using namespace std;


void modeling_config(int num_objects, int num_params, double* params)
// как параметры передаем число объектов каждого типа, число параметров данного объекта и затем их параметры массивом
{
    struct tm newtime;
    time_t ltime;
    char buf[50];
    ltime=time(&ltime);
    localtime_r(&ltime, &newtime);

    //int Year = newtime.tm_year + 1900;
    //int Month = newtime.tm_mon + 1;
    int Day = newtime.tm_mday;
    int Hour = newtime.tm_hour;
    //int Min = newtime.tm_min;
    //int Sec = newtime.tm_sec;

    cout << Day << Hour << endl;

    string config_name = to_string(Day)+ '_' + to_string(Hour);//to_string(Hour) + '_' + to_string(Min) + '_' + to_string(Sec);

    // указатель файла
    fstream fout;

    // открывает существующий CSV-файл или создает новый файл.
    fout.open(config_name + "_config.csv", ios::out | ios::app);

    fout << num_objects << "\n";
    //cout << params[0] << params[32] << endl;

    // Цикл по объектам текущего типа
    for (int i = 0; i < num_objects; i++) {

        // Вставляем данные в файл
        for (int j = 0; j < num_params-1; j++) {
            fout << params[i*num_params + j] << ", ";
        }
        fout << params[i*num_params + num_params-1] << "\n";
    }

    fout.close();
}

int main()
{
    int num_rls = 3;
    int num_rls_params = 11;
    double params[33] = {0, 0, 0, 0, 0, 45, 1, 400, 30, 40, 1,
                         1, 0, 0, 0, 0, 45, 1, 400, 30, 40, 1,
                         2, 0, 0, 0, 0, 45, 1, 400, 30, 40, 1 };
    modeling_config(num_rls, num_rls_params, params);

    return 0;
}