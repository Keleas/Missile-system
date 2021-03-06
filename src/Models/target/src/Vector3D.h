#ifndef VECTOR3D_H
#define VECTOR3D_H

#include "Coordinates.h"
#include <array>

class Vector3D
{
public:
    Vector3D() = default;
    Vector3D(double _x, double _y, double _z);
    Vector3D(GeocentricCoodinates coord);
    Vector3D(const std::array<double, 3> &coord);

//    Vector3D& operator=(const std::array<double,3> &coords);


    double length() const;
    double sqrlength() const;

    Vector3D normalized() const;
    Vector3D& normalize();

    void operator()(double _x, double _y, double _z);

    Vector3D& operator+=(Vector3D const& that);
    Vector3D& operator-=(Vector3D const& that);
    template <typename T>
    Vector3D& operator*=(T num);
    template <typename T>
    Vector3D& operator/=(T num);

    bool operator==(Vector3D const& that);
    bool operator!=(Vector3D const& that);

    Vector3D operator-() const;

    Vector3D& rotate(Vector3D const& axis, double angle);
    Vector3D rotated(Vector3D const& axis, double angle);

    double x{0},y{0},z{0};
private:
};

inline Vector3D::Vector3D(double _x, double _y, double _z) : x{_x}, y{_y}, z{_z} {}

inline Vector3D::Vector3D(GeocentricCoodinates coord) : x{coord.x}, y{coord.y}, z{coord.z} {}

inline Vector3D::Vector3D(const std::array<double, 3> &coord)
{
    x = coord.at(0);
    y = coord.at(1);
    z = coord.at(2);
}

//Vector3D &Vector3D::operator=(const std::array<double, 3> &coords)
//{
//    x = coords[0];
//    y = coords[1];
//    z = coords[2];
//    return *this;
//}

inline double Vector3D::length() const{
    return sqrt(x*x + y*y + z*z);
}

inline double Vector3D::sqrlength() const{
    return x*x + y*y + z*z;
}

inline void Vector3D::operator ()(double _x, double _y, double _z)
{
    x = _x;
    y = _y;
    z = _z;
}

inline Vector3D& Vector3D::operator+=(Vector3D const& that){
    x += that.x;
    y += that.y;
    z += that.z;
    return*this;
}
inline Vector3D& Vector3D::operator-=(Vector3D const& that){
    x -= that.x;
    y -= that.y;
    z -= that.z;
    return*this;
}

inline bool Vector3D::operator==(const Vector3D &that){
    return x == that.x && y == that.y && z == that.y;
}

inline bool Vector3D::operator!=(const Vector3D &that){
    return x != that.x || y != that.y || z != that.y;
}

inline Vector3D Vector3D::operator-() const
{
    return {-x,-y,-z};
}

inline Vector3D &Vector3D::rotate(const Vector3D &axis, double angle){
    double cosA = cos(angle);
    double sinA = sin(angle);
    Vector3D res;
    res.x = (cosA + (1-cosA)*axis.x*axis.x)*x + ((1-cosA)*axis.x*axis.y-sinA*axis.z)*y +
            ((1-cosA)*axis.x*axis.z + sinA*axis.y)*z;
    res.y = ((1-cosA)*axis.y*axis.x + sinA*axis.z)*x + (cosA + (1-cosA)*axis.y*axis.y)*y +
            ((1-cosA)*axis.y*axis.z - sinA*axis.x)*z;
    res.z = ((1-cosA)*axis.z*axis.x - sinA*axis.y)*x + ((1-cosA)*axis.z*axis.y + sinA*axis.x)*y +
            (cosA + (1-cosA)*axis.z*axis.z)*z;
    *this = res;
    return *this;
}

inline Vector3D Vector3D::rotated(const Vector3D &axis, double angle){
    Vector3D res = *this;
    return res.rotate(axis,angle);
}

template <typename T>
inline Vector3D& Vector3D::operator*=(T num){
    x *= num;
    y *= num;
    z *= num;
    return*this;
}

template <typename T>
inline Vector3D& Vector3D::operator/=(T num){
    x /= num;
    y /= num;
    z /= num;
    return *this;
}

inline Vector3D operator+(Vector3D const& a, Vector3D const& b){
    return Vector3D(a.x+b.x,a.y+b.y,a.z+b.z);
}

inline Vector3D operator-(Vector3D const& a, Vector3D const& b){
    return Vector3D(a.x-b.x,a.y-b.y,a.z-b.z);
}

template <typename T>
inline Vector3D operator*(Vector3D const& vec, T num){
    return Vector3D(vec.x*num,vec.y*num,vec.z*num);
}

template <typename T>
inline Vector3D operator*(T num, Vector3D const& vec){
    return Vector3D(vec.x*num,vec.y*num,vec.z*num);
}

template <typename T>
inline Vector3D operator/(Vector3D const& vec, T num){
    return Vector3D(vec.x/num,vec.y/num,vec.z/num);
}

inline double dot(Vector3D const& a, Vector3D const& b){
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

inline Vector3D Vector3D::normalized() const{
    return *this*(1./length());
}

inline Vector3D& Vector3D::normalize(){
    return (*this *= 1./length());
}

inline Vector3D mul(Vector3D const& a, Vector3D const& b){
    return {a.y*b.z-a.z*b.y,-a.x*b.z+a.z*b.x,a.x*b.y-a.y*b.x};
}

inline double angeleBetween(Vector3D const& a, Vector3D const& b){
    double tmp = dot(a.normalized(),b.normalized());
    double res = acos(tmp);
    return res;
}

inline Vector3D GeoToPBU(GeocentricCoodinates GC0, GeocentricCoodinates GC)
{
    EarthEllipsoid ellipsoid;
    /*
    ellipsoid.a = 100000000000000000;
    ellipsoid.b = ellipsoid.a;
    ellipsoid.e = sqrt(ellipsoid.a*ellipsoid.a - ellipsoid.b*ellipsoid.b) / ellipsoid.a;
    ellipsoid.f = (ellipsoid.a-ellipsoid.b) / ellipsoid.a;*/

    GeodezicCoodinates GD0 = GeocentricToGeodezic(GC0).toRadians();
    double sinB = sin(GD0.latitude);
    double N = ellipsoid.a / sqrt(1 - pow(ellipsoid.e, 2) * pow(sinB, 2));

    double z = GC.z + pow(ellipsoid.e, 2) * N * sinB;
    double x = GC.x * cos(GD0.longitude) + GC.y * sin(GD0.longitude);
    double y = -GC.x * sin(GD0.longitude) + GC.y * cos(GD0.longitude);

    double z1 = z;

    z = z1 * cos(M_PI_2 - GD0.latitude) + x * sin(M_PI_2 - GD0.latitude);
    x = -z1 * sin(M_PI_2 - GD0.latitude) + x * cos(M_PI_2 - GD0.latitude);
    z = z - (N+GD0.altitude);
    x = -x;
    return Vector3D(x, y, z);
}

inline GeocentricCoodinates PBUToGeo(GeocentricCoodinates GC0, Vector3D PBU)
{
    EarthEllipsoid ellipsoid;
    /*
    ellipsoid.a = 100000000000000000;
    ellipsoid.b = ellipsoid.a;
    ellipsoid.e = sqrt(ellipsoid.a*ellipsoid.a - ellipsoid.b*ellipsoid.b) / ellipsoid.a;
    ellipsoid.f = (ellipsoid.a-ellipsoid.b) / ellipsoid.a;*/

    GeodezicCoodinates GD0 = GeocentricToGeodezic(GC0).toRadians();
    double sinB = sin(GD0.latitude);
    double N = ellipsoid.a / sqrt(1 - pow(ellipsoid.e, 2) * pow(sinB, 2));

    double x = -PBU.x;
    double z = PBU.z + N + GD0.altitude;

    double z1 = z;
    z = z1 * cos(-M_PI_2 + GD0.latitude) + x * sin(-M_PI_2 + GD0.latitude);
    x = -z1 * sin(-M_PI_2 + GD0.latitude) + x * cos(-M_PI_2 + GD0.latitude);

    double x1 = x;
    x = x1 * cos(-GD0.longitude) + PBU.y * sin(-GD0.longitude);
    double y = -x1 * sin(-GD0.longitude) + PBU.y * cos(-GD0.longitude);

    z = z - pow(ellipsoid.e, 2) * N * sinB;

    return GeocentricCoodinates(x, y, z);

}

#endif // VECTOR3D_H
