#ifndef _GAME_BITMAPFONT_H
#define _GAME_BITMAPFONT_H

#include <lang/String.h>
#include <game/IFont.h>

namespace gr
{
	class Context;
}

namespace io
{
	class InputStream;
}

namespace game
{

	class Sprite;
	class SpriteSheet;

class BitmapFont :
	public IFont
{
public:
	explicit BitmapFont(gr::Context* context, const std::string& filename);

	BitmapFont(gr::Context* context, io::InputStream& dat, io::InputStream& image);

	~BitmapFont();

	void drawString(gr::Context* context, const std::string& str, float y, float x, Anchor anchor) const;

	void drawString(gr::Context* context, const std::string& str, int offset, int length, float x, float y, Anchor anchor) const;

	void drawString(gr::Context* context, const lang::u32string& str, int length, int offset, float x, float y, Anchor anchor) const;

	std::string filter(const std::string& str) const;

	bool isCharacterSupported(int character) const;

	int getStringWidth(const std::string& str, int offset, int length) const;

	int getStringWidth(const lang::u32string& str, int offset, int length) const;

	int getStringHeight(const std::string& str, int offset, int length) const;

	int getStringHeight(const lang::u32string& str, int offset, int length) const;

	int getHeight() const;

	int getMaxAscending() const;

	int getMaxDescending() const;

	int getLeading() const;

	int getTracking() const;

	gr::Rect getBounds(const std::string& str, Anchor anchor, int offset, int length) const; //Following the mangled symbol.

	void setGlyphRenderer(const std::function<void (gr::Context*, Sprite*, float, float)>& renderer); //Added in Seasons 4.1.0

	Sprite* getGlyph(int) const;
private:
	std::map<int, Sprite*> m_glyphs;
	P(SpriteSheet) m_sheet;
	int m_tracking;
	int m_maxAscending;
	int m_maxDescending;
	int m_leading;

	std::function<void (gr::Context*, Sprite*, float, float)> m_renderer;

	int getMaxPivotY(const lang::u32string& str, int offset, int length) const;

	void load(gr::Context* context, io::InputStream& dat, bool loadsheet, const std::string& filename);
};

}

#endif