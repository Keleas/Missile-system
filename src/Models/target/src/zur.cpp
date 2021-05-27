#include "zur.h"

zur::zur(id_type id, MsgChannelCarrier &carrier, std::ostream& log)
    : Model{id, carrier, log}
{
    declareteQueue(recieve_msg_PBU);
    declareteQueue(recieve_msg_PU);
}

bool zur::init(const rapidjson::Value& initial_data)
{
    rocketName = initial_data["rocket_name"].GetString();
    param.MAX_TRANSVERSE_OVERLOAD = initial_data["rocket_max_Nx"].GetDouble();
    param.MAX_NORMAL_OVERLOAD =  initial_data["rocket_max_Ny"].GetDouble();
    param.MAX_MAH =  initial_data["rocket_max_M"].GetDouble();
    param.MIN_TRANSVERSE_OVERLOAD =  initial_data["rocket_min_Nx"].GetDouble();
    param.PRACTICAL_ROOF =  initial_data["rocket_practical_roof"].GetDouble();

    return 0;
}

void zur::firstStep()
{
    status = ZurStatus::is_fly;
    setLogHeader("target_id", "X", "Y", "Z", "Vx", "Vy", "Vz", "Elevation", "Azimuth", "Status");
    //write_to_csv(true);
}

void zur::step(double time)
{
    GeocentricCoodinates GC_target;
    bool is_target_init = false;
    Vector3D crd_target;
    double vel_target;
    if (!recieve_msg_PU.empty())
    {
        crd_target = recieve_msg_PU.front().message.target_coord;
        vel_target = recieve_msg_PU.front().message.target_speed;

        Vector3D crd_pu = recieve_msg_PU.front().message.pu_coord;
        start_point.initialPoint = PBUToGeo(GeodezicToGeoCentric(GD_Msc), crd_pu);
        start_point.initialVel = 1.5 * vel_target;

        GC_target = PBUToGeo(GeodezicToGeoCentric(GD_Msc), crd_target);

        recieve_msg_PU.pop_front();

        start_time = time;

        start_calculate = true;
        is_target_init = true;
    }

    if (!recieve_msg_PBU.empty())
    {
        crd_target = Vector3D(recieve_msg_PBU.front().message.target_coord);
        vel_target = recieve_msg_PBU.front().message.target_speed;

        GC_target = PBUToGeo(GeodezicToGeoCentric(GD_Msc), crd_target);

        recieve_msg_PBU.pop_front();
        is_target_init = true;
    }

    if (data.nPoints != 0)
    {
        GeocentricCoodinates GC_rocket = {data.xPos.back(), data.yPos.back(), data.zPos.back()};
        if ((GC_target-GC_rocket).length() <= 200)
            is_target_init = false;

        std::cout << "CHECK LENGTH at " << time << " : " << (GC_target-GC_rocket).length() << std::endl;
    }

    if (start_calculate && is_target_init)
    {
        double dt;
        if (data.nPoints != 0)
        {
            dt = time - data.times.back();
        }
        else
            dt = time;

        dt = 0.01;

        if (!is_tossed)
        {
            toss_rocket(dt);
        }
        else
        {
            std::vector<TrajectoryPoint> points_rocket(2);

            points_rocket[0].initialPoint.x = data.xPos.back();
            points_rocket[0].initialPoint.y = data.yPos.back();
            points_rocket[0].initialPoint.z = data.zPos.back();
            points_rocket[0].initialVel = sqrt(data.xVel.back()*data.xVel.back() + data.yVel.back()*data.yVel.back() + data.zVel.back()*data.zVel.back());

            GC_target = PBUToGeo(GeodezicToGeoCentric(GD_Msc), crd_target);

            TrajectoryPoint target_pos(GC_target, 1.5*vel_target);
            points_rocket[1] = target_pos;

            calculate(dt, points_rocket);
            data.times.back() += start_time;
        }

        if (data.nPoints != 0)
        {
            ZurMSG msg;
            GeocentricCoodinates GC(data.xPos.back(), data.yPos.back(), data.zPos.back());
            Vector3D crd = GeoToPBU(GeodezicToGeoCentric(GD_Msc), GC);
            msg.crd_zur = {crd.x, crd.y, crd.z};
            msg.vels_zur = {data.xVel.back(), data.yVel.back(), data.zVel.back()};
            msg.status = status;

            writeLog(data.times.back(), id, msg.crd_zur[0], msg.crd_zur[1], msg.crd_zur[2],
                    msg.vels_zur[0], msg.vels_zur[1], msg.vels_zur[2],
                    data.angle_horizontal_plane.back(), data.wayAngle.back(),
                    int(status));

            //write_to_csv();

            send<ZurMSG>(data.times.back(), msg);
        }
    }
}

ZurStatus zur::get_status()
{
    return status;
}

Vector3D zur::get_coords()
{
    double x = data.xPos.back();
    double y = data.yPos.back();
    double z = data.zPos.back();

    return Vector3D(x, y, z);
}

void zur::set_status(ZurStatus trg)
{
    status = trg;
}

void zur::calculate(double dt, std::vector<TrajectoryPoint> control_points)
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

    double speed = control_points[1].initialVel;
    GeocentricCoodinates GC_2(control_points[1].initialPoint.x, control_points[1].initialPoint.y, control_points[1].initialPoint.z);
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

        NuDesDer = (NuDes - NuCur*cosFi)*(k_nu*fi/sin(fi));
    }
    else
    {
        fi = acos(cosFi);
        NuDesDer = (NuDes - NuCur*cosFi)*(k_nu*fi/sin(fi));
    }

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
    if (speed < control_points[1].initialVel && speed <= param.MAX_MAH*330)
    {
        k++;
        speed += g*param.MAX_TRANSVERSE_OVERLOAD*dt;
        _transOV.push_back(param.MAX_TRANSVERSE_OVERLOAD);
    }

    if (speed > control_points[1].initialVel && speed <= param.MAX_MAH*330)
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
    }

    this->NuCurNext = NuCurNext;
    data.insert(data.nPoints, _points, _vels, _accels, _bankAngle, _horizontal_plane, _wayAngle, _transOV, _normOV, dt);
    coords = {data.xPos.back(), data.yPos.back(), data.zPos.back()};
}

void zur::toss_rocket(double dt)
{
    int n_steps = round(0.5/dt)+1;
    double h = 50;

    data.nPoints++;

    GeodezicCoodinates GD_tmp = GeocentricToGeodezic(GeocentricCoodinates(start_point.initialPoint.x, start_point.initialPoint.y, start_point.initialPoint.z));
    GD_tmp.altitude = GD_tmp.altitude + data.nPoints*(h/n_steps);
    GeocentricCoodinates GC_tmp = GeodezicToGeoCentric(GD_tmp);

    data.times.push_back(data.nPoints*dt + start_time);

    data.xPos.push_back(GC_tmp.x);
    data.yPos.push_back(GC_tmp.y);
    data.zPos.push_back(GC_tmp.z);

    data.xVel.push_back(0);
    data.yVel.push_back(100);
    data.zVel.push_back(0);

    data.xAcc.push_back(0);
    data.yAcc.push_back(100);
    data.zAcc.push_back(0);

    data.bankAngle.push_back(0);
    data.angle_horizontal_plane.push_back(90*DEGREES_TO_RADIANS);
    data.wayAngle.push_back(0);

    Vector3D OY(0, 1, 0);
    data.normalOverload.push_back((OY*(data.yVel.back()/g) + OY - OY*data.yVel.back()).length());
    data.transverseOverload.push_back(1);

    if (GD_tmp.altitude > 50)
        is_tossed = true;
}
