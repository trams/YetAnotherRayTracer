#ifndef SCREEN_H_
#define SCREEN_H_

#include "common.h"
#include <string>

class Screen
{
public:
    virtual void SetPixel(int x, int y, const Color& color) = 0;
    virtual void SetCaption(const std::string& caption) = 0;
    virtual void Flip() = 0;
    virtual void waitForExit() = 0;
};

#endif /*SCREEN_H_*/
