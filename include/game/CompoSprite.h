#ifndef _GAME_COMPOSPRITE_H
#define _GAME_COMPOSPRITE_H

#include <lang/Object.h>
#include <game/Anchor.h>
#include <math/float2.h>

namespace gr
{
	class Context;
}

namespace game
{
	class Sprite;

class CompoSprite : //20
	public lang::Object
{
public:
	class Entry : public lang::Object //24
	{
	public:
		std::string m_spriteEntryName; //27
		Sprite* m_sprite; //28
		math::float2 m_pos; //29
		math::float2 m_scale; //30
		math::float2 m_flip; //31
		float m_angle; //32
		bool m_visible; //33
	};

	void addSprite(const std::string& spriteId, float x, float y, Sprite* sprite); //43

	void addSprite(const std::string& spriteId, const std::string& spriteCompoId, Sprite* sprite, const math::float2& pos, const math::float2& scale, const math::float2& flip, float angle); //55
	
	void removeSprite(int index); //61 | Recover from ABFM

	void removeSprite(const std::string& spriteId); //67 | Recover from below

	void replaceSprite(const std::string& spriteIdOld, const std::string& spriteIdNew, Sprite* sprite); //75

	void draw(gr::Context* context, float x, float y, Anchor anchor); //84

	Entry& getSpriteEntry(int index); //90

	Entry& getSpriteEntry(const std::string& spriteId); //96

	int getSpriteCount() const; //101

	int getWidth() const; //106

	int getHeight() const; //111

	int getPivotX() const; //116

	int getPivotY() const; //121

	void calculateBounds(); //126

private:
	std::vector<P(Entry)> m_sprites; //129
	std::map<std::string, P(Entry)> m_namedSprites; //130

	int m_width; //132
	int m_height; //133
	int m_pivotX; //134
	int m_pivotY; //135
};

}

#endif