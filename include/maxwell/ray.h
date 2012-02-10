#ifndef RAY_H_
#define RAY_H_

#include "common.h"

class Ray
{
private:
    Vector3 m_origin;
    Vector3 m_direction;
public:
    Vector3 GetOrigin() const { return m_origin; }
    Vector3 GetDirection() const { return m_direction; }

    Vector3 GetPoint(double distance)
    {
        return (m_origin + m_direction*distance);
    }

    Ray(Vector3 a_origin, Vector3 a_direction)
        : m_origin(a_origin), m_direction(a_direction)
    {}
};

#endif /*RAY_H_*/
