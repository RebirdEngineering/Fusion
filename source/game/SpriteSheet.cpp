#include <game/SpriteSheet.h>
#include <io/BundleInputStream.h>
#include <gr/Context.h>
#include <gr/Image.h>

using namespace gr;
using namespace io;

namespace game
{

SpriteSheet::SpriteSheet()
{
	m_imagePath = "";
	m_image = 0;
}

SpriteSheet::SpriteSheet(Image* image)
{
	m_imagePath = "";
	m_image = image;
}

SpriteSheet::~SpriteSheet()
{
}

void SpriteSheet::loadImage(Context* context, InputStream& in) //Correct?
{
	m_image = context->createImage(in, in.toString());
};

void SpriteSheet::loadImage(Context* context, const std::string& filename)
{
	BundleInputStream in(filename, BundleInputStream::READ_BULK); //Different on Android?
	loadImage(context, in);
};

void SpriteSheet::unload()
{
	delete m_image;
	m_image = 0;
};

Sprite* SpriteSheet::createSprite(const std::string& id, int x, int y, int width, int height, int pivotX, int pivotY, Sprite::SourceRotation rotation)
{
	P(Sprite) sprite = new Sprite(this, id, x, y, width, height, pivotX, pivotY, rotation);
	m_sprites[id] = sprite;

	return sprite;
}

Sprite* SpriteSheet::getSprite(const std::string& id) const
{
	for (std::map<std::string, P(Sprite)>::const_iterator it = m_sprites.begin(); it != m_sprites.end(); ++it)
	{
		if (it->first == id)
			return it->second;
	}
	return 0;
};

void SpriteSheet::removeSprite(const std::string&)
{
}

Image* SpriteSheet::getImage() const
{
	return m_image;
};

int SpriteSheet::getWidth() const
{
	return m_image->width();
};

int SpriteSheet::getHeight() const
{
	return m_image->height();
};

const std::map<std::string, P(Sprite)>& SpriteSheet::getSprites() const
{
	return m_sprites;
};

}