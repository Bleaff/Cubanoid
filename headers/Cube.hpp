#pragma once
#include "Point.hpp"
#include <vector>


class Cubanoid{

public:

private:
    std::vector<Point<float>> points = {
    {-1,-1,-1},{ 1,-1,-1},{ 1, 1,-1},{-1, 1,-1},
    {-1,-1, 1},{ 1,-1, 1},{ 1, 1, 1},{-1, 1, 1}
    };

};