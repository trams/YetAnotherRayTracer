#include <maxwell/primitives/primitive.h>

IntersectionPoint Primitive::getIntersection(const Ray& ray) const
{
    IntersectionPoint result;
    double distance;

    result.m_intersectionType = GetIntersection(ray, &distance);
    result.m_point = ray.GetPoint(distance);

    return result;
}
