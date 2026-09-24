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

class CompoSprite :
	public lang::Object
{
public:
	class Entry :
		public lang::Object
	{
	public:
		std::string m_spriteEntryName;
		Sprite* m_sprite;
		math::float2 m_pos;
		math::float2 m_scale;
		math::float2 m_flip;
		float m_angle;
		bool m_visible;
	};
	void addSprite(const std::string& spriteId, float x, float y, Sprite* sprite);

	void addSprite(const std::string& spriteId, const std::string& spriteCompoId, Sprite* sprite, const math::float2& pos, const math::float2& scale, const math::float2& flip, float angle);

	void removeSprite(int index); //Recover from below

	void removeSprite(const std::string& spriteId); //Recover from below

	void replaceSprite(const std::string& spriteIdOld, const std::string& spriteIdNew, Sprite* sprite);

	void draw(gr::Context* context, float x, float y, Anchor anchor);

	Entry& getSpriteEntry(int index);

	Entry& getSpriteEntry(const std::string& spriteId);

	int getSpriteCount() const;

	int getWidth() const;

	int getHeight() const;

	int getPivotX() const;

	int getPivotY() const;

	void calculateBounds();
private:
	std::vector<P(Entry)> m_sprites;
	std::map<std::string, P(Entry)> m_namedSprites;
	int m_width;
	int m_height;
	int m_pivotX;
	int m_pivotY;
};

}

#endif