#ifndef ENGINE_H_
#define ENGINE_H_

#include "scene.h"
#include "screen.h"

class Engine
{
public:
    static const int Width = 800;
    static const int Height = 600;
private:
    Screen& m_screen;
    Scene m_scene;
    Color m_image[Width][Height];
    int m_progress;
public:
    void Init(const std::string& filename);
    void Calculate();
    void Draw();
    void WaitForQuit();

    Engine(Screen& screen);
    ~Engine();
};

struct NearestIntersection
{
    const Primitive* primitive;

    RayIntersectionPoint intersection;

    NearestIntersection():
        primitive(NULL),
        intersection()
    {}

    bool isNull() const
    {
	return intersection.isNull();
    }
};

NearestIntersection findNearestIntersection(const Scene& scene, const Ray& ray);

#endif /*ENGINE_H_*/
