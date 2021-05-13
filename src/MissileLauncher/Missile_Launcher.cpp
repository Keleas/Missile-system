/*
Consructors:
Missile_Launcher(id,x,y,z)
Missile_Launcher(id,x,y,z,N_rocker,Range)
вспомогательнй класс - счетчик ЗУР, общий для всех ПУ
Id_Gen()
functions
CSV_logs() - return step logs as string in csv format
Missile_Launcher_Step (float dt, Id_Gen& id_gen, std::set<ZUR>& rockets)  
Launch_the_Rocket(X,Y,Z)  command from PBU
Louncher_Unit_Status() return louncher status for PBU
Missile_Launcher_Logs() rerurn logs as struct 
*/

#include <iostream>
#include <string>
#include <deque>
#include <set>
#include <sstream>

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


struct Missile_Launcher_Logs   //Log data
{
    int id;
    float X;
    float Y;
    float Z;
    int rocket_count;
    float range; 
    bool ready;
};

struct Louncher_Status
{
    bool ready;
    int rocket_count;
    float cooldown;
};



class Missile_Launcher
{private:
    // logs
    int id;
    Coordinates unit_coordinates;
    int rocket_count = 4;
    float range = 100; //100 km   int?
    bool ready = 1;
    // no logs
    float cooldown=5;  //5 seconds
    float no_launch_time=5;
    
    
    std::deque<Coordinates> launch_queue;  
    std::string unit_logs = "";
     
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
        if (N_ < 1)
        {
            ready=0;
        }
        
    }
    //functions
    bool is_ready()                   //return
    {
        return (no_launch_time >= cooldown && rocket_count >= 1);
    }
    
    
    void Launch_the_Rocket(float X,float Y,float Z)
    //Launch_the_Rocket(X,Y,Z)  
    {
        Coordinates target_coordinats;
        target_coordinats.X = X;
        target_coordinats.Z = Z;
        target_coordinats.Y = Y;
        launch_queue.push_back(target_coordinats);
    }

    std::string CSV_logs()
    {
        return unit_logs;
    }

    Louncher_Status Louncher_Unit_Status()
    {
        Louncher_Status status;
        status.ready=ready;
        status.rocket_count=rocket_count;
        status.cooldown=cooldown;
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
 
    void do_CSV_logs()   
    {     
        std::ostringstream logs;
        logs<<id<<";";
        logs<<unit_coordinates.X<<";";
        logs<<unit_coordinates.Y<<";";
        logs<<unit_coordinates.Z<<";";
        logs<<rocket_count<<";";
        logs<<range<<";";
        logs<<ready<<";";
        unit_logs = logs.str();
    }   
    
    void Missile_Launcher_Step(float dt/*, Id_Gen& id_gen, std::set<int> & rockets*/)
    //Missile_Launcher_Step(шаг моделирования,ссылка на счетчик индека ЗУР,ссылка на сет ЗУР-ов)
    {
       ready=is_ready();
       if (ready &&  !launch_queue.empty())
       {
           Coordinates target_coordinats = launch_queue.front();
           launch_queue.pop_front();
///           int id_rocket = it_gen.generate();
///        ZUR rocket = ZUR_constractor(id_rocket,unit_coordinates,target_coordinats,)
///        rockets.push_back(rocket);
           no_launch_time = 0;
           rocket_count -= 1;
           ready = 0;
       }
       do_CSV_logs();
       no_launch_time += dt;
    }       

};


/*
int main()
{
    std::cout<<"Hello World\n";
    Missile_Launcher a(1,2,3,4);
    a.do_CSV_logs();
    std::string b = a.CSV_logs();
    std::cout<<b<<"\n";
    a.Missile_Launcher_Step(0.01);
    std::string c=a.CSV_logs();
    std::cout<<c<<"\n";
    a.Launch_the_Rocket(7,8,9);
    a.Missile_Launcher_Step(0.01);
    std::string d=a.CSV_logs();
    std::cout<<d<<"\n";
    a.Missile_Launcher_Step(0.01);
    std::string e=a.CSV_logs();
    std::cout<<e<<"\n";
    a.Missile_Launcher_Step(4.99);
    std::string f=a.CSV_logs();
    std::cout<<f<<"\n";
     a.Missile_Launcher_Step(0.01);
    std::string h=a.CSV_logs();
    std::cout<<h<<"\n";
}
/*
