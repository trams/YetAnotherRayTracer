#include <maxwell/engine.h>
#include <maxwell/text_screen.h>

int main(int argc, char** argv)
{
    if (argc > 1)
    {
	TextScreen screen;
        static Engine engine(screen);

        engine.Init(argv[1]);
        engine.Calculate();
        engine.Draw();
        engine.WaitForQuit();
    }
    else
	return -1;
}
