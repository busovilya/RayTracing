#pragma once

struct Vector3f
{
    float x, y, z;

    Vector3f();
    Vector3f(float x, float y, float z);
    Vector3f operator+(const Vector3f& other) const;
    Vector3f operator+(float scalar) const;
    Vector3f operator-(const Vector3f& other) const;
    Vector3f operator*(float scalar) const;
    float operator*(const Vector3f& other) const;
    Vector3f unit() const;
    float length() const;
};