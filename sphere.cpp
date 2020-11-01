#include <limits>
#include <math.h>

#include "sphere.h"

bool Sphere::intersect(const Vector3f& origin, const Vector3f& ray, float& intersect_dist)
{
    intersect_dist = std::numeric_limits<float>::max();
    Vector3f origToCenter = center - origin;
    float origToCenterToRayProjectionLen = origToCenter * ray.unit();
    float d2 = origToCenter * origToCenter - origToCenterToRayProjectionLen * origToCenterToRayProjectionLen;
    if(d2 > radius * radius)    return false;
    intersect_dist = std::abs(origToCenterToRayProjectionLen - std::sqrt(radius * radius - d2));
    return true;
}