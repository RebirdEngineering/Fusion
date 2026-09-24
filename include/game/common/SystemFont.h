#ifndef _GAME_COMMON_SYSTEMFONT_H
#define _GAME_COMMON_SYSTEMFONT_H

#include <game/SystemFont.h>

namespace game
{

SystemFont::SystemFont(gr::Context* context, const std::string& fontName, int fontSize, const gr::Color& fontColor, int style) //15
{
	m_impl = new Impl(context, fontName, fontSize, fontColor, style);
}

SystemFont::~SystemFont()
{
}

void SystemFont::drawString(gr::Context* context, const std::string& str, float y, float x, Anchor anchor) const //Idk why x and y are swapped
{
	m_impl->drawString(context, str, 0, -1, y, x, anchor);
}

void SystemFont::drawString(gr::Context* context, const std::string& str, int offset, int length, float x, float y, Anchor anchor) const
{
	m_impl->drawString(context, str, offset, length, y, x, anchor);
}

std::string SystemFont::filter(const std::string& str) const
{
	return m_impl->filter(str);
}

bool SystemFont::isCharacterSupported(int character) const
{
	return m_impl->isCharacterSupported(character); //Always?
}

int SystemFont::getStringWidth(const std::string& str, int offset, int length) const
{
	return m_impl->getStringWidth(str, offset, length);
}

int SystemFont::getStringHeight(const std::string& str, int offset, int length) const
{
	return m_impl->getStringHeight(str, offset, length);
}

int SystemFont::getHeight() const
{
	return m_impl->getHeight();
}

int SystemFont::getMaxAscending() const
{
	return m_impl->getMaxAscending();
}

int SystemFont::getMaxDescending() const
{
	return m_impl->getMaxDescending();
}

int SystemFont::getLeading() const
{
	return m_impl->getLeading();
}

int SystemFont::getTracking() const
{
	return m_impl->getTracking(); //Always?
}

gr::Rect SystemFont::getBounds(const std::string& str, Anchor anchor, int offset, int length) const
{
	return m_impl->getBounds(str, anchor, offset, length);
}

}

#endif