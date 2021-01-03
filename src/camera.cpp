#include "camera.h"

Camera::Camera(Vector3f origin, float viewport_width, float viewport_height, Vector3f lower_left_corner)
{
    this->origin = origin;
    this->viewport_width = viewport_width;
    this->viewport_height = viewport_height;
    this->lower_left_corner = lower_left_corner;
}

Ray Camera::getRay(float i, float j)
{
    Vector3f ray_direction{float(i) * viewport_width,
                           float(j) * viewport_height,
                           0};
    return Ray(origin, ray_direction + lower_left_corner);
}