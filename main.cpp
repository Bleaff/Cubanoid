#include "headers/SmartPoint.hpp"

int main(){
    SmartPoint<int> p1(CartesianPoint<int>(1, 2, 3));
    SmartPoint<int> p2(p1.rotate(30, 0));
    SmartPoint<int> p3(PolarPoint<int>(1, 30, 0));
}