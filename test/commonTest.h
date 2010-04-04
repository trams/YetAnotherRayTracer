#ifndef COMMONTEST_H_
#define COMMONTEST_H_

#include "../common.h"
#include <gtest/gtest.h>
#include <limits.h>
#include <math.h>

#include <string>
#include <sstream>

int randRange(int min, int max)
{
	double r = rand()/RAND_MAX;
	double result = r*min - r*max + 1.0*min;
	
	EXPECT_GE(INT_MAX, result);
	EXPECT_LE(INT_MIN, result);
	
	return trunc(result);
}


TEST(VectorTest, Operators)
{
	EXPECT_EQ(Vector3(1,1,0), Vector3(1,0,0) + Vector3(0,1,0));  
	EXPECT_EQ(Vector3(3,-4,7), Vector3(2,-8,0) + Vector3(1,4,7));
	
	EXPECT_EQ(Vector3(1,-1,0), Vector3(1,0,0) - Vector3(0,1,0));
	EXPECT_EQ(Vector3(1,-12,-7), Vector3(2,-8,0) - Vector3(1,4,7));
	
	EXPECT_EQ(Vector3(2.4,1.2,0.84), Vector3(1.2,0.6,0.42)*2);
	EXPECT_EQ(Vector3(2.4,1.2,0.84), 2*Vector3(1.2,0.6,0.42));
}

TEST(VectorTest, Input)
{
	std::istringstream stream("1.0 0.0 0.0  0.0 1.0 0.0  0.0 0.0 1.0");
	
	Color color;
	stream >> color;
	EXPECT_EQ(Color(1.0, 0.0, 0.0), color);
	stream >> color;
	EXPECT_EQ(Color(0.0, 1.0, 0.0), color);
	stream >> color;
	EXPECT_EQ(Color(0.0, 0.0, 1.0), color);
}

TEST(VectorTest, DotLength)
{
	EXPECT_EQ(0, Dot(Vector3(rand(),0,0), Vector3(0,rand(),rand())));
	EXPECT_EQ(3, Dot(Vector3(2,3,-2), Vector3(1,1,1)));
	
	double x = Vector3(0,0,0).Length();
	EXPECT_EQ(0, x);
	EXPECT_EQ(1, Vector3(0,1,0).Length());
	EXPECT_EQ(5, Vector3(3,4,0).Length());
	EXPECT_EQ(3, Vector3(0,0,3).Length());
}

TEST(VectorTest, DotLengthEquality)
{
	for (int i = 0; i < 100; i++)
	{
		Vector3 a(randRange(-1000,1000), randRange(-1000,1000), randRange(-1000,1000));
		EXPECT_TRUE(Dot(a,a) == a.SqrLength()) << a;
	}
}

TEST(VectorTest, Normalize)
{
	for (int i = 0; i < 100; i++)
	{
		Vector3 a(rand(), rand(), rand());
		a.Normalize();
		
		EXPECT_FLOAT_EQ(1.0, a.Length());
		//EXPECT_TRUE(absf(a.Length() - 1.0)< EPSILON);
	}
}


#endif /*COMMONTEST_H_*/
