#ifndef _GAME_COMPOSPRITESET_H
#define _GAME_COMPOSPRITESET_H

#include <lang/Object.h>

namespace game
{
	class CompoSprite;

class CompoSpriteSet :
	public lang::Object
{
public:
	CompoSpriteSet();

	void add(const std::string& id, CompoSprite* compo);

	CompoSprite* getCompoSprite(const std::string& id) const;

	void removeSprite(const std::string& id); //Undefined on iOS, guessed var.

	const std::map<std::string, P(CompoSprite)> getCompoSprites() const; //Unknown where this is.
private:
	std::map<std::string, P(CompoSprite)> m_composites;
};

}

#endif