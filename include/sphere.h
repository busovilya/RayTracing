#pragma once

#include "geometry.h"
#include "ray.h"

struct Sphere
{
    Vector3f center;
    float radius;
    Vector3f color;

    bool intersect(const Ray& ray, float& intersect_dist);
};