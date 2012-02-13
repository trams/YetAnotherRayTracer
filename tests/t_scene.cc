#include "catch.hpp"

#include <maxwell/engine.h>
#include <maxwell/primitives/ball.h>

TEST_CASE("scene/find_nearest_intersection/empty_scene", "")
{
    Scene scene;
    Ray ray(Vector3(), Vector3(0.0, 0.0, 5.0));

    Primitive const * nearestPrimitive;
    double distance;
    int intersectionType;

    findNearsetIntersection(scene, ray, &nearestPrimitive,
			    &distance, &intersectionType);

    REQUIRE(intersectionType == DontIntersect);
}

TEST_CASE("scene/find_nearest_intersection/one_primitive/outside", "")
{
    Scene scene;
    Ball ball(Vector3(0.0, 0.0, 6.0), 1.0, Material(), false, "");

    scene.Add(&ball);

    Ray ray(Vector3(), Vector3(0.0, 0.0, 5.0).Normalize());

    Primitive const * nearestPrimitive;
    double distance;
    int intersectionType;

    findNearsetIntersection(scene, ray, &nearestPrimitive,
			    &distance, &intersectionType);

    REQUIRE(intersectionType == IntersectOutside);
    REQUIRE(nearestPrimitive == &ball);
    REQUIRE(distance == Approx(5.0));
}

TEST_CASE("scene/find_nearest_intersection/one_primitive/inside", "")
{
    Scene scene;
    Ball ball(Vector3(0.0, 0.0, 0.0), 1.0, Material(), false, "");

    scene.Add(&ball);

    Ray ray(Vector3(), Vector3(0.0, 0.0, 5.0).Normalize());

    Primitive const * nearestPrimitive;
    double distance;
    int intersectionType;

    findNearsetIntersection(scene, ray, &nearestPrimitive,
			    &distance, &intersectionType);

    REQUIRE(intersectionType == IntersectInside);
    REQUIRE(nearestPrimitive == &ball);
    REQUIRE(distance == Approx(1.0));
}

TEST_CASE("scene/find_nearest_intersection/two_primives", "")
{
    Scene scene;
    Ball ball(Vector3(0.0, 0.0, 6.0), 1.0, Material(), false, "");
    Ball ball2(Vector3(0.0, 0.0, 6.0), 2.0, Material(), false, "");

    scene.Add(&ball);
    scene.Add(&ball2);

    Ray ray(Vector3(), Vector3(0.0, 0.0, 5.0).Normalize());

    Primitive const * nearestPrimitive;
    double distance;
    int intersectionType;

    findNearsetIntersection(scene, ray, &nearestPrimitive,
			    &distance, &intersectionType);

    REQUIRE(intersectionType == IntersectOutside);
    REQUIRE(nearestPrimitive == &ball2);
    REQUIRE(distance == Approx(4.0));
}
