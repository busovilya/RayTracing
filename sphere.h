#include "geometry.h"

struct Sphere
{
    Vector3f center;
    float radius;
    Vector3f color;

    bool intersect(const Vector3f& origin, const Vector3f& ray, float& intersect_dist);
};