#include <maxwell/primitives/ball.h>

int Ball::GetArea() const
{
	return 1;
}

Vector3 Ball::GetRandomPoint() const
{
	return m_center;
}

int Ball::GetIntersection(Ray r, double* distance) const
{
	assert( fabs(r.GetDirection().Length() - 1) < EPSILON  );
	
	double t = Dot(m_center - r.GetOrigin(), r.GetDirection());
	
	Vector3 nearest = r.GetOrigin() + r.GetDirection() * t;
	double sqrDist = (nearest - m_center).SqrLength();
	
	if (sqrDist > m_radius*m_radius)
		return DontIntersect;
	
	double result = t - sqrt(m_radius*m_radius - sqrDist);
	double result2 = t + sqrt(m_radius*m_radius - sqrDist);
	
	if (result2 < EPSILON)
		return DontIntersect;
	else
	{
		if (result < EPSILON)
		{
			*distance = result2;
			return IntersectInside;
		}
		else
		{
			*distance = result;
			return IntersectOutside;
		}
	}
}

Vector3 Ball::GetNormal(Vector3 point) const
{
	Vector3 result = point - m_center;
	result.Normalize();
	return result;
}
