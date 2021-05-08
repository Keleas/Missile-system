#include "airtarget.h"

AirTarget::AirTarget(std::string targetName_, AirTargetParams param_)
    : targetName(targetName_), param{param_} {}

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

void AirTarget::calculate(const std::vector<TrajectoryPoint>& control_points, TrajData &data, int num_iter,
                          std::vector<double> cur_vec_vel, std::vector<double> next_vec_vel_, std::vector<double> AccelsLast_,
                          double NormLast_, double TransLast_, double HorizLast_, double BankLast_, double WayLast_)
{
    std::vector<Vector3D> _points;
    std::vector<Vector3D> _vels;
    std::vector<Vector3D> _accels;
    std::vector<double> _normOV;
    std::vector<double> _transOV;
    std::vector<double> _bankAngle;
    std::vector<double> _horizontal_plane;
    std::vector<double> _wayAngle;

    Vector3D NuCur, NuCurDer;
    Vector3D NuDes, NuDesDer;
    Vector3D NuCurNext;
    Vector3D radiusVector;
    Vector3D NormalOverload, TransOverload, VelComp, AccelsComp;

    double k_nu = 0.6;
    double fi = 0;
    double dt = 0.1;

    bool first_time = true;

    for (unsigned int i = 0; i < control_points.size()-1; i++)
    {
        double speed = control_points[i].initialVel;
        int iter = 0;
        GeocentricCoodinates GC_1(control_points[i].initialPoint.x, control_points[i].initialPoint.y, control_points[i].initialPoint.z);
        GeocentricCoodinates GC_2(control_points[i+1].initialPoint.x, control_points[i+1].initialPoint.y, control_points[i+1].initialPoint.z);
        GeocentricCoodinates GC(control_points[i].initialPoint.x, control_points[i].initialPoint.y, control_points[i].initialPoint.z);
        GeodezicCoodinates GD = GeocentricToGeodezic(GC_1).toRadians();
        Vector3D LocalCoord_1 = GeoToLocal(GD, GC_1, GC_1);

        bool is_reached = false;
        while (!is_reached)
        {
            iter++;
            k_nu = 0.6;
            Vector3D LocalCoord_2 = GeoToLocal(GD, GC_2, GC);

            if (i == 0 && first_time && cur_vec_vel.empty())
            {
                radiusVector = LocalCoord_1;
                NormalOverload(0, 0, 0);
                TransOverload(0, 0, 0);

                NuCur = (LocalCoord_2 - LocalCoord_1);
                NuCur.normalize();

                NuCurNext(0, 0, 0);
                NuDesDer(0, 0, 0);
                NuCurDer(0, 0, 0);

                VelComp = NuCur*speed;
                AccelsComp(0, 0, 0);

                _vels.push_back(VelComp);
                _accels.push_back(AccelsComp);
                _normOV.push_back(0);
                _transOV.push_back(0);
                _horizontal_plane.push_back(0);
                _bankAngle.push_back(0);
                _wayAngle.push_back(0);
                _points.push_back(Vector3D(GC_1.x, GC_1.y, GC_1.z));
            }

            if (!cur_vec_vel.empty())
            {
                NuCur.x = cur_vec_vel[0];
                NuCur.y = cur_vec_vel[1];
                NuCur.z = cur_vec_vel[2];
                _points.push_back(Vector3D(GC_1.x, GC_1.y, GC_1.z));
                _vels.push_back(Vector3D(NuCur*speed));
                NuCur.x = next_vec_vel_[0];
                NuCur.y = next_vec_vel_[1];
                NuCur.z = next_vec_vel_[2];
                _accels.push_back(Vector3D(AccelsLast_[0], AccelsLast_[1], AccelsLast_[2]));
                _normOV.push_back(NormLast_);
                _transOV.push_back(TransLast_);
                _bankAngle.push_back(BankLast_);
                _horizontal_plane.push_back(HorizLast_);
                _wayAngle.push_back(WayLast_);
                first_time = false;
                cur_vec_vel.clear();
            }

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

            if (i == 0 && first_time)
            {
                NuCur = NuDes;
                first_time = false;
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

           ///std::cout << "NuCur " << NuCur.x << " " << NuCur.y << " " << NuCur.z << " " << "NuDes " << NuDes.x  << " " << NuDes.y << " " << NuDes.z << "\n";

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

            ///std::cout << "k cosfi fi " << k_nu << " " << cosFi << " " << fi << "\n";

            _normOV.push_back(NormalOverload.length());

            NuCurDer = (NormalOverload - OY + NuCur*NuCur.y) * (g/speed);

            ///std::cout << "NuCurDer " << NuCurDer.x << " " << NuCurDer.y << " " << NuCurDer.z << " NuDesDer " << NuDesDer.x << " " << NuDesDer.y << " " << NuDesDer.z << "\n";

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

            radiusVector(0, 0, 0);
            GD = GeocentricToGeodezic(GC).toRadians();

            double dist = (GC_2 - GC).length();

            std::cout << dist << "\n";

            if (dist <= 100)
            {
                is_reached = true;
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

            NuCurLast = {NuCur.x, NuCur.y, NuCur.z};
            NuCur = NuCurNext;

            if (((iter >= num_iter) && (num_iter > 0)))
                break;
        }
    }

    NuCurNextLast = {NuCur.x, NuCur.y, NuCur.z};
    AccelsLast = {_accels.back().x, _accels.back().y, _accels.back().z};
    NormLast = _normOV.back();
    TransLast = _transOV.back();
    HorizLast = _horizontal_plane.back();
    BankLast = _bankAngle.back();
    WayLast = _wayAngle.back();
    data.insert(0, _points, _vels, _accels, _bankAngle, _horizontal_plane, _wayAngle, _transOV, _normOV, dt);
}
