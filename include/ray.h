#pragma once

#include "geometry.h"

class Ray
{
public:
    Vector3f origin, direction;
    Ray(Vector3f, Vector3f);
};