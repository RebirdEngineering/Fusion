#include <game/BitmapFont.h>
#include <game/SpriteSheet.h>
#include <io/BundleInputStream.h>
#include <io/ByteArrayInputStream.h>
#include <io/DataInputStream.h>
#include <io/PathName.h>
#include <io/IOException.h>
#include <gr/Context.h>

using namespace gr;
using namespace lang;
using namespace io;

namespace game
{

BitmapFont::BitmapFont(Context* context, const std::string& filename) //[TODO]
{
    m_sheet = 0;
    m_maxAscending = 0;
    m_maxDescending = 0;
    BundleInputStream in(filename);
    ByteArrayInputStream bytein(0, in.available());
    in.read(bytein.data(), bytein.available());
    load(context, bytein, true, filename);
}

BitmapFont::BitmapFont(Context* context, InputStream& dat, InputStream& image)
{
    m_sheet = new SpriteSheet(context->createImage(dat, image.toString()));
    load(context, dat, false, "");
}

void BitmapFont::load(Context* context, InputStream& dat, bool loadsheet, const std::string& filename)
{
    DataInputStream dis(dat); //45

    unsigned int chunkID = dis.readInt(); //48
    if (chunkID != 'KA3D')
        return;

    unsigned int chunkSize = dis.readInt(); //51
    if (chunkSize > dis.available())
        throwError(IOException(Format("Malformed KA3D file: {0}", dis.toString())));

    while (dis.available() > 0)
    {
        //
        unsigned int chunkID = dis.readInt(); //58
        unsigned int chunkSize = dis.readInt(); //59
        if (chunkID != 'FONT')
            dis.skip(chunkSize);
        else
        {
            //
            unsigned int version = dis.readShort(); //65
            if (version <= 1)
                break;

            const std::string imagePath = dis.readUTF(); //69
            if (loadsheet)
            {
                PathName parentPath = PathName(filename).parent();
                std::string finalPath = PathName(imagePath).toString(); //?
                m_sheet = new SpriteSheet(context->createImagefromBundle(finalPath));
            }
            m_leading = dis.readShort();
            m_tracking = dis.readShort();
            int charCount = dis.readShort();
            if (charCount <= 1)
                break;
            for (int i = 0; i < charCount; i++)
            {
                int charCode = version == 1 ? dis.readInt() : dis.readShort(); //A downgrade?

                int x = dis.readShort();
                int y = dis.readShort();
                int width = dis.readShort();
                int height = dis.readShort();
                int baseline = dis.readShort();

                if (m_maxAscending < baseline)
                    m_maxAscending = baseline;
                if (m_maxDescending < height - baseline)
                    m_maxDescending = height - baseline;

                m_glyphs[i]->getSheet()->createSprite(string::to_string(charCode), x, y, width, height, 0, baseline, Sprite::ROTATION_NONE);
            }
        }
    }
}

BitmapFont::~BitmapFont()
{
}

void BitmapFont::drawString(Context* context, const std::string& str, float y, float x, Anchor anchor) const
{
    drawString(context, str, 0, -1, y, x, anchor);
}

void BitmapFont::drawString(Context* context, const std::string& str, int offset, int length, float x, float y, Anchor anchor) const
{
    if (str.empty())
        return;

    lang::u32string unicode = lang::string::toUTF32string(str);
    int size = unicode.size();

    //?
    if (size < offset)
        offset = size;
    if (offset + length > size)
        length = size - offset;
    //?

    drawString(context, unicode, size, length, x, y, anchor);
}

void BitmapFont::drawString(Context* context, const lang::u32string& str, int offset, int length, float x, float y, Anchor anchor) const //TODO
{
    //assert(str.c_str()); //assert str
    //getStringWidth(str, offset, length);
    //const bool hasRenderer = true; //?
    
     //.empty

    //= getStringWidth(str, offset, length);
    //const std::map<int, Sprite*>::iterator& it = m_glyphs.find(offset);
    //int i;
    //width
    //Sprite* sprite;
}

std::string BitmapFont::filter(const std::string& str) const
{
    lang::u32string unicode = lang::string::toUTF32string(str); //188

    lang::u32string filtered = lang::string::toUTF32string(str); //191

    size_t i; //193

    //m_glyphs.find()

    return lang::string::toUTF8string(filtered);
}

bool BitmapFont::isCharacterSupported(int character) const //?
{
    while (m_glyphs.begin() != m_glyphs.end())
    {
        if (&m_glyphs.find(character))
            return true;
    }
}

int BitmapFont::getStringWidth(const std::string& str, int offset, int length) const
{
    lang::u32string unicode = lang::string::toUTF32string(str);
    int size = unicode.length();
    if (str.empty())
        //assert(str);
        return 0;
    return getStringWidth(unicode, offset, size);
}

int BitmapFont::getStringWidth(const lang::u32string& str, int offset, int length) const
{
    int i;
    int width;
    //assert(str);
    return width;
}

int BitmapFont::getStringHeight(const std::string& str, int offset, int length) const
{
    lang::u32string unicode = lang::string::toUTF32string(str);
    int size = unicode.length();
    if (str.empty())
        //assert(str);
        return 0;
    return getStringHeight(unicode, offset, size);
}

int BitmapFont::getStringHeight(const lang::u32string& str, int offset, int length) const
{
    int i;
    int height;
    //const std::map<int, Sprite*>::iterator& it = m_glyphs.find(i, );
    {
        int glyphHeight;
        {
            int height;
        }
    }
    return i;
}

int BitmapFont::getMaxAscending() const
{
    return m_maxAscending;
}

int BitmapFont::getMaxDescending() const
{
    return m_maxDescending;
}

int BitmapFont::getHeight() const
{
    return m_maxAscending + m_maxDescending;
}

int BitmapFont::getLeading() const
{
    return m_leading;
}

int BitmapFont::getTracking() const
{
    return m_tracking;
}

Rect BitmapFont::getBounds(const std::string& str, Anchor anchor, int offset, int length) const
{
    int x = getStringWidth(str, offset, length);
    int y;

    int width;
    int height;

    //getMaxPivotY();

    str.empty();
    //m_glyphs.find()
    return Rect(0, 0);
}

int BitmapFont::getMaxPivotY(const u32string& str, int offset, int length) const
{
    int size;
    int i;
    //std::map<int, Sprite*>& it;
    {
        int maxPivotY;
        int pivotY;
    }
    return 0;
}

void BitmapFont::setGlyphRenderer(const std::function<void(Context*, Sprite*, float, float)>& renderer)
{
    m_renderer = renderer;
}

}