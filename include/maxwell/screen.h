#ifndef SCREEN_H_
#define SCREEN_H_

#include "common.h"
#include <SDL/SDL.h>
#include <string>

class Screen
{
private:
	SDL_Surface* m_screen;
public:
	class RuntimeError {};

	Screen(int width, int height);
	~Screen();
	
	void SetPixel(int x, int y, Color color);
	void SetCaption(const std::string caption);
	void Flip();
};

#endif /*SCREEN_H_*/
