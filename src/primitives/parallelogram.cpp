#include <maxwell/primitives/parallelogram.h>

int Parallelogram::GetIntersection(Ray r, double* distance) const
{
    assert( fabs(m_e1.SqrLength() - 1) < EPSILON  );
    assert( fabs(m_e2.SqrLength() - 1) < EPSILON  );

    double dist;
    int result = Plane::GetIntersection(r, &dist);

    if (result != DontIntersect)
    {
        Vector3 p = r.GetPoint(dist) - m_origin;
        if ((fabs(Dot(p, m_e1)) < (m_length1 / 2)) && ((fabs(Dot(p, m_e2)) < (m_length2 / 2))))
        {
            *distance = dist;
            return result;
        }
    }

    return DontIntersect;
}

Vector3 Parallelogram::GetRandomPoint() const
{
    double x1 = rand()/((double)RAND_MAX + 1) - 0.5;
    double x2 = rand()/((double)RAND_MAX + 1) - 0.5;

    assert((x1 > -0.5) && (x1 < 0.5));
    assert((x2 > -0.5) && (x2 < 0.5));

    return (m_origin + x1 * m_e1 + x2 * m_e2);
}

int Parallelogram::GetArea() const
{
    return m_area;
}
