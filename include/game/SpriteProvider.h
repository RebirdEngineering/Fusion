#ifndef _GAME_SPRITEPROVIDER_H
#define _GAME_SPRITEPROVIDER_H

#include <lang/pp.h>

namespace game
{
	class Sprite;

class SpriteProvider //13
{
public:
	virtual ~SpriteProvider(); //16
	virtual Sprite* getSprite(const std::string& spriteId) = 0; //17
};

}

#endif