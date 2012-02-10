#ifndef PRIMITIVE_H_
#define PRIMITIVE_H_

#include "../material.h"
#include "../ray.h"
#include "../common.h"
#include <string>

static const int DontIntersect = 0;
static const int IntersectOutside = 1;
static const int IntersectInside = -1;

class Primitive
{
protected:
	Material m_material;
	bool m_isIlluminative;
	const std::string m_name;
public:
	virtual int GetIntersection(Ray r, double* distance) const = 0;
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
