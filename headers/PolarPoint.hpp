#pragma once

#include "SmartPoint.hpp"
#include <math.h>

template <typename T>
class PolarPoint
{
 /*
    Polar point - r, alpha, teta
    alpha, teta - angles in degree's
 */
public:
    //constructors/destructors
    PolarPoint(T r, T alpha, T teta): r(r), alpha(alpha), teta(teta){}
    PolarPoint(const PolarPoint<T>& other): r(other.r), alpha(other.alpha), teta(other.teta){}
    ~PolarPoint(){}
    //operators
    bool operator==(const PolarPoint<T>& other) const { return r == other.r && alpha == other.alpha && teta == other.teta; }
    PolarPoint<T>& operator=(const PolarPoint<T>& other) { r = other.r; alpha = other.alpha; teta = other.teta; return *this; }
    PolarPoint<T> operator+(const PolarPoint<T>& other) const { return PolarPoint<T>(r + other.r, alpha + other.alpha, teta + other.teta); }
    PolarPoint<T> operator-(const PolarPoint<T>& other) const { return PolarPoint<T>(r - other.r, alpha - other.alpha, teta - other.teta); }
    PolarPoint<T> operator*(const PolarPoint<T>& other) const { return PolarPoint<T>(r * other.r, alpha * other.alpha, teta * other.teta); }
    std::ostream operator<<(std::ostream& os) const { return os << r << " " << alpha << " " << teta; }
    CartesianPoint<T> toCartesian(){return CartesianPoint<T>(r*sin(alpha)*sin(teta), r*cos(alpha)*sin(teta), r*cos(teta));};
public:
    T r, alpha, teta;
};