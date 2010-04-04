#include "engine.h"
#include <stdio.h>
#include <gtest/gtest.h>

#include "test/commonTest.h"
#include "test/rayTest.h"
#include "test/intersectionTest.h"
#include "test/tiXmlTest.h"

int main(int argc, char** argv)
{
	printf("Yet Another Raytracer\n");
	if (argc > 1)
	{
		static Engine engine;
		
		engine.Init(argv[1]);
		engine.Calculate();
		engine.Draw();
		engine.WaitForQuit();
	}
	else
	{
		testing::InitGoogleTest(&argc, argv);
		
		return RUN_ALL_TESTS();
	}
}