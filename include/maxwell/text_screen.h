#ifndef TEXT_SCREEN_H_
#define TEXT_SCREEN_H_

#include <maxwell/screen.h>

#include <vector>

struct PixelWithColor
{
    int x;
    int y;
    Color color;

    PixelWithColor(int ax, int ay, Color aColor):
        x(ax),
        y(ay),
        color(aColor)
    {}
};

class TextScreen : public Screen
{
public:
    void SetPixel(int x, int y, const Color& color);
    void SetCaption(const std::string& caption);
    void Flip();
private:
    std::vector<PixelWithColor> m_textScreen;
};

#endif
