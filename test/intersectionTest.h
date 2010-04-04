#ifndef INTERSECTIONTEST_H_
#define INTERSECTIONTEST_H_

#include "../primitives/plane.h"
#include "../primitives/ball.h"
#include "../ray.h"
#include <gtest/gtest.h>

//TODO: Add some tests
TEST(Intersection, Ball)
{
	Material m(Color(), 0.0);
	
	Ball s1(Vector3(3,3,0), 1, m, false, "");
	Ball s2(Vector3(4,-3,0), 1, m, false, "");
	
	double result = 0;
	EXPECT_EQ(1, s1.GetIntersection(Ray(Vector3(), Vector3(1,1,0).Normalize()), &result));
	EXPECT_FLOAT_EQ(3*sqrt(2) - 1, result);

	result = 0;	
	EXPECT_EQ(1, s2.GetIntersection(Ray(Vector3(), Vector3(4,-3,0).Normalize()), &result));
	EXPECT_FLOAT_EQ(4, result);
	
	for (int i = 0; i < 100; i++)
	{
		Ray r(Vector3(3, 3, 0), Vector3(rand(), rand(), rand()).Normalize());
		Ray r2(Vector3(4, -3, 0), Vector3(rand(), rand(), rand()).Normalize());
		
		EXPECT_EQ(-1, s1.GetIntersection(r, &result));
		EXPECT_EQ(-1, s2.GetIntersection(r2, &result)); 
	}
	
	EXPECT_EQ(0, s1.GetIntersection(Ray(Vector3(), Vector3(1,0,0)), &result));
	EXPECT_EQ(0, s2.GetIntersection(Ray(Vector3(), Vector3(1,0,0)), &result));
}

//TODO: Add some tests
TEST(Intersection, Plane)
{
	Material m(Color(), 0.0);
	Plane p1(Vector3(0,0,1), Vector3(0,0,1), m, false, "");
	
	double result = 0;
	EXPECT_EQ(0, p1.GetIntersection(Ray(Vector3(), Vector3(1,0,0)), &result));
	
	result = 0;
	EXPECT_EQ(0, p1.GetIntersection(Ray(Vector3(), Vector3(0,1,0)), &result));
	
	result = 0;
	EXPECT_EQ(1, p1.GetIntersection(Ray(Vector3(), Vector3(0,0,1)), &result));
	EXPECT_FLOAT_EQ(1, result);
	
	for (int i = 0; i < 100; i++)
	{
		Vector3 v = Vector3(rand(), rand(), rand()).Normalize();
		
		result = 0;
		int r1 = p1.GetIntersection(Ray(Vector3(), v), &result);

		if (r1 != 0)
		{
			EXPECT_EQ(1, r1);
			EXPECT_LE(1, result);
		}

		result = 0;
		int r2 = p1.GetIntersection(Ray(Vector3(), -v), &result);

		if (r2 != 0)
		{
			EXPECT_EQ(1, r2);
			EXPECT_LE(1, result);
		}
		
		EXPECT_EQ(0 ,(r1*r2));
	}
}

#endif /*INTERSECTIONTEST_H_*/
