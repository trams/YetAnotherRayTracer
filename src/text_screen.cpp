#include <maxwell/text_screen.h>

void TextScreen::SetPixel(int x, int y, const Color& color)
{
    m_textScreen.push_back(PixelWithColor(x, y, color));
}

void TextScreen::SetCaption(const std::string& )
{
    //do nothing
}

void TextScreen::Flip()
{
    for (std::vector<PixelWithColor>::const_iterator it = m_textScreen.begin();
	 it != m_textScreen.end();
	 ++it)
    {
	std::cout << it->x << '\t' << it->y << '\t' << it->color << std::endl;
    }
}

void TextScreen::waitForExit()
{
    //do nothing
}
