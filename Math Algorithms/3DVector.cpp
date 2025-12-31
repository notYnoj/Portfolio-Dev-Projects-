#include <iostream>
#include <vector>
#include <stdexcept>
#include <utility>
#include <float.h>
#include <cmath>

struct Vec3D{
    long long x,y,z;
    std::array<long long, 3> vec;
    Vec3D(const long long& _x, const long long& _y, const long long& _z) : x(_x), y(_y), z(_z) {

    }

};