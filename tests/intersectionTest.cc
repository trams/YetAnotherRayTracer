#include "catch.hpp"

#include <maxwell/primitives/plane.h>
#include <maxwell/primitives/ball.h>
#include <maxwell/ray.h>

//TODO: Add some tests
TEST_CASE("Intersection/Ball", "")
{
	Material m(Color(), 0.0);
	
	Ball s1(Vector3(3,3,0), 1, m, false, "");
	Ball s2(Vector3(4,-3,0), 1, m, false, "");
	
	double result = 0;
	REQUIRE(1 == s1.GetIntersection(Ray(Vector3(), Vector3(1,1,0).Normalize()), &result));
	REQUIRE(Approx(3*sqrt(2) - 1) == result);

	result = 0;	
	REQUIRE(1 == s2.GetIntersection(Ray(Vector3(), Vector3(4,-3,0).Normalize()), &result));
	REQUIRE(4 == result);
	
	for (int i = 0; i < 100; i++)
	{
		Ray r(Vector3(3, 3, 0), Vector3(rand(), rand(), rand()).Normalize());
		Ray r2(Vector3(4, -3, 0), Vector3(rand(), rand(), rand()).Normalize());
		
		REQUIRE(-1 == s1.GetIntersection(r, &result));
		REQUIRE(-1 == s2.GetIntersection(r2, &result));
	}
	
	REQUIRE(0 == s1.GetIntersection(Ray(Vector3(), Vector3(1,0,0)), &result));
	REQUIRE(0 == s2.GetIntersection(Ray(Vector3(), Vector3(1,0,0)), &result));
}

//TODO: Add some tests
TEST_CASE("Intersection/Plane", "")
{
	Material m(Color(), 0.0);
	Plane p1(Vector3(0,0,1), Vector3(0,0,1), m, false, "");
	
	double result = 0;
	REQUIRE(0 == p1.GetIntersection(Ray(Vector3(), Vector3(1,0,0)), &result));
	
	result = 0;
	REQUIRE(0 == p1.GetIntersection(Ray(Vector3(), Vector3(0,1,0)), &result));
	
	result = 0;
	REQUIRE(1 == p1.GetIntersection(Ray(Vector3(), Vector3(0,0,1)), &result));
	REQUIRE(1.0 == Approx(result).epsilon(0.0001));
	
	for (int i = 0; i < 100; i++)
	{
		Vector3 v = Vector3(rand(), rand(), rand()).Normalize();
		
		result = 0;
		int r1 = p1.GetIntersection(Ray(Vector3(), v), &result);

		if (r1 != 0)
		{
			REQUIRE(1 == r1);
			REQUIRE(1 <= result);
		}

		result = 0;
		int r2 = p1.GetIntersection(Ray(Vector3(), -v), &result);

		if (r2 != 0)
		{
			REQUIRE(1 == r2);
			REQUIRE(1 <= result);
		}
		
		REQUIRE(0 == (r1*r2));
	}
}

