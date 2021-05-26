#include "airtarget.h"

#define square_destroy_range 40000


AirTarget::AirTarget(id_type id, MsgChannelCarrier &carrier, std::ostream& log)
    : Model{id, carrier, log}
{
    declareteQueue(recieve_msg);
}

Vector3D GeoToLocal(GeodezicCoodinates GD, GeocentricCoodinates GC, GeocentricCoodinates GC0)
{
    double sinL = sin(GD.longitude);
    double cosL = cos(GD.longitude);
    double sinB = sin(GD.latitude);
    double cosB = cos(GD.latitude);
    double xLoc = sinL*(GC.x-GC0.x) + (-cosL)*(GC.y-GC0.y);
    double yLoc = cosB*cosL*(GC.x-GC0.x) + cosB*sinL*(GC.y-GC0.y) + sinB*(GC.z-GC0.z);
    double zLoc = (-cosL)*sinB*(GC.x-GC0.x) + (-sinB)*sinL*(GC.y-GC0.y) + cosB*(GC.z-GC0.z);

    return Vector3D(xLoc, yLoc, zLoc);
}

GeocentricCoodinates LocalToGeo(GeodezicCoodinates GD, Vector3D Loc, GeocentricCoodinates GC0)
{
    double sinL = sin(GD.longitude);
    double cosL = cos(GD.longitude);
    double sinB = sin(GD.latitude);
    double cosB = cos(GD.latitude);
    double xGeo = sinL*Loc.x + cosB*cosL*Loc.y + (-cosL*sinB)*Loc.z + GC0.x;
    double yGeo = (-cosL)*Loc.x + cosB*sinL*Loc.y + (-sinB)*sinL*Loc.z + GC0.y;
    double zGeo = sinB*Loc.y + cosB*Loc.z + GC0.z;

    return GeocentricCoodinates(xGeo, yGeo, zGeo);
}

bool AirTarget::init(const rapidjson::Value& initial_data)
{
    targetModelType = initial_data["target_model_type"].GetString();
    targetName = initial_data["target_name"].GetString();
    param.MAX_TRANSVERSE_OVERLOAD = initial_data["target_max_Nx"].GetDouble();
    param.MAX_NORMAL_OVERLOAD =  initial_data["target_max_Ny"].GetDouble();
    param.MAX_MAH =  initial_data["target_max_M"].GetDouble();
    param.MIN_TRANSVERSE_OVERLOAD =  initial_data["target_min_Nx"].GetDouble();
    param.PRACTICAL_ROOF = initial_data["target_practical_roof"].GetDouble();

    for (auto& v : initial_data["target_points"].GetArray())
    {
        TrajectoryPoint p;
        double x = v["x"].GetDouble();
        double y = v["y"].GetDouble();
        double z = v["z"].GetDouble();

        GeocentricCoodinates GC = PBUToGeo(GeodezicToGeoCentric(GD_Msc), {x,y,z});

        p.initialPoint = GC;
        p.initialVel = v["vel"].GetDouble();
        control_points.push_back(p);
    }
    return true;
}

void AirTarget::firstStep()
{
    status = TargetStatus::is_fly;

    setLogHeader("target_model", "target_id", "X", "Y", "Z", "Vx", "Vy", "Vz", "Elevation", "Azimuth", "Status");

    //write_to_csv(true);
}

void AirTarget::step(double time)
{
    if (!recieve_msg.empty())
    {
        Vector3D crd_rct_inPBU = recieve_msg.front().message.crd_zur;
        GeocentricCoodinates crd_rct_GC = PBUToGeo(GeodezicToGeoCentric(GD_Msc), crd_rct_inPBU);
        recieve_msg.pop_front();
        double dist = (coords-crd_rct_GC).lengthSquared();

        if (dist <= square_destroy_range)
            status = TargetStatus::is_destroy;
    }
    double dt;
    if (data.nPoints != 0)
    {
        dt = time - data.times.back();
    }
    else
        dt = time;

    dt = 0.01;

    if (num_point_passed == control_points.size()-1)
        status = TargetStatus::is_done;

    if (status == TargetStatus::is_fly)
        calculate(0.01);

    TargetMsg msg;
    GeocentricCoodinates GC(data.xPos.back(), data.yPos.back(), data.zPos.back());
    Vector3D crd = GeoToPBU(GeodezicToGeoCentric(GD_Msc), GC);
    msg.coord = {crd.x, crd.y, crd.z};
    msg.vels = {data.xVel.back(), data.yVel.back(), data.zVel.back()};
    msg.status = status;

    writeLog(data.times.back(), targetModelType, id, msg.coord[0], msg.coord[1], msg.coord[2],
            msg.vels[0], msg.vels[1], msg.vels[2],
            data.angle_horizontal_plane.back(), data.wayAngle.back(), int(status));

    //write_to_csv();

    send<TargetMsg>(data.times.back(), msg);
}

void AirTarget::calculate(double dt)
{
    std::vector<Vector3D> _points;
    std::vector<Vector3D> _vels;
    std::vector<Vector3D> _accels;
    std::vector<double> _normOV;
    std::vector<double> _transOV;
    std::vector<double> _bankAngle;
    std::vector<double> _horizontal_plane;
    std::vector<double> _wayAngle;

    Vector3D NuCur(0,0,0);
    Vector3D NuCurDer(0,0,0);
    Vector3D NuDes(0,0,0);
    Vector3D NuDesDer(0,0,0);
    Vector3D NuCurNext(0,0,0);
    Vector3D radiusVector(0,0,0);
    Vector3D NormalOverload(0,0,0);
    Vector3D VelComp(0,0,0);
    Vector3D AccelsComp(0,0,0);

    double k_nu = 0.6;
    double fi = 0;

    int i = num_point_passed;
    GeocentricCoodinates GC_1;

    if (data.nPoints == 0)
    {
        GC_1 = GeocentricCoodinates(control_points[0].initialPoint.x, control_points[0].initialPoint.y, control_points[0].initialPoint.z);
        _points.push_back(Vector3D(GC_1.x, GC_1.y, GC_1.z));
        _vels.push_back({0,0,0});
        _accels.push_back(AccelsComp);
        _normOV.push_back(0);
        _transOV.push_back(0);
        _horizontal_plane.push_back(0);
        _bankAngle.push_back(0);
        _wayAngle.push_back(0);
    }
    else
    {
        GC_1 = GeocentricCoodinates(data.xPos.back(), data.yPos.back(), data.zPos.back());
        double vel = sqrt(data.xVel.back() * data.xVel.back() + data.yVel.back() * data.yVel.back()
                              + data.zVel.back() * data.zVel.back());

        NuCur = {data.xVel.back()/vel, data.yVel.back()/vel, data.zVel.back()/vel};
        NuCur = this->NuCurNext;

        _vels.push_back(Vector3D(NuCur*vel));

        _accels.push_back(Vector3D(data.xAcc.back(), data.yAcc.back(), data.zAcc.back()));
        _normOV.push_back(data.normalOverload.back());
        _transOV.push_back(data.transverseOverload.back());
        _horizontal_plane.push_back(data.angle_horizontal_plane.back());
        _bankAngle.push_back(data.bankAngle.back());
        _wayAngle.push_back(data.wayAngle.back());
    }

    double speed = control_points[i].initialVel;
    GeocentricCoodinates GC_2(control_points[i+1].initialPoint.x, control_points[i+1].initialPoint.y, control_points[i+1].initialPoint.z);
    GeocentricCoodinates GC = GC_1;
    GeodezicCoodinates GD = GeocentricToGeodezic(GC_1).toRadians();

    k_nu = 0.6;
    Vector3D LocalCoord_2 = GeoToLocal(GD, GC_2, GC);

    NuDes = (LocalCoord_2 - radiusVector);
    NuDes.normalize();

    double fi_for_correction = angeleBetween(Vector3D(GC), Vector3D(GC_2));
    double speedForChangingHeight = (Vector3D(GC_2).length() - Vector3D(GC).length()) / fi_for_correction;
    double alphaCorrection = acos ( sqrt ( Vector3D(GC).sqrlength() /
                                           (Vector3D(GC).sqrlength() + speedForChangingHeight * speedForChangingHeight)));
    double B = 0;
    if (pow(NuDes.x, 2) + pow(NuDes.z, 2) > 0.0001)
        B = sqrt (cos(alphaCorrection) / (pow(NuDes.x, 2) + pow(NuDes.z, 2)));
    else
        B = 0;

    NuDes.x *= B;
    NuDes.z *= B;
    if (fabs(Vector3D(GC_2).length() - Vector3D(GC).length()) > 0.00001)
        NuDes.y = sin(alphaCorrection) * Sign(Vector3D(GC_2).length() - Vector3D(GC).length());
    else
        NuDes.y = 0;

    NuDes.normalize();

    if (data.nPoints == 0)
    {
        NuCur = NuDes;
    }

    double cosFi = dot(NuCur, NuDes);

    if (cosFi >= 0.9999999999)
    {
        fi = 0;
        cosFi = 1;
        NuDesDer(0, 0, 0);

        //                if (k_nu - 0.3*dt*dt > 0)
        //                    k_nu -= 0.3*dt*dt;
        //                else
        //                    k_nu = 0;
    }
    else if (cosFi <= -0.9999999999)
    {
        double alpha =  M_PI/30;
        double x = NuCur.x;
        double z = NuCur.z;

        NuCur.x = x*cos(alpha) - z*sin(alpha);
        NuCur.z = x*sin(alpha) + z*cos(alpha);

        cosFi = dot(NuCur, NuDes);
        fi = acos(cosFi);

        //                if (k_nu < 0.3)
        //                    k_nu += 0.3*dt*dt;
        NuDesDer = (NuDes - NuCur*cosFi)*(k_nu*fi/sin(fi));
    }
    else
    {
        fi = acos(cosFi);

        //                if (k_nu < 0.3)
        //                    k_nu += 0.3*dt*dt*dt;
        NuDesDer = (NuDes - NuCur*cosFi)*(k_nu*fi/sin(fi));
    }

    //std::cout << "NuCur " << NuCur.x << " " << NuCur.y << " " << NuCur.z << " " << "NuDes " << NuDes.x  << " " << NuDes.y << " " << NuDes.z << "\n";

    Vector3D OY(0, 1, 0);
    NormalOverload = NuDesDer*(speed/g) + OY - NuCur*NuCur.y;

    if (param.MAX_NORMAL_OVERLOAD > 0)
    {
        if (NormalOverload.length() >= param.MAX_NORMAL_OVERLOAD)
        {
            Vector3D B = (NuDes - NuCur*cosFi)*(speed*fi/(g*sin(fi)));
            double a = B.sqrlength();
            double b = B.y - dot(B, NuCur)*NuCur.y;
            double c = 1 - NuCur.y*NuCur.y - param.MAX_NORMAL_OVERLOAD*param.MAX_NORMAL_OVERLOAD;

            if (a == 0)
                k_nu = -1*c / b;
            else
                k_nu = (- b + sqrt( b * b - a * c )) / a;

            if (fi != 0)
                NuDesDer = (NuDes - NuCur*cosFi)*(k_nu*fi/sin(fi));
            else
                NuDesDer = (NuDes - NuCur*cosFi)*k_nu;

            NormalOverload = NuDesDer*(speed/g) + OY - NuCur*NuCur.y;
        }
    }

    _normOV.push_back(NormalOverload.length());

    NuCurDer = (NormalOverload - OY + NuCur*NuCur.y) * (g/speed);

    int k = 0;
    if (speed < control_points[i+1].initialVel && speed <= param.MAX_MAH*330)
    {
        k++;
        speed += g*param.MAX_TRANSVERSE_OVERLOAD*dt;
        _transOV.push_back(param.MAX_TRANSVERSE_OVERLOAD);
    }

    if (speed > control_points[i+1].initialVel && speed <= param.MAX_MAH*330)
    {
        k++;
        speed += g*param.MIN_TRANSVERSE_OVERLOAD*dt;
        _transOV.push_back(param.MIN_TRANSVERSE_OVERLOAD);
    }

    if (k == 0)
        _transOV.push_back(param.MAX_TRANSVERSE_OVERLOAD);

    if (speed >= param.MAX_MAH*330)
        speed = param.MAX_MAH*330;

    VelComp = NuCur*speed;
    AccelsComp = (VelComp - _vels.back()) / dt;
    _vels.push_back(VelComp);
    _accels.push_back(AccelsComp);

    NuCurNext = NuCur + NuCurDer*dt;
    NuCurNext.normalize();

    radiusVector += NuCurNext*(speed*dt);
    GC = LocalToGeo(GD, radiusVector, GC);
    _points.push_back(Vector3D(GC.x, GC.y, GC.z));

    double Lx = NormalOverload.x / NormalOverload.length();
    double Lz = NormalOverload.z / NormalOverload.length();
    _bankAngle.push_back(asin(-NuCur.x*Lx + NuCur.z*Lz));

    _horizontal_plane.push_back(asin(NuCur.y));
    _wayAngle.push_back(asin(NuCur.z/(cos(asin(NuCur.y)))));

    GD = GeocentricToGeodezic(GC).toRadians();

    double dist = (GC_2 - GC).length();

    //std::cout << dist << "\n";

    if (dist <= 100)
    {
        radiusVector = GeoToLocal(GD, GC_2, GC);
        _points.push_back(Vector3D(GC_2.x, GC_2.y, GC_2.z));
        VelComp = NuCur*speed;
        AccelsComp = (VelComp - _vels.back()) / dt;
        _vels.push_back(VelComp);
        _accels.push_back(AccelsComp);
        _normOV.push_back(_normOV.back());
        _transOV.push_back(_transOV.back());
        _bankAngle.push_back(_bankAngle.back());
        _horizontal_plane.push_back(_horizontal_plane.back());
        _wayAngle.push_back(_wayAngle.back());
        num_point_passed++;
    }

    this->NuCurNext = NuCurNext;
    data.insert(data.nPoints, _points, _vels, _accels, _bankAngle, _horizontal_plane, _wayAngle, _transOV, _normOV, dt);
    coords = {data.xPos.back(), data.yPos.back(), data.zPos.back()};
}

TargetStatus AirTarget::get_status()
{
    return status;
}

Vector3D AirTarget::get_coords()
{
    double x = data.xPos.back();
    double y = data.yPos.back();
    double z = data.zPos.back();

    return Vector3D(x, y, z);
}

void AirTarget::set_status(TargetStatus trg)
{
    status = trg;
}
