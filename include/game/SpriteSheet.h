#ifndef _GAME_SPRITESHEET_H
#define _GAME_SPRITESHEET_H

#include <game/Sprite.h>
#include <io/InputStream.h>

namespace gr
{
	class Image;
	class Context;
}

namespace game
{

class SpriteSheet :
	public lang::Object
{
public:
	SpriteSheet();

	SpriteSheet(gr::Image* image);

	virtual ~SpriteSheet();

	void loadImage(gr::Context* context, io::InputStream& in);
	void loadImage(gr::Context* context, const std::string& filename);

	void unload();
	
	Sprite* createSprite(const std::string& id, int x, int y, int width, int height, int pivotX, int pivotY, Sprite::SourceRotation rotation);
	
	void removeSprite(const std::string&);

	Sprite* getSprite(const std::string& id) const;

	gr::Image* getImage() const;

	int getWidth() const;

	int getHeight() const;

	const std::map<std::string, P(Sprite)>& getSprites() const;
private:
	std::string m_imagePath;
	P(gr::Image) m_image;
	std::map<std::string, P(Sprite)> m_sprites;
};

}

#endif