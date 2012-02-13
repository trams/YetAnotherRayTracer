#ifndef SDL_SCREEN_H_
#define SDL_SCREEN_H_

#include <maxwell/screen.h>

#include <SDL/SDL.h>

class SDLScreen : public Screen
{
private:
    SDL_Surface* m_screen;
public:
    class RuntimeError {};

    SDLScreen(int width, int height);
    ~SDLScreen();

    virtual void SetPixel(int x, int y, const Color& color);
    virtual void SetCaption(const std::string& caption);
    virtual void Flip();
    virtual void waitForExit();
};

#endif
