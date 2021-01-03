#include <limits>
#include <math.h>

#include "sphere.h"

bool Sphere::intersect(const Ray& ray, float& intersect_dist)
{
    intersect_dist = std::numeric_limits<float>::max();
    Vector3f origToCenter = center - ray.origin;
    float origToCenterToRayProjectionLen = origToCenter * ray.direction.unit();
    float d2 = origToCenter * origToCenter - origToCenterToRayProjectionLen * origToCenterToRayProjectionLen;
    if(d2 > radius * radius)    return false;
    intersect_dist = std::abs(origToCenterToRayProjectionLen - std::sqrt(radius * radius - d2));
    return true;
}