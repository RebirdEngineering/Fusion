#ifndef _GAME_COMMON_SYSTEMFONT_H
#define _GAME_COMMON_SYSTEMFONT_H

const std::vector<std::string>& SystemFont::getAvailableFontNames()
{
	return m_impl->getAvailableFontNames();
}

std::string SystemFont::findBestFontMatch(const std::string& param1, const std::string& param2)
{
	return m_impl->findBestFontMatch(param1, param2);
}

SystemFont::SystemFont(Context* context, const std::string& fontName, int fontSize, const gr::Color& fontColor, int style) //15 | 45B9D0
{
	m_impl = new Impl(context, fontName, fontSize, fontColor, style); //4F0AA0 | 17
}

SystemFont::~SystemFont() //45A820 | 21-22
{
}

void SystemFont::drawString(Context* context, const std::string& str, float y, float x, Anchor anchor) const //45C780 | 24
{
	m_impl->drawString(context, str, 0, -1, x, y, anchor); //45C230 | 26
}

void SystemFont::drawString(Context* context, const std::string& str, int offset, int length, float x, float y, Anchor anchor) const //45C7C0 | 29
{
	m_impl->drawString(context, str, offset, length, x, y, anchor); //45C230 | 31
}

std::string SystemFont::filter(const std::string& str) const //45ADA0 | 34
{
	return m_impl->filter(str); //45AD70 | 36
}

bool SystemFont::isCharacterSupported(int character) const //39
{
	return m_impl->isCharacterSupported(character);
}

int SystemFont::getStringWidth(const std::string& str, int offset, int length) const //45BD50 | 44
{
	return m_impl->getStringWidth(str, offset, length); //45B890 | 46
}

int SystemFont::getStringHeight(const std::string& str, int offset, int length) const //45BDA0 | 49
{
	return m_impl->getStringHeight(str, offset, length); //45B890 | 51
}

int SystemFont::getHeight() const
{
	return m_impl->getHeight(); //45A620 | 56
}

int SystemFont::getMaxAscending() const
{
	return m_impl->getMaxAscending(); //45A630 | 61
}

int SystemFont::getMaxDescending() const
{
	return m_impl->getMaxDescending(); //45A640 | 66
}

int SystemFont::getLeading() const
{
	return m_impl->getLeading(); //45A650 | 71
}

int SystemFont::getTracking() const
{
	return m_impl->getTracking(); //495DC0
}

Rect SystemFont::getBounds(const std::string& str, Anchor anchor, int offset, int length) const //45BDF0 | 79
{
	return m_impl->getBounds(str, anchor, offset, length); //45BC70 | 81
}

#endif