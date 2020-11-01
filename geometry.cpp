#include "geometry.h"
#include <math.h>

Vector3f::Vector3f() : x(0), y(0), z(0)
{ }

Vector3f::Vector3f(float x, float y, float z) : x(x), y(y), z(z)
{ }

Vector3f Vector3f::operator+(const Vector3f& other) const
{
    return Vector3f { x + other.x, y + other.y, z + other.z };
}

Vector3f Vector3f::operator+(float scalar) const
{
    return Vector3f { x + scalar, y + scalar, z + scalar };
}

Vector3f Vector3f::operator-(const Vector3f& other) const
{
    return Vector3f { x - other.x, y - other.y, z - other.z };
}

Vector3f Vector3f::operator*(float scalar) const
{
    return Vector3f { x * scalar, y * scalar, z * scalar };
}

float Vector3f::operator*(const Vector3f& other) const
{
    return x * other.x + y * other.y + z * other.z;
}

Vector3f Vector3f::unit() const
{
    float len = this->length();
    return Vector3f{ this->x / len, this->y / len, this->z / len };
}

float Vector3f::length() const
{
    return sqrt(x * x + y * y + z * z);
}