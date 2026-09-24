#ifndef _GAME_SYSTEMFONT_H
#define _GAME_SYSTEMFONT_H

#include <game/IFont.h>
#include <gr/Color.h>

namespace game
{

class SystemFont :
	public IFont
{
public:
	enum Style
	{
		Normal,
		Bold,
		Italic,
	};
	static const std::vector<std::string> getAvailableFontNames();

	static std::string findBestFontMatch(const std::string&, const std::string&);

	SystemFont(gr::Context* context, const std::string& fontName, int fontSize, const gr::Color& fontColor, int style);

	~SystemFont();

	void drawString(gr::Context* context, const std::string& str, float y, float x, Anchor anchor) const;

	void drawString(gr::Context* context, const std::string& str, int offset, int length, float x, float y, Anchor anchor) const;

	std::string filter(const std::string& str) const;

	bool isCharacterSupported(int character) const;

	int getStringWidth(const std::string& str, int offset, int length) const;

	int getStringHeight(const std::string& str, int offset, int length) const;

	int getHeight() const;

	int getMaxAscending() const;

	int getMaxDescending() const;

	int getLeading() const;

	int getTracking() const;

	gr::Rect getBounds(const std::string& str, Anchor anchor, int offset, int length) const; //Mangled symbol suggests this, output suggests we start at str, offset and length

	const char* toString(Style);
private:
	class Impl;
	P(Impl) m_impl;
};

}

#endif