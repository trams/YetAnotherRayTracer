#ifndef SCREEN_H_
#define SCREEN_H_

#include "common.h"
#include <SDL/SDL.h>
#include <string>

class SDLScreen
{
private:
    SDL_Surface* m_screen;
public:
    class RuntimeError {};

    SDLScreen(int width, int height);
    ~SDLScreen();

    void SetPixel(int x, int y, Color color);
    void SetCaption(const std::string caption);
    void Flip();
};

#endif /*SCREEN_H_*/
