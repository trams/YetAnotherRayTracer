#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "common.h"

class Material
{
private:
	double m_diffuse;
	double m_reflection;
	double m_refractionRate;
	double m_absorptionRate;
	Color m_color;
public:
	double GetDiffuse() const { return m_diffuse; }
	double GetReflection() const { return m_reflection; }
	double GetRefraction() const { return 1.0 - (m_diffuse + m_reflection); }
	double GetRefractionRate() const { return m_refractionRate; }
	double GetAbsorptionRate() const { return m_absorptionRate; }
	Color GetColor() const { return m_color; }

	Material()
	{
		m_diffuse = 1.0;
		m_reflection = 0.0;
		m_refractionRate = 1.0;
		m_absorptionRate = 0.0;
	}

	Material(Color a_color, double a_diffuse,
			double a_reflection = 0.0,
			double a_refractionRate = 1.0,
			double a_absorptionRate = 0.0)
	{
		m_color = a_color;
		m_diffuse = a_diffuse;
		m_reflection = a_reflection;
		m_refractionRate = a_refractionRate;
		m_absorptionRate = a_absorptionRate;
	}
};

#endif /*MATERIAL_H_*/
