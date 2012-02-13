#include <maxwell/primitives/primitive.h>

RayIntersectionPoint Primitive::getIntersection(const Ray& ray) const
{
    RayIntersectionPoint result;
    result.m_ray = ray;

    result.m_intersectionType = GetIntersection(ray, &result.m_distance);

    return result;
}
