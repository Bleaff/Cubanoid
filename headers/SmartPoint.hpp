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
    CartesianPoint<T>& operator=(const CartesianPoint<T>& other) { x = other.x; y = other.y; z = other.z; return *this; }
    CartesianPoint<T> operator+(const CartesianPoint<T>& other) const { return CartesianPoint<T>(x + other.x, y + other.y, z + other.z); }
    CartesianPoint<T> operator-(const CartesianPoint<T>& other) const { return CartesianPoint<T>(x - other.x, y - other.y, z - other.z); }
    CartesianPoint<T> operator*(const CartesianPoint<T>& other) const { return CartesianPoint<T>(x * other.x, y * other.y, z * other.z); }
    ostream operator<<(ostream& os) const { return os << x << " " << y << " " << z; }
    
    x = r*sin(alpha)*sin(teta);
    y = r * cos(alpha)*sin(teta);
    z = r*cos(teta);
    PolarPoint<T> toPolar(){PolarPoint<T>(std::sqrt(x^2 + y^2 + z^2), std::atan2(y, x), std::atan2(std::sqrt(x^2 + y^2), z));};
    
public:
    T x, y, z;
};

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
    ostream operator<<(ostream& os) const { return os << r << " " << alpha << " " << teta; }
    CartesianPoint<T> toCartesian(){return CartesianPoint<T>(r*sin(alpha)*sin(teta), r*cos(alpha)*sin(teta), r*cos(teta));};
public:
    T r, alpha, teta;
};



template<typename T> 
class SmartPoint
{
public:
    //constructors/destructors
    mutable std::mutex mtx;
    SmartPoint(CartesianPoint<T> c): c(c){p = c.toPolar();}
    SmartPoint(PolarPoint<T> p): p(p){c = p.toCartesian();}
    SmartPoint(const SmartPoint<T> other): p(other.p), c(other.c){}
    ~SmartPoint(){}
    //operators
    bool operator==(const SmartPoint<T>& other) const { std::lock_guard<std::mutex> lock(mtx);  return p == other.p && c == other.c; }
    SmartPoint<T>& operator=(const SmartPoint<T>& other) {std::lock_guard<std::mutex> lock(mtx); p = other.p; c = other.c; return *this; }
    SmartPoint<T> operator+(const SmartPoint<T>& other) const {std::lock_guard<std::mutex> lock(mtx); return SmartPoint<T>(p + other.p); }
    SmartPoint<T> operator-(const SmartPoint<T>& other) const {std::lock_guard<std::mutex> lock(mtx); return SmartPoint<T>(p - other.p); }
    SmartPoint<T> operator*(const SmartPoint<T>& other) const {std::lock_guard<std::mutex> lock(mtx); return SmartPoint<T>(p * other.p); }
    ostream operator<<(ostream& os) const {std::lock_guard<std::mutex> lock(mtx); return os << p << " " << c; }
    // operations
    SmartPoint<T> rotate(T alpha, T teta){std::lock_guard<std::mutex> lock(mtx); SmartPoint<T> rotatedPoint {this.p + PolarPoint<T>(0, alpha, teta)}; this = rotatedPoint; return rotatedPoint;};
    SmartPoint<T> move(T x, T y, T z){std::lock_guard<std::mutex> lock(mtx); SmartPoint<T> movedPoint {this.c + CartesianPoint<T>(x, y, z)}; this = movedPoint; return movedPoint;};
    CartesianPoint<T> getCartesianPoint()const{return c;};
    PolarPoint<T> getPolarPoint()const{return p;};
private:
    PolarPoint<T> p;
    CartesianPoint<T> c;

};


