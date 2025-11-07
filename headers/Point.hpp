#pragma once


#include <mutex>

template<typename T> 
class SmartPoint
{
    std::mutex mtx;
public:
    SmartPoint(x, y, z): x(x), y(y), z(z){}
private:
    T x, y, z;
    float r, alpha, teta;
    SmartPoint& operator=(const SmartPoint& p);
};


