#pragma once

#include "geometry.h"
#include "ray.h"

class Camera
{
public:
    Camera(Vector3f, float, float, Vector3f);
    Ray getRay(float, float);
private:
    float viewport_width, viewport_height;
    Vector3f origin, lower_left_corner;
};