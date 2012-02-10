#include "catch.hpp"

#include <maxwell/common.h>

#include <limits.h>
#include <math.h>

#include <string>
#include <sstream>

int randRange(int min, int max)
{
	double r = rand()/RAND_MAX;
	double result = r*min - r*max + 1.0*min;
	
	REQUIRE(INT_MAX >= result);
	REQUIRE(INT_MIN <= result);
	
	return trunc(result);
}


TEST_CASE("VectorTest/Operators", "")
{
	REQUIRE(Vector3(1,1,0) == Vector3(1,0,0) + Vector3(0,1,0));  
	REQUIRE(Vector3(3,-4,7) == Vector3(2,-8,0) + Vector3(1,4,7));
	
	REQUIRE(Vector3(1,-1,0) == Vector3(1,0,0) - Vector3(0,1,0));
	REQUIRE(Vector3(1,-12,-7) == Vector3(2,-8,0) - Vector3(1,4,7));
	
	REQUIRE(Vector3(2.4,1.2,0.84) == Vector3(1.2,0.6,0.42)*2);
	REQUIRE(Vector3(2.4,1.2,0.84) == 2*Vector3(1.2,0.6,0.42));
}

TEST_CASE("VectorTest/Input", "")
{
	std::istringstream stream("1.0 0.0 0.0  0.0 1.0 0.0  0.0 0.0 1.0");
	
	Color color;
	stream >> color;
	REQUIRE(Color(1.0, 0.0, 0.0) == color);
	stream >> color;
	REQUIRE(Color(0.0, 1.0, 0.0) == color);
	stream >> color;
	REQUIRE(Color(0.0, 0.0, 1.0) == color);
}

TEST_CASE("VectorTest/DotLength", "")
{
	REQUIRE(0 == Dot(Vector3(rand(),0,0), Vector3(0,rand(),rand())));
	REQUIRE(3 == Dot(Vector3(2,3,-2), Vector3(1,1,1)));
	
	double x = Vector3(0,0,0).Length();
	REQUIRE(0 == x);
	REQUIRE(1 == Vector3(0,1,0).Length());
	REQUIRE(5 == Vector3(3,4,0).Length());
	REQUIRE(3 == Vector3(0,0,3).Length());
}

TEST_CASE("VectorTest/DotLengthEquality", "")
{
	for (int i = 0; i < 100; i++)
	{
		Vector3 a(randRange(-1000,1000), randRange(-1000,1000), randRange(-1000,1000));
		REQUIRE(Dot(a,a) == a.SqrLength());
	}
}

TEST_CASE("VectorTest/Normalize", "")
{
	for (int i = 0; i < 100; i++)
	{
		Vector3 a(rand(), rand(), rand());
		a.Normalize();
		
		REQUIRE(fabs(a.Length() - 1.0)< EPSILON);
	}
}
