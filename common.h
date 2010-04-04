// -----------------------------------------------------------
// common.h
// 2004 - Jacco Bikker - jacco@bik5.com - www.bik5.com -   <><
// 2009 - Priymak Aleksandr
// -----------------------------------------------------------

#ifndef I_COMMON_H
#define I_COMMON_H

#include "math.h"
#include "stdlib.h"
#include <cassert>
#include <iostream>
#include <sstream>

#define EPSILON 0.0001

class Vector3
{
public:
	Vector3() : x(.0), y(.0), z(.0) {};
	Vector3( double a_X, double a_Y, double a_Z ) : x( a_X ), y( a_Y ), z( a_Z ) 
	{};
	
	Vector3& Normalize() 
	{ 
		double l = 1.0 / Length(); x *= l; y *= l; z *= l;
		return *this; 
	}
	double SqrLength() const { return x * x + y * y + z * z; }
	double Length() const { return sqrt(SqrLength()); }
	void operator += ( Vector3& a_V ) { x += a_V.x; y += a_V.y; z += a_V.z; }
	void operator -= ( Vector3& a_V ) { x -= a_V.x; y -= a_V.y; z -= a_V.z; }
	void operator *= ( double f ) { x *= f; y *= f; z *= f; }
	void operator *= ( Vector3& a_V ) { x *= a_V.x; y *= a_V.y; z *= a_V.z; }
	Vector3 operator- () const { return Vector3( -x, -y, -z ); }
	friend Vector3 operator + ( const Vector3& v1, const Vector3& v2 ) { return Vector3( v1.x + v2.x, v1.y + v2.y, v1.z + v2.z ); }
	friend Vector3 operator - ( const Vector3& v1, const Vector3& v2 ) { return Vector3( v1.x - v2.x, v1.y - v2.y, v1.z - v2.z ); }
	friend Vector3 operator * ( const Vector3& v, double f ) { return Vector3( v.x * f, v.y * f, v.z * f ); }
	friend Vector3 operator * ( const Vector3& v1, const Vector3& v2 ) { return Vector3( v1.x * v2.x, v1.y * v2.y, v1.z * v2.z ); }
	friend Vector3 operator * ( double f, const Vector3& v ) { return Vector3( v.x * f, v.y * f, v.z * f ); }
	friend bool operator == (const Vector3& v1, const Vector3& v2)
	{
		return ((v1.x == v2.x) and (v1.y == v2.y) and (v1.z == v2.z));
	}
	friend std::ostream& operator << (std::ostream& stream, const Vector3& v)
	{
		stream << '(' << v.x << ',' << v.y << ',' << v.z << ')';
		return stream;
	}
	friend std::istream& operator >> (std::istream& stream, Vector3& v)
	{
		stream >> v.x >> v.y >> v.z;
		return stream;
	}
	 
	union
	{
		struct { double x, y, z; };
		struct { double r, g, b; };
		struct { double cell[3]; };
	};
};

typedef Vector3 Color;

inline double Dot(Vector3 a, Vector3 b)
{
	return a.x*b.x + a.y*b.y + a.z*b.z;
}

inline Vector3 readVector(const char* str)
{
	Vector3 v;
	
	std::istringstream stream(str);
	stream >> v;
	
	return v;	
}

#endif