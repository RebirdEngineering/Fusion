#ifndef _GAME_COMPOSPRITESET_H
#define _GAME_COMPOSPRITESET_H

#include <lang/Object.h>

namespace game
{
	class CompoSprite;

class CompoSpriteSet : //14
	public lang::Object
{
public:
	CompoSpriteSet(); //21

	void add(const std::string& id, CompoSprite* compo); //26

	CompoSprite* getCompoSprite(const std::string& id) const; //32

	void removeSprite(const std::string& id); //38 | Undefined on iOS, guessed var.

	const std::map<std::string, P(CompoSprite)>& getCompoSprites() const; //43 | Unknown where this is.

private:
	std::map<std::string, P(CompoSprite)> m_composites; //46
};

}

#endif