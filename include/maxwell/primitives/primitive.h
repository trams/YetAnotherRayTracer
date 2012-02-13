#ifndef PRIMITIVE_H_
#define PRIMITIVE_H_

#include "../material.h"
#include "../ray.h"
#include "../common.h"
#include <string>

static const int DontIntersect = 0;
static const int IntersectOutside = 1;
static const int IntersectInside = -1;

struct RayIntersectionPoint
{
    int m_intersectionType;
    Ray m_ray;
    double m_distance;

    RayIntersectionPoint():
        m_intersectionType(0),
        m_ray(Vector3(), Vector3()),
	m_distance(0.0)
    {}

    bool isNull() const
    {
	return (m_intersectionType == DontIntersect);
    }

    double getDistance() const
    {
	return m_distance;
    }
};

class Primitive
{
protected:
    Material m_material;
    bool m_isIlluminative;
    const std::string m_name;
public:
    virtual int GetIntersection(Ray r, double* distance) const = 0;
    virtual RayIntersectionPoint getIntersection(const Ray& ray) const;

    virtual Vector3 GetNormal(Vector3 point) const = 0;

    virtual Material GetMaterial() const
    {
        return m_material;
    }

    virtual bool IsIlluminative() const
    {
        return m_isIlluminative;
    }

    virtual const std::string& GetName() const
    {
        return m_name;
    }

    virtual ~Primitive()
    {}

    Primitive(Material a_material, bool a_isLight, const std::string& a_name)
        : m_material(a_material), m_isIlluminative(a_isLight), m_name(a_name)
    {}
};

#endif /*PRIMITIVE_H_*/
