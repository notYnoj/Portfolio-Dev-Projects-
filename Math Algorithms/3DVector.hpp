#ifndef VEC3D_HPP
#define VEC3D_HPP

#include <array>
#include <iostream>

struct Vec3D {
    std::array<double, 3> vec;

    
    Vec3D(const double& _x, const double& _y, const double& _z);
    Vec3D();

    
    const double& x() const;
    const double& y() const;
    const double& z() const;
    double& x();
    double& y();
    double& z();

    
    Vec3D operator+(const Vec3D& Addend) const;
    Vec3D& operator+=(const Vec3D& Addend);
    Vec3D operator-(const Vec3D& Subtrahend) const;
    Vec3D& operator-=(const Vec3D& Subtrahend);
    Vec3D operator*(const double& Factor) const;
    Vec3D& operator*=(const double& Factor);
    double operator*(const Vec3D& factor) const; // dot product
    bool operator==(const Vec3D& other) const;
    bool operator!=(const Vec3D& other) const;

    
    friend Vec3D operator*(const double& scalar, const Vec3D& vector);

    // Methods
    double magnitude() const;
    Vec3D normal() const;
    Vec3D cross(const Vec3D& Factor) const;
    Vec3D proj(const Vec3D& B) const;
    Vec3D reflect(const Vec3D& NormalVec) const;
    double angleBetween(const Vec3D& B) const;
    void print() const;
};

#endif
