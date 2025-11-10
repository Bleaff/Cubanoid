#pragma once
#include <mutex>
#include <math.h>
template<typename T>
class CartesianPoint
{
public:
    // constuctors/destructors
    CartesianPoint(T x, T y, T z): x(x), y(y), z(z){}
    CartesianPoint(const CartesianPoint<T>& other): x(other.x), y(other.y), z(other.z){}
    ~CartesianPoint(){}
    //operators
    bool operator==(const CartesianPoint<T>& other) const { return x == other.x && y == other.y && z == other.z; }
    CartesianPoint<T> operator+(const CartesianPoint<T>& other) const { return CartesianPoint<T>(x + other.x, y + other.y, z + other.z); }
    CartesianPoint<T> operator-(const CartesianPoint<T>& other) const { return CartesianPoint<T>(x - other.x, y - other.y, z - other.z); }
    CartesianPoint<T> operator*(const CartesianPoint<T>& other) const { return CartesianPoint<T>(x * other.x, y * other.y, z * other.z); }
    ostream operator<<(ostream& os) const { return os << x << " " << y << " " << z; }
    
    x = r*sin(alpha)*sin(teta);
    y = r * cos(alpha)*sin(teta);
    z = r*cos(teta);
    PolarPoint<T> toPolar(){T r = std::sqrt(x^2 + y^2 + z^2); };
    
public:
    T x, y, z;
};

template <typename T>
class PolarPoint
{
public:
    PolarPoint(T r, T alpha, T teta): r(r), alpha(alpha), teta(teta){}
    ~PolarPoint(){}
    CartesianPoint<T> toCartesian();
public:
    T r, alpha, teta;
};



template<typename T> 
class SmartPoint
{
    mutable std::mutex mtx;

public:
    SmartPoint(CartesianPoint<T> c): c(c){

    }
    SmartPoint(PolarPoint<T> p): p(p){}

private:
    PolarPoint<T> p;
    CartesianPoint<T> c;

    SmartPoint& operator=(const SmartPoint& p);
};


