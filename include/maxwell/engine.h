#ifndef ENGINE_H_
#define ENGINE_H_

#include "scene.h"
#include "screen.h"

class Engine
{
private:
    static const int Width = 800;
    static const int Height = 600;

    Screen m_screen;
    Scene m_scene;
    Color m_image[Width][Height];
    int m_progress;
public:
    void Init(const std::string& filename);
    void Calculate();
    void Draw();
    void WaitForQuit();

    Engine();
    ~Engine();
};

#endif /*ENGINE_H_*/
