#ifndef _GAME_IFONT_H
#define _GAME_IFONT_H

#include <game/Anchor.h>
#include <lang/Object.h>

namespace gr
{
	class Context;
};

namespace game
{
class IFont :
	public lang::Object
{
public:
	virtual void drawString(gr::Context* context, const std::string& str, float y, float x, Anchor anchor) const = 0;

	virtual void drawString(gr::Context* context, const std::string& str, int offset, int length, float x, float y, Anchor anchor) const = 0;

	virtual std::string filter(const std::string & str) const = 0;

	virtual bool isCharacterSupported(int character) const = 0;

	virtual int getStringWidth(const std::string& str, int offset, int length) const = 0;

	virtual int getStringHeight(const std::string& str, int offset, int length) const = 0;

	virtual int getHeight() const = 0;

	virtual int getMaxAscending() const = 0;

	virtual int getMaxDescending() const = 0;

	virtual int getLeading() const = 0;

	virtual int getTracking() const = 0;

	virtual gr::Rect getBounds(const std::string& str, Anchor anchor, int offset, int length) const = 0; //Mangled symbol suggests this order.
protected:
	IFont();
private:
	IFont(const IFont&);
	IFont& operator=(const IFont&);
};

}

#endif