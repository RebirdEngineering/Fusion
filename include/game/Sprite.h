#ifndef _GAME_SPRITE_H
#define _GAME_SPRITE_H

#include <game/Anchor.h>
#include <math/Transform.h>
#include <lang/Object.h>

namespace gr
{
	class Context;
	class Shader;
}

namespace game
{

	class SpriteSheet;

	class Sprite :
		public lang::Object
	{
		friend class SpriteSheet; //Needed

	public:
		enum SourceRotation
		{
			ROTATION_NONE,
			ROTATION_CW_90_DEGREES,
			FLIP_HORIZONTAL,
			FLIP_VERTICAL,
		};
		void draw(gr::Context* context, float x, float y, Anchor anchor) const;

		void draw(gr::Context* context, float x, float y, float width, float height, Anchor anchor) const;

		void draw(gr::Context* context, const math::Transform& tm, const math::float2* corners, gr::Shader* shader) const;

		void draw(gr::Context* context, const math::Transform& tm, const math::float2* corners, gr::Shader* shader, math::float4* vertexColors) const;

		SpriteSheet* getSheet() const;

		const std::string& getName() const;

		int getWidth() const;

		int getHeight() const;

		int getPivotX() const;

		int getPivotY() const;

		int getPositionInSheetX() const;

		int getPositionInSheetY() const;
	private:
		Sprite(SpriteSheet* sheet, const std::string& name, int x, int y, int width, int height, short pivotX, short pivotY, SourceRotation rotation);

		SpriteSheet* m_sheet;

		std::string m_name;

		short m_x;
		short m_y;
		short m_width;
		short m_height;
		short m_pivotX;
		short m_pivotY;
		math::float2 m_UVs[4];
	};

}

#endif