#include <maxwell/primitives/plane.h>

const double planeWidth = EPSILON;

int Plane::GetIntersection(Ray r, double* distance) const
{
    assert( fabs(r.GetDirection().Length() - 1) < EPSILON  );

    double dot = Dot(m_normal, r.GetDirection());

    if (fabs(dot) < EPSILON)
        return DontIntersect;

    double dot2 = Dot((m_origin - r.GetOrigin()), m_normal);
    double t = (dot2 / dot);

    if (t < EPSILON)
        return DontIntersect;

    double dt = planeWidth / dot;

    *distance = t - dt;

    return IntersectOutside;
}

Vector3 Plane::GetNormal(Vector3 point) const
{
    if (Dot(point - m_origin, m_normal) > 0)
        return m_normal;
    else
        return -m_normal;
}
