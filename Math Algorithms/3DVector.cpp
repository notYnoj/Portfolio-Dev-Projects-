#include <iostream>
#include <vector>
#include <stdexcept>
#include <utility>
#include <float.h>
#include <cmath>

struct Vec3D{
    double x, y, z;
    std::array<double, 3> vec;
    Vec3D(const double& _x, const double& _y, const double& _z) : x(_x), y(_y), z(_z), vec{_x, _y, _z} {}
    Vec3D() : x(0.0), y(0.0), z(0.0), vec{0.0, 0.0, 0.0} {}
    /*
    Intended Functions:
    Add Done
    Subtract Done
    Scalar Multiplication Done
    Dot Product Done
    Cross Product Done
    Magnitutde Done=
    Normalize Done
    Projection Done
    Reflection Done
    Angle Between Vectors Done
    */

    Vec3D operator+(const Vec3D& Addend) const{
        Vec3D temp(0,0,0);
        temp.vec[0] = vec[0] + Addend.vec[0];
        temp.vec[1] = vec[1] + Addend.vec[1];
        temp.vec[2] = vec[2] + Addend.vec[2];
        return temp;
    }

    Vec3D& operator+=(const Vec3D& Addend){
        vec[0] += Addend.vec[0];
        vec[1] += Addend.vec[1];
        vec[2] += Addend.vec[2];
        return *this;
    }
    Vec3D operator*(const double& Factor) const{
        Vec3D temp = *this;
        temp.vec[0] *= Factor;
        temp.vec[1] *= Factor;
        temp.vec[2] *= Factor;
        return temp;
    }
    friend Vec3D operator*(const double& scalar, const Vec3D& vector){
        return vector * scalar;
    }

    
    Vec3D& operator*=(const double& Factor){
        vec[0] *= Factor;
        vec[1] *= Factor;
        vec[2] *= Factor;
        return *this;
    }

    Vec3D operator-(const Vec3D& Subtrahend) const{
        Vec3D temp = *this;
        temp.vec[0] -= Subtrahend.vec[0];
        temp.vec[1] -= Subtrahend.vec[1];
        temp.vec[2] -= Subtrahend.vec[2];
        return temp;
    }

    Vec3D& operator-=(const Vec3D& Subtrahend){
        vec[0] -= Subtrahend.vec[0];
        vec[1] -= Subtrahend.vec[1];
        vec[2] -= Subtrahend.vec[2];
        return *this;
    }

    double operator*(const Vec3D& factor) const{
        return ((vec[0] * factor.vec[0])  + (vec[1] * factor.vec[1]) + (vec[2] * factor.vec[2]));
    }

    double magnitude() const{
        return (sqrt((vec[0] * vec[0]) + (vec[1] * vec[1]) + (vec[2] * vec[2])));
    }

    Vec3D normal() const{
        Vec3D temp(vec[0], vec[1], vec[2]);
        double scalar = 1.0/magnitude();
        temp *= scalar;
        return temp;
    }

    Vec3D cross(const Vec3D& Factor) const{
        Vec3D ans;
        ans.vec[0] = vec[1] * Factor.vec[2] - vec[2] * Factor.vec[1]; 
        ans.vec[1] = vec[2] * Factor.vec[0] - vec[0] * Factor.vec[2];
        ans.vec[2] = vec[0] * Factor.vec[1] - vec[1] * Factor.vec[0];
        return ans;
    }

    Vec3D proj(const Vec3D& B) const{
        //A proj onto B = a dot b / |b|^2  * b
        return ((*this * B) / (B.magnitude() * B.magnitude()) * B);
    }
    //reflect current vector given a N normal vector perpendicular to a surface
    Vec3D reflect(const Vec3D& NormalVec) const{
        //R = V - 2* projn(V)
        return (*this -  (2 * proj(NormalVec)));
    }

    double angleBetween(const Vec3D& B) const{
        //angle between A and B = arccos(a dot b / (|a| * |b|))
        return (acos((*this * B) / (magnitude() * B.magnitude())));
    }

};