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
}

SpriteSheet::SpriteSheet(Image* image) //26
{
	m_imagePath = "";
	m_image = image;
}

void SpriteSheet::loadImage(Context* context, InputStream& in) //31-34
{
	m_image = context->createImage(in, in.toString()); //33
}

void SpriteSheet::loadImage(Context* context, const std::string& filename) //36
{
	BundleInputStream in(filename, BundleInputStream::READ_BULK); //38
	loadImage(context, in);
}

SpriteSheet::~SpriteSheet()
{
}

void SpriteSheet::unload()
{
	delete m_image;
	m_image = 0;
};

Sprite* SpriteSheet::createSprite(const std::string& id, int x, int y, int width, int height, int pivotX, int pivotY, Sprite::SourceRotation rotation) //51-56
{
	P(Sprite) sprite = new Sprite(this, id, x, y, width, height, pivotX, pivotY, rotation); //53
	m_sprites[id] = sprite; //54
	return sprite;
}

Sprite* SpriteSheet::getSprite(const std::string& id) const //63
{
	std::map<std::string, P(Sprite)>::const_iterator it = m_sprites.find(id); //65
	if (it->first == id) //66
		return it->second;

	return 0;
}

void SpriteSheet::removeSprite(const std::string& id)
{
	delete m_sprites[id];
	m_sprites[id] = 0;
}

Image* SpriteSheet::getImage() const
{
	return m_image; //71
}

int SpriteSheet::getWidth() const
{
	return m_image->width();
}

int SpriteSheet::getHeight() const
{
	return m_image->height();
}

const std::map<std::string, P(Sprite)>& SpriteSheet::getSprites() const
{
	return m_sprites;
}

}