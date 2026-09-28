#ifndef _GAME_SYSTEMFONT_H
#define _GAME_SYSTEMFONT_H

#include <game/IFont.h>
#include <gr/Color.h>

namespace game
{

class SystemFont : //13 | 88 bytes on Win32 (GDI), 56 on iOS, 40 bytes on ABC OSX 3.0.1 and ABS OSX 3.1.1
	public IFont
{
public:
	enum Style //17
	{
		Normal,
		Bold,
		Italic,
	};

	static const std::vector<std::string>& getAvailableFontNames(); //27

	static std::string findBestFontMatch(const std::string&, const std::string&); //36

	SystemFont(gr::Context* context, const std::string& fontName, int fontSize, const gr::Color& fontColor, int style); //47

	~SystemFont(); //52

	void drawString(gr::Context* context, const std::string& str, float y, float x, Anchor anchor) const; //63

	void drawString(gr::Context* context, const std::string& str, int offset, int length, float x, float y, Anchor anchor) const; //76

	std::string filter(const std::string& str) const; //82

	bool isCharacterSupported(int character) const; //88

	int getStringWidth(const std::string& str, int offset, int length) const; //97

	int getStringHeight(const std::string& str, int offset, int length) const; //106

	int getHeight() const; //111

	int getMaxAscending() const; //116

	int getMaxDescending() const; //121

	int getLeading() const; //126

	int getTracking() const; //131

	gr::Rect getBounds(const std::string& str, Anchor anchor, int offset, int length) const; //136 | Mangled symbol suggests this, output suggests we start at str, offset and length

	const char* toString(Style); //141
private:
	class Impl;
	P(Impl) m_impl; //159
};

}

#endif