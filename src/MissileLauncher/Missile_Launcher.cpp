/*
Consructors:
Missile_Launcher(id,x,y,z)
Missile_Launcher(id,x,y,z,N_rocker,Range)

вспомогательнй класс - счетчик ЗУР, общий для всех ПУ
Id_Gen()

functions
CSV_logs() - return logs as string in csv format
Missile_Launcher_Step(float dt, Id_Gen& id_gen, std::set<ZUR>& rockets)  
Launch_the_Rocket(X,Y,Z)  command from PBU
*/


#include <iostream>

//constexpr real dt==0.01;

#include <string>  
#include <cmath> 
//подключить библиотеку ЗУР
//#include

struct Coordinates      //coordinates
{
    float X;
    float Y;
    float Z;
};

class Id_Gen            //missile id generator 
{
    int i = 0;
public:
    int generate()
    {
        int id = i;
        i += 1;
        return id;
    }
};


struct Missile_Launcher_Logs()   //Log data
{
    int id;
    float X;
    float Y;
    float Z;
    int rocket_count;
    float range; 
    bool ready;
}

struct Louncher_Status()
{
    bool ready_status;
    int rocket_count_status;
    float cooldown_status;
}



class Missile_Launcher
{private:
    // logs
    int id;
    Coordinates unit_coordinates;
    int rocket_count = 4;
    float range = 100; //100 km   int?
    bool ready = 1;
    // no logs
    real cooldown=5;  //5 seconds
    real no_launch_time=6;
    
    
    std::duque<Coordinates>=launch_queue;  
    string unit_logs = "";
     
public:
    //contructors
    Missile_Launcher(int id_, float X_, float Y_, float Z_ )   
    //costructor(id,x,y,z)    колличество ЗУР, радиус по уполчанию
    {
        id = id_;
        unit_coordinates.X = X_;
        unit_coordinates.Y = Y_;
        unit_coordinates.Z = Z_;
    }
    
    Missile_Launcher(int id_, float X_, float Y_, float Z_, int N_, float R_)   //costructor(id,x,y,z,Nrocket,R)
    {
        id = id_;
        unit_coordinates.X = X_;
        unit_coordinates.Y = Y_;
        unit_coordinates.Z = Z_;
        rocket_count = N_;
        range = R_;
        if N_ < 1
        {
            ready=0;
        }
        
    }
    //functions
    bool is_ready()                   //return
    {
        return (no_launch_time_time >= cooldown && rocket_count >= 1);
    }
    
    
    void Launch_the_Rocket(float X,float Y,float Z)
    //Launch_the_Rocket(X,Y,Z)  
    {
        Coordinates target_coordinats(X,Y,Z);
        lounch_queue.push_back(target_coordinats);
    }

    string CSV_logs()
    {
        return unit_logs;
    }

    Louncher_Status Louncher_Unit_Status()
    {
        Louncher_Status status(ready, rocket_count, cooldown-);
        return status;
    }

    
    Missile_Launcher_Logs Step_Logs()
    {
        Missile_Launcher_Logs logs;
        logs.id = id;
        logs.X = unit_coordinates.X;
        logs.Y = unit_coordinates.Y;
        logs.Z = unit_coordinates.Z;
        logs.rocket_count = rocket_count;
        logs.range = range;
        logs.ready = is_ready();
        
    }
    
    void Missile_Launcher_Step(float dt, Id_Gen& id_gen, std::set<ZUR>& rockets)
    //Missile_Launcher_Step(шаг моделирования,ссылка на счетчик индека ЗУР,ссылка на сет ЗУР-ов)
    {
       ready=is_ready();
       
       

       if (ready &&  !launch_queue.empty())
       {
           
           
           
           
           Coordinates target_coordinats = launch_queue.pop_front();
           int id_rocket = it_gen.generate();
///        ZUR rocket = ZUR_constractor(id_rocket,unit_coordinates,target_coordinats,)
///        rockets.push_back(rocket);
           no_launch_time = 0;
           rocket_count -= 1;
           
       }
       Missile_Launcher_Logs step_logs = Step_Logs();
       
       
///    CSV Logs
///   scv + "/n"+"n;X;Y;Z;N_rocket;Range;ready"
 
       unit_logs = unit_logs + 
                 + step_logs.id_rocket +";"
                 + step_logs.X +";"
                 + step_logs.Y +";"
                 + step_logs.Z +";"
                 + step_logs.rocket_count +";"
                 + step_logs.range + ";"
                 + step_logs.ready + "/n";





    
    
}
