#pragma once
#include <mutex>
#include <math.h>
#include "PolarPoint.hpp"

template<typename T> 
class SmartPoint
{
    /*
    This 
SmartPoint
 class represents a point in 3D space that can be either in Cartesian or Polar coordinates. It has methods to perform operations on the point such as rotation, movement, and getting the coordinates.

Here's a summary of what each method does:

Constructors: Initialize the point in either Cartesian or Polar coordinates.
Destructor: Clean up any resources used by the point.
operator==
: Check if two points are equal.
operator=
: Assign one point to another.
operator+
, 
operator-
, 
operator*
: Perform addition, subtraction, and multiplication on two points.
operator<<
: Print the point's coordinates.
rotate
: Rotate the point around the z-axis by a given angle.
move
: Move the point by a given distance in the x, y, and z directions.
getCartesianPoint
: Get the Cartesian coordinates of the point.
getPolarPoint
: Get the Polar coordinates of the point.
The mutable std::mutex mtx; is used to protect access to the point's data in the 
operator==
, 
operator=
, 
operator+
, 
operator-
, 
operator*
, and 
operator<<
 methods.
    */
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
    std::ostream operator<<(std::ostream& os) const {std::lock_guard<std::mutex> lock(mtx); return os << p << " " << c; }
    // operations
    SmartPoint<T> rotate(T alpha, T teta){
        /*
        
        */
        std::lock_guard<std::mutex> lock(mtx); 
        SmartPoint<T> rotatedPoint {this.p + PolarPoint<T>(0, alpha, teta)}; 
        this = rotatedPoint; 
        return rotatedPoint;
    };
    SmartPoint<T> move(T x, T y, T z){std::lock_guard<std::mutex> lock(mtx); SmartPoint<T> movedPoint {this.c + CartesianPoint<T>(x, y, z)}; this = movedPoint; return movedPoint;};
    CartesianPoint<T> getCartesianPoint()const{return c;};
    PolarPoint<T> getPolarPoint()const{return p;};
private:
    PolarPoint<T> p;
    CartesianPoint<T> c;

};


