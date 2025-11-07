#pragma once

template<typename T> 
class Point
{
public:
    Point(x, y, z): x(x), y(y), z(z){}
private:
    T x, y, z;
    float r, alpha, teta;
    Poinit& operator=(const Point& p);
};


