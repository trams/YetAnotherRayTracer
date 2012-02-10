#ifndef SPHERE_H_
#define SPHERE_H_

#include "illuminative.h"
#include "primitive.h"

class Ball : public Primitive, public Illuminative
{
protected:
	Vector3 m_center;
	double m_radius;
public:
	virtual int GetIntersection(Ray r, double* distance) const;
	virtual Vector3 GetNormal(Vector3 point) const;
	virtual Vector3 GetRandomPoint() const;
	virtual int GetArea() const;

	Vector3 GetCenter() const { return m_center; }

	Ball(Vector3 a_center, double a_radius, Material a_material, bool a_isLight, const std::string& a_name)
		: Primitive(a_material, a_isLight, a_name), m_center(a_center), m_radius(a_radius)
	{}
};

#endif /*SPHERE_H_*/
