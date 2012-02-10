#ifndef PARALLELOGRAM_H_
#define PARALLELOGRAM_H_

#include "plane.h"
#include "illuminative.h"

class Parallelogram : public Plane, public Illuminative
{
protected:
	double m_length1;
	double m_length2;
	Vector3 m_e1;
	Vector3 m_e2;
	int m_area;
public:
	virtual Vector3 GetRandomPoint() const;
	virtual int GetIntersection(Ray r, double* distance) const;
	virtual int GetArea() const;

	Parallelogram(Vector3 a_origin, Vector3 a_normal, Material a_material, bool islight,
	              double length1, double length2, Vector3 e1, Vector3 e2,
	              int a_area,
	              const std::string& a_name)
	  : Plane(a_origin, a_normal, a_material, islight, a_name)
	{
		m_length1 = length1;
		m_length2 = length2;
		m_e1 = e1;
		m_e2 = e2;
		m_area = a_area;
	}
};

#endif /*PARALLELOGRAM_H_*/
