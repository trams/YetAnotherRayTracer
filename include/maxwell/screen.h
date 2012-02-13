#ifndef SCREEN_H_
#define SCREEN_H_

#include "common.h"
#include <SDL/SDL.h>
#include <string>

class Screen
{
public:
    virtual void SetPixel(int x, int y, const Color& color) = 0;
    virtual void SetCaption(const std::string& caption) = 0;
    virtual void Flip() = 0;
};

class SDLScreen : public Screen
{
private:
    SDL_Surface* m_screen;
public:
    class RuntimeError {};

    SDLScreen(int width, int height);
    ~SDLScreen();

    void SetPixel(int x, int y, const Color& color);
    void SetCaption(const std::string& caption);
    void Flip();
};

#endif /*SCREEN_H_*/
