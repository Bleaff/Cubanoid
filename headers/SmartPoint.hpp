#pragma once


#include <mutex>

template<typename T, typename PT> 
class SmartPoint
{
    mutable std::mutex mtx;
public:
    SmartPoint(T x,T y, T z): x(x), y(y), z(z){}
private:
    T x, y, z;
    float r, alpha, teta;
    SmartPoint& operator=(const SmartPoint& p);
};


