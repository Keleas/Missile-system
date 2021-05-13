#ifndef COORDINATES_H
#define COORDINATES_H

#include <utility>
#include <vector>
#include <math.h>
//#include <qdebug.h>
#include <iostream>
#include <iomanip>

#ifdef _WIN32
#define M_PI 3.14159265358979323846
#define M_PI_2 1.57079632679489661923
#endif

constexpr double EARTH_RADIUS = 6364000;
constexpr double DEGREES_TO_RADIANS = M_PI / 180;
constexpr double RADIANS_TO_DEGREES = 180 / M_PI;

inline int Sign(double val)
{
    int res = 1;

    if (val == 0)
        res = 0;
    else if (val < 0)
        res =  -1;

    return res;
}

struct EarthEllipsoid
{
    EarthEllipsoid(double fVal = 1 / 298.257223563, double aVal = 6378137.0)
        : f(fVal), a(aVal)
    {
        b = a - a * f;
        e = sqrt(a*a - b*b) / a;
    }

    double f;
    double a;
    double b;
    double e;
};

struct GeodezicCoodinates
{
    GeodezicCoodinates(){}
    GeodezicCoodinates(double latit, double longit, double altit)
        : latitude(latit), longitude(longit), altitude(altit){}
    GeodezicCoodinates(double latit, double longit, double altit, double rad)
        : latitude(latit), longitude(longit), altitude(altit), R(rad){}

    GeodezicCoodinates toRadians(){ return {latitude*DEGREES_TO_RADIANS,longitude*DEGREES_TO_RADIANS,altitude, R}; }
    GeodezicCoodinates toDegrees(){ return {latitude*RADIANS_TO_DEGREES,longitude*RADIANS_TO_DEGREES,altitude, R};}
    double latitude;
    double longitude;
    double altitude;
    double R;
};

struct  GeocentricCoodinates
{
    GeocentricCoodinates(){}
    GeocentricCoodinates(double xVal, double yVal, double zVal)
        : x(xVal), y(yVal), z(zVal){}

    double x;
    double y;
    double z;

    double length(){ return sqrt(x*x + y*y +z*z); }

    double lengthSquared(){ return x*x + y*y +z*z; }

    GeocentricCoodinates normalized()
    {
        GeocentricCoodinates res;
        double len = length();
        res.x = x/len;
        res.y = y/len;
        res.z = z/len;
        return res;
    }
    inline friend GeocentricCoodinates operator*(GeocentricCoodinates const& r, double const& a);
    inline friend GeocentricCoodinates operator*(double const& a,GeocentricCoodinates const& r);
    inline friend GeocentricCoodinates operator/(GeocentricCoodinates const& r, double const& a);
    inline friend GeocentricCoodinates operator+(GeocentricCoodinates const& a, GeocentricCoodinates const& b);
    inline friend GeocentricCoodinates operator-(GeocentricCoodinates const& a, GeocentricCoodinates const& b);
};


inline GeocentricCoodinates GeodezicToGeoCentric(GeodezicCoodinates latLongAlt)
{
    double sinB = sin(DEGREES_TO_RADIANS * latLongAlt.latitude);
    double cosB = cos(DEGREES_TO_RADIANS * latLongAlt.latitude);
    double sinL = sin(DEGREES_TO_RADIANS * latLongAlt.longitude);
    double cosL = cos(DEGREES_TO_RADIANS * latLongAlt.longitude);

    double H = latLongAlt.altitude;

    EarthEllipsoid ellipsoid;
    double N = ellipsoid.a / sqrt(1 - pow(ellipsoid.e, 2) * pow(sinB, 2));

    double x = (N + H) * cosB * cosL;
    double y = (N + H) * cosB * sinL;
    double z = (N * (1 - pow(ellipsoid.e, 2)) + H) * sinB;

    return GeocentricCoodinates(x, y, z);
}


inline GeodezicCoodinates GeocentricToGeodezic(GeocentricCoodinates xyz)
{
    double x = xyz.x;
    double y = xyz.y;
    double z = xyz.z;

    EarthEllipsoid ellipsoid;
    double f = ellipsoid.f;
    double a = ellipsoid.a;

    f = 1 / f;
    double k0 = (f - 1) / f;
    double k1 =a * (2 * f - 1) / (f * (f - 1));
    double k2 = k0 * k1;

    double latitude;
    double longitude;
    double altitude;

    double R = sqrt(pow(x, 2) + pow(y, 2));

    if ( R == 0 ) {
        longitude = 0;
        latitude = (M_PI / 2) * Sign(z);
    }
    else {
        if ( y != 0 )
            longitude = 2 * atan(y / (x + R)) + M_PI * (1 - Sign(y));
        else
            if ( x >= 0 )
                longitude = 0;
            else
                if ( x < 0 )
                    longitude = M_PI;

        double U = atan(((k1 / sqrt(pow(z, 2) + pow(k0 * R, 2))) + 1) * k0 * z / R);
        double sinU = sin(U);
        double cosU = cos(U);

        latitude = atan((z + k1 * pow(sinU, 3)) / (R - k2 * pow(cosU, 3)));
    }

    double cosB = cos(latitude);
    double sinB = sin(latitude);

    altitude = R * cosB + z * sinB - a * sqrt(1 - k2 * pow(sinB, 2) / a);

    if(longitude > M_PI)
        longitude = -2*M_PI+longitude;

    GeodezicCoodinates GD(latitude * RADIANS_TO_DEGREES, longitude * RADIANS_TO_DEGREES, altitude);
    GD.R = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));

    return GD;
}

inline GeodezicCoodinates GeocentricToGeodezicSphere(GeocentricCoodinates xyz)
{
    double longitude = atan(xyz.y / xyz.x);
    double latitude = atan(xyz.z / sqrt(pow(xyz.x, 2) + pow(xyz.y, 2)));
    double R = sqrt(pow(xyz.x, 2) + pow(xyz.y, 2) + pow(xyz.z, 2));
    double altitude = R - EARTH_RADIUS;

    if (xyz.y < 0)
    {
        longitude = - acos(xyz.x / sqrt(pow(xyz.x, 2) + pow(xyz.y, 2)));
    }
    else if ( xyz.y > 0  )
    {
        longitude = acos(xyz.x / sqrt(pow(xyz.x, 2) + pow(xyz.y, 2)));
    }
    latitude = asin(xyz.z / R);

    GeodezicCoodinates GD(latitude * RADIANS_TO_DEGREES, longitude * RADIANS_TO_DEGREES, altitude);
    GD.R = R;

    return GD;
}

inline double dotProduct(GeocentricCoodinates a, GeocentricCoodinates b){
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

GeocentricCoodinates operator+(const GeocentricCoodinates &a, const GeocentricCoodinates &b)
{
    GeocentricCoodinates res;
    res.x = a.x + b.x;
    res.y = a.y + b.y;
    res.z = a.z + b.z;
    return res;
}

GeocentricCoodinates operator-(const GeocentricCoodinates &a, const GeocentricCoodinates &b)
{
    GeocentricCoodinates res;
    res.x = a.x - b.x;
    res.y = a.y - b.y;
    res.z = a.z - b.z;
    return res;
}

GeocentricCoodinates operator/(const GeocentricCoodinates &r, const double &a)
{
    GeocentricCoodinates res;
    res.x = r.z/a;
    res.y = r.y/a;
    res.z = r.z/a;
    return res;
}

GeocentricCoodinates operator*(const GeocentricCoodinates &r, const double &a)
{
    GeocentricCoodinates res;
    res.x = r.x*a;
    res.y = r.y*a;
    res.z = r.z*a;
    return res;
}

GeocentricCoodinates operator*(double const& a,GeocentricCoodinates const& r)
{
    GeocentricCoodinates res;
    res.x = r.x*a;
    res.y = r.y*a;
    res.z = r.z*a;
    return res;
}

#endif // COORDINATES_H
