#include <maxwell/engine.h>
#include <stdio.h>

int main(int argc, char** argv)
{
    printf("Yet Another Raytracer\n");
    if (argc > 1)
    {
	SDLScreen screen(Engine::Width, Engine::Height);
        static Engine engine(screen);

        engine.Init(argv[1]);
        engine.Calculate();
        engine.Draw();
        engine.WaitForQuit();
    }
}
