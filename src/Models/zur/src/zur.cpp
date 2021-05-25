#include "zur.h"

bool zur::init(const rapidjson::Value& initial_data)
{
    rocketModelType = initial_data["rocket_model_type"].GetString();
    rocketName = initial_data["rocket_name"].GetString();
    param.MAX_TRANSVERSE_OVERLOAD = initial_data["rocket_max_Nx"].GetDouble();
    param.MAX_NORMAL_OVERLOAD =  initial_data["rocket_max_Ny"].GetDouble();
    param.MAX_MAH =  initial_data["rocket_max_M"].GetDouble();
    param.MIN_TRANSVERSE_OVERLOAD =  initial_data["rocket_min_Nx"].GetDouble();

    for (auto& v : initial_data["rocket_points"].GetArray())
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
}

void zur::firstStep()
{
    status = ZurStatus::is_fly;
    write_to_csv(true);
}

void zur::step(double time)
{
    GeocentricCoodinates GC_target;
    Vector3D crd_target;
    double vel_target;
    if (!recieve_msg_pu.empty())
    {
        crd_target = recieve_msg_pu.front().message.crd_target;
        vel_target = recieve_msg_pu.front().message.vel_target;
        recieve_msg_pu.pop_front();
    }

    double dt;
    if (data.nPoints != 0)
    {
        dt = time - data.times.back();
    }
    else
        dt = time;

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

        TrajectoryPoint target_pos(GC_target, 1.1*vel_target);
        points_rocket[1] = target_pos;

        calculate(dt, points_rocket);
    }

    ZurMSG msg;
    GeocentricCoodinates GC(data.xPos.back(), data.yPos.back(), data.zPos.back());
    Vector3D crd = GeoToPBU(GeodezicToGeoCentric(GD_Msc), GC);
    msg.crd_zur = {crd.x, crd.y, crd.z};
    msg.vels_zur = {data.xVel.back(), data.yVel.back(), data.zVel.back()};
    msg.status = status;

    write_to_csv();

    send<ZurMSG>(data.times.back(), msg);
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

void AirTarget::set_status(TargetStatus trg)
{
    status = trg;
}

void zur::pursuit(double dt)
{
    double rocket_vel = start_point.initialVel;
    GeocentricCoodinates start_rocket(start_point.initialPoint.x, start_point.initialPoint.y, start_point.initialPoint.z);

    std::vector<TrajectoryPoint> points_rocket(2);

    bool first_time = true;

    std::vector<double> cur_vec_vel(3);
    std::vector<double> AccelsLast_(3);
    double NormLast_ = 0;
    double TransLast_ = 0;
    double HorizLast_  = 0;
    double BankLast_ = 0;
    double WayLast_ = 0;

    int i = 0;
    double time_detection = 0;

    TrajectoryPoint target_pos(GC_, rocket_vel);
    points_rocket[1] = target_pos;

        /*if (first_time)
        {
            time_detection = data_target.times[i];
            toss_rocket(point_start_rocket, data_rocket);

            points_rocket[0].initialPoint.x = data_rocket.xPos.back();
            points_rocket[0].initialPoint.y = data_rocket.yPos.back();
            points_rocket[0].initialPoint.z = data_rocket.zPos.back();
            points_rocket[0].initialVel = sqrt(data_rocket.xVel.back()*data_rocket.xVel.back() + data_rocket.yVel.back()*data_rocket.yVel.back() + data_rocket.zVel.back()*data_rocket.zVel.back());

            double vel_ = sqrt(data_rocket.xVel.back()*data_rocket.xVel.back() + data_rocket.yVel.back()*data_rocket.yVel.back() + data_rocket.zVel.back()*data_rocket.zVel.back());
            cur_vec_vel = {data_rocket.xVel.back()/vel_, data_rocket.yVel.back()/vel_, data_rocket.zVel.back()/vel_};
            AccelsLast_ = {data_rocket.xAcc.back(), data_rocket.yAcc.back(), data_rocket.zAcc.back()};
            NormLast_ = data_rocket.normalOverload.back();
            TransLast_ = data_rocket.transverseOverload.back();
            HorizLast_ = data_rocket.angle_horizontal_plane.back();
            BankLast_ = data_rocket.bankAngle.back();
            WayLast_ = data_rocket.wayAngle.back();

            //calculate(points_rocket, data_rocket, 4, cur_vec_vel, AccelsLast_, NormLast_, TransLast_, HorizLast_, BankLast_, WayLast_);
            first_time = false;
        }*/

    points_rocket[0].initialPoint.x = data.xPos.back();
    points_rocket[0].initialPoint.y = data.yPos.back();
    points_rocket[0].initialPoint.z = data.zPos.back();
    points_rocket[0].initialVel = sqrt(data.xVel.back()*data.xVel.back() + data.yVel.back()*data.yVel.back() + data.zVel.back()*data.zVel.back());

    //calculate(points_rocket, data_rocket, 9, cur_vec_vel, AccelsLast_, NormLast_, TransLast_, HorizLast_, BankLast_, WayLast_);

    GeocentricCoodinates GC_r(data.xPos.back(), data.yPos.back(), data.zPos.back());
    GC_.x = data_target.xPos[i+10];
    GC_.y = data_target.yPos[i+10];
    GC_.z = data_target.zPos[i+10];

    //std::cout << (GC_ - GC_r).length() << "\n";
    if ((GC_ - GC_r).length() < 200)
    {
        data_target.resize(i+11);
        break;
    }

    std::cout << i << " " << data_target.times[i] << " " << data_rocket.times.back() << "\n";

    i += 10;

    for (int i = 0; i < data_rocket.nPoints; i++)
    {
        data_rocket.times[i] += time_detection;
    }
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

    data.times.push_back(data.nPoints*dt);

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

    if (GD_tmp.altitude == 50)
        is_tossed = true;
}
