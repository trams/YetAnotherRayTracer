#ifndef PLANE_H_
#define PLANE_H_

#include "primitive.h"

class Plane : public Primitive
{
protected:
	Vector3 m_origin;
	Vector3 m_normal;
public:
	virtual int GetIntersection(Ray r, double* distance) const;
	virtual Vector3 GetNormal(Vector3 point) const;

	Plane(Vector3 a_origin, Vector3 a_normal, Material a_material, bool islight, const std::string& a_name)
		: Primitive(a_material, islight, a_name), m_origin(a_origin), m_normal(a_normal)
	{
		m_normal.Normalize();
	}
};

#endif /*PLANE_H_*/
