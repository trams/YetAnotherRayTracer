#include "catch.hpp"

#include <maxwell/ray.h>

TEST_CASE("Ray/GetPoint", "")
{
	Ray r(Vector3(), Vector3(1,0,0));
	
	for (int i = 0; i < 100; i++)
	{
	        REQUIRE(Vector3(i,0,0) == r.GetPoint(i));
	}
	
	Ray r2(Vector3(), Vector3(0,2,3));
	
	for (int i = 0; i < 100; i++)
	{
		REQUIRE(Vector3(0,2*i,3*i) == r2.GetPoint(i));
	}
}
