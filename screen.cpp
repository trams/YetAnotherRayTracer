#include "screen.h"
#include <SDL/SDL.h>

int min(int x, int y)
{
	if (y > x)
		return x;
	else
		return y;
}

Screen::Screen(int width, int height)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
		throw RuntimeError();
	
	m_screen = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE);
	if (m_screen == NULL)
		throw RuntimeError();
}

Screen::~Screen()
{
	SDL_Quit();
}

void Screen::SetPixel(int x, int y, Color color)
{
	int num = x + y*m_screen->clip_rect.w;
	Uint32 * pixel = (Uint32*)m_screen->pixels + num;
	*pixel = SDL_MapRGB(m_screen->format, min(color.r*255, 255), min(color.g*255, 255), min(color.b*255, 255) ); 
}

void Screen::Flip()
{
	if (SDL_Flip(m_screen) == -1)
	  throw RuntimeError();
}

void Screen::SetCaption(const std::string caption)
{
	SDL_WM_SetCaption(caption.c_str(), NULL);
}
