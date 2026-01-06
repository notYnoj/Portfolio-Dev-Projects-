#include "3DVector.hpp"
#include <cmath>
#include <stdexcept>

Vec3D::Vec3D(const double& _x, const double& _y, const double& _z) : vec{_x, _y, _z} {}
Vec3D::Vec3D() : vec{0.0, 0.0, 0.0} {}

const double& Vec3D::x() const { return vec[0]; }
const double& Vec3D::y() const { return vec[1]; }
const double& Vec3D::z() const { return vec[2]; }
double& Vec3D::x() { return vec[0]; }
double& Vec3D::y() { return vec[1]; }
double& Vec3D::z() { return vec[2]; }

Vec3D Vec3D::operator+(const Vec3D& Addend) const {
    return Vec3D(vec[0] + Addend.vec[0], vec[1] + Addend.vec[1], vec[2] + Addend.vec[2]);
}

Vec3D& Vec3D::operator+=(const Vec3D& Addend) {
    vec[0] += Addend.vec[0];
    vec[1] += Addend.vec[1];
    vec[2] += Addend.vec[2];
    return *this;
}

Vec3D Vec3D::operator-(const Vec3D& Subtrahend) const {
    return Vec3D(vec[0] - Subtrahend.vec[0], vec[1] - Subtrahend.vec[1], vec[2] - Subtrahend.vec[2]);
}

Vec3D& Vec3D::operator-=(const Vec3D& Subtrahend) {
    vec[0] -= Subtrahend.vec[0];
    vec[1] -= Subtrahend.vec[1];
    vec[2] -= Subtrahend.vec[2];
    return *this;
}

Vec3D Vec3D::operator*(const double& Factor) const {
    return Vec3D(vec[0] * Factor, vec[1] * Factor, vec[2] * Factor);
}

Vec3D& Vec3D::operator*=(const double& Factor) {
    vec[0] *= Factor;
    vec[1] *= Factor;
    vec[2] *= Factor;
    return *this;
}

double Vec3D::operator*(const Vec3D& factor) const {
    return vec[0] * factor.vec[0] + vec[1] * factor.vec[1] + vec[2] * factor.vec[2];
}

Vec3D operator*(const double& scalar, const Vec3D& vector) {
    return vector * scalar;
}

bool Vec3D::operator==(const Vec3D& other) const {
    return vec[0] == other.vec[0] && vec[1] == other.vec[1] && vec[2] == other.vec[2];
}

bool Vec3D::operator!=(const Vec3D& other) const {
    return !(*this == other);
}

double Vec3D::magnitude() const {
    return std::sqrt(vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2]);
}

Vec3D Vec3D::normal() const {
    double mag = magnitude();
    if (mag < 1e-10) throw std::runtime_error("Cannot normalize zero vector (Division by 0)");
    return (*this) * (1.0 / mag);
}

Vec3D Vec3D::cross(const Vec3D& Factor) const {
    return Vec3D(
        vec[1]*Factor.vec[2] - vec[2]*Factor.vec[1],
        vec[2]*Factor.vec[0] - vec[0]*Factor.vec[2],
        vec[0]*Factor.vec[1] - vec[1]*Factor.vec[0]
    );
}

Vec3D Vec3D::proj(const Vec3D& B) const {
    double bSquared = B.magnitude() * B.magnitude();
    if (bSquared < 1e-10) throw std::runtime_error("Cannot proj onto zero vector (Division by 0)");
    return ((*this * B) / bSquared) * B;
}

Vec3D Vec3D::reflect(const Vec3D& NormalVec) const {
    return *this - 2 * proj(NormalVec);
}

double Vec3D::angleBetween(const Vec3D& B) const {
    double mags = magnitude() * B.magnitude();
    if (mags < 1e-20) throw std::runtime_error("Cannot compute angle with zero vector");
    return std::acos((*this * B) / mags);
}

void Vec3D::print() const {
    std::cout << "(" << vec[0] << ", " << vec[1] << ", " << vec[2] << ")" << std::endl;
}
