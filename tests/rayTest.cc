#ifndef RAYTEST_
#define RAYTEST_

#include "../ray.h"
#include <gtest/gtest.h>

TEST(Ray, GetPoint)
{
	Ray r(Vector3(), Vector3(1,0,0));
	
	for (int i = 0; i < 100; i++)
	{
		EXPECT_EQ(Vector3(i,0,0), r.GetPoint(i));
	}
	
	Ray r2(Vector3(), Vector3(0,2,3));
	
	for (int i = 0; i < 100; i++)
	{
		EXPECT_EQ(Vector3(0,2*i,3*i), r2.GetPoint(i));
	}
}

#endif /*RAYTEST_*/
