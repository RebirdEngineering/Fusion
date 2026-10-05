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

class BitmapFont : //22
	public IFont
{
public:
	explicit BitmapFont(gr::Context* context, const std::string& filename); //32

	BitmapFont(gr::Context* context, io::InputStream& dat, io::InputStream& image); //40

	~BitmapFont(); //45

	void drawString(gr::Context* context, const std::string& str, float y, float x, Anchor anchor) const; //56

	void drawString(gr::Context* context, const std::string& str, int offset, int length, float x, float y, Anchor anchor) const; //69

	void drawString(gr::Context* context, const lang::u32string& str, int length, int offset, float x, float y, Anchor anchor) const; //82

	std::string filter(const std::string& str) const; //88

	bool isCharacterSupported(int character) const; //94

	int getStringWidth(const std::string& str, int offset, int length) const; //103

	int getStringWidth(const lang::u32string& str, int offset, int length) const; //112

	int getStringHeight(const std::string& str, int offset, int length) const; //121

	int getStringHeight(const lang::u32string& str, int offset, int length) const; //130

	int getHeight() const; //135

	int getMaxAscending() const; //140

	int getMaxDescending() const; //145

	int getLeading() const; //150

	int getTracking() const; //155

	gr::Rect getBounds(const std::string& str, Anchor anchor, int offset, int length) const; //160

	void setGlyphRenderer(const std::function<void (gr::Context*, Sprite*, float, float)>& renderer); //165

	Sprite* getGlyph(int) const; //171
private:
	std::map<int, Sprite*> m_glyphs; //174
	P(SpriteSheet) m_sheet; //175
	int m_tracking; //176
	int m_maxAscending; //177
	int m_maxDescending; //178
	int m_leading; //179

	std::function<void (gr::Context*, Sprite*, float, float)> m_renderer; //181

	int getMaxPivotY(const lang::u32string& str, int offset, int length) const; //183

	void load(gr::Context* context, io::InputStream& dat, bool loadsheet, const std::string& filename); //185
};

}

#endif