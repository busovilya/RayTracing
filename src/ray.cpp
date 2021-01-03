#include "ray.h"

Ray::Ray(Vector3f origin, Vector3f direction)
{
    this->origin = origin;
    this->direction = direction;
}