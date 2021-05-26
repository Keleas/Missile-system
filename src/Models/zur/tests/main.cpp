#include <iostream>

#include "zur.h"
#include "ModelingDispatcher.h"


void printMSG(id_type id, double time, ZurMSG msg)
{
    std::cout << "Message from " << id << " at time " << time <<std::endl;
    std::cout << "coord: " << msg.crd_zur[0] << " " << msg.crd_zur[1] << " " << msg.crd_zur[2] << std::endl;
    std::cout << "vel: " << msg.vels_zur[0] << " " << msg.vels_zur[1] << " " << msg.vels_zur[2] << std::endl;
    std::cout << "name: " << msg.name << std::endl;
}

int main(int argc, char *argv[])
{

    std::map<std::string, std::pair<int, ModelFactory*> > factories;
    ///std::pair<int, ModelFactory*> fac1 = {1, new AirTargetFactory()};
    ///factories["AirTarget"] = fac1;

    ModelingDispatcher md(0.01, factories);
    ///md.msgSubscribe<TargetMsg>(printMSG);
    std::cout << "Starting...\n";
    ///md.run(scenario);
    std::cout << "finished!\n";

    /*
    GeodezicCoodinates GD_Msc = GeodezicCoodinates(55, 37, 0);

    Vector3D crd(37035.885104, 574478.867425, -15932.8059282);
    //Vector3D crd(0, 0, 0);
    //Vector3D crd(233495.792456, 303480.14781, -11386.4586281);

    GeodezicCoodinates GD = GeocentricToGeodezic(PBUToGeo(GeodezicToGeoCentric(GD_Msc), crd));

    std::cout << GD.latitude << " " << GD.longitude << " " << GD.altitude;*/

    /* GC1(2551014.27811, 2641652.6159, 5209575.04365);
    GeocentricCoodinates GC2(2521759.87014, 2270602.78583, 5394218.20446);
    GeocentricCoodinates GC3(2587663.12314, 2329942.34136, 5325983.96688);

    GeodezicCoodinates GD_Msc = GeodezicCoodinates(55, 37, 0); //костыыыыль

    Vector3D p1 = GeoToPBU(GeodezicToGeoCentric(GD_Msc), GC1);
    Vector3D p2 = GeoToPBU(GeodezicToGeoCentric(GD_Msc), GC2);
    Vector3D p3 = GeoToPBU(GeodezicToGeoCentric(GD_Msc), GC3);

    std::cout << std::setprecision(12) << p1.x << " " << p1.y << " " << p1.z << "\n";
    std::cout << std::setprecision(12) << p2.x << " " << p2.y << " " << p2.z << "\n";
    std::cout << std::setprecision(12) << p3.x << " " << p3.y << " " << p3.z << "\n";
    */
}
