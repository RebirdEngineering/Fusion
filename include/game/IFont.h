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
class IFont : //20
	public lang::Object
{
public:
	virtual void drawString(gr::Context* context, const std::string& str, float y, float x, Anchor anchor) const = 0; //34

	virtual void drawString(gr::Context* context, const std::string& str, int offset, int length, float x, float y, Anchor anchor) const = 0; //47

	virtual std::string filter(const std::string & str) const = 0; //53

	virtual bool isCharacterSupported(int character) const = 0; //59

	virtual int getStringWidth(const std::string& str, int offset, int length) const = 0; //68

	virtual int getStringHeight(const std::string& str, int offset, int length) const = 0; //77

	virtual int getHeight() const = 0; //82

	virtual int getMaxAscending() const = 0; //87

	virtual int getMaxDescending() const = 0; //92

	virtual int getLeading() const = 0; //97

	virtual int getTracking() const = 0; //102

	virtual gr::Rect getBounds(const std::string& str, Anchor anchor, int offset, int length) const = 0; //107 | Mangled symbol suggests this order.

protected:
	IFont(); //110

private:
	IFont(const IFont&); //113
	IFont& operator=(const IFont&); //114
};

}

#endif