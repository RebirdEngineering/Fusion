#include <game/BitmapFont.h>
#include <game/SpriteSheet.h>
#include <io/BundleInputStream.h>
#include <io/ByteArrayInputStream.h>
#include <io/DataInputStream.h>
#include <io/PathName.h>
#include <io/IOException.h>
#include <gr/Context.h>
#include <lang/Math.h>

using namespace gr;
using namespace lang;
using namespace io;

namespace game
{

BitmapFont::BitmapFont(Context* context, const std::string& filename) //25-33
{
    m_maxAscending = 0; //27
    m_maxDescending = 0; //28
    BundleInputStream in(filename); //29
    ByteArrayInputStream bytein(0, in.available()); //30
    in.read(bytein.data(), bytein.available()); //31
    load(context, bytein, true, filename); //32
}

BitmapFont::BitmapFont(Context* context, InputStream& dat, InputStream& image) //35-41
{
    m_maxAscending = 0; //36
    m_maxDescending = 0; //37
    m_sheet = new SpriteSheet(context->createImage(dat, image.toString())); //38
    load(context, dat, false, ""); //39
}

void BitmapFont::load(Context* context, InputStream& dat, bool loadsheet, const std::string& filename) //43-111
{
    DataInputStream dis(dat); //45

    unsigned int chunkID = dis.readInt(); //48
    if (chunkID == 'KA3D') //49
    {
        unsigned int chunkSize = dis.readInt(); //51
        if (chunkSize > dis.available())
            throwError(IOException(Format("Malformed KA3D file: {0}", dis.toString()))); //53

        while (dis.available() > 0) //56
        {
            unsigned int chunkID = dis.readInt(); //58
            unsigned int chunkSize = dis.readInt(); //59

            if (chunkID == 'FONT') //61
            {
                unsigned int version = dis.readShort(); //65

                if ((version - 1) <= 1) //?
                {
                    const std::string imagePath = dis.readUTF(); //69
                    if (loadsheet)
                    {
                        PathName parentPath = PathName(filename).parent(); //72
                        std::string finalPath = PathName(imagePath).toString(); //73

                        m_sheet = new SpriteSheet(context->createImagefromBundle(finalPath)); //76
                    }

                    m_leading = dis.readShort(); //79
                    m_tracking = dis.readShort(); //80
                    int charCount = dis.readShort(); //81

                    for (int i = 0; i < charCount; i++) //83
                    {
                        int charCode = version == 1 ? dis.readInt() : dis.readShort(); //86 | A downgrade?
                        int x = dis.readShort(); //87
                        int y = dis.readShort(); //88
                        int width = dis.readShort(); //80
                        int height = dis.readShort(); //90
                        int baseline = dis.readShort(); //91

                        m_maxAscending = Math::max(m_maxAscending, baseline); //93
                        m_maxDescending = Math::max(m_maxDescending, height - baseline); //94

                        m_glyphs[i]->getSheet()->createSprite(string::to_string(charCode), x, y, width, height, 0, baseline, Sprite::ROTATION_NONE); //96
                    }
                }
            }

            else
                dis.skip(chunkSize); //105
        }
    }
}

BitmapFont::~BitmapFont() //112-115
{
    m_glyphs.clear(); //114
}

void BitmapFont::drawString(Context* context, const std::string& str, float y, float x, Anchor anchor) const //117-120
{
    drawString(context, str, 0, -1, y, x, anchor);
}

void BitmapFont::drawString(Context* context, const std::string& str, int offset, int length, float x, float y, Anchor anchor) const //122
{
    if (str.empty()) //125
        return;

    lang::u32string unicode = lang::string::toUTF32string(str); //129
    int size = unicode.size(); //130

    if (size < offset)
        offset = size;
    if (offset + length > size)
        length = size - offset;

    drawString(context, unicode, size, length, x, y, anchor); //140
}

void BitmapFont::drawString(Context* context, const lang::u32string& str, int offset, int length, float x, float y, Anchor anchor) const //143 | TODO
{
    /*switch (anchor.v)
    {
    case Anchor::BOTTOM: y -= m_maxDescending; break;
    case Anchor::VCENTER: y -= m_maxDescending; break;
    case Anchor::TOP: y += m_maxDescending; break;
    }
    switch (anchor.h)
    {
    case Anchor::RIGHT: break;
    case Anchor::HCENTER: break;
    }
    //assert(str.c_str()); //assert str
    //getStringWidth(str, offset, length); //155
    
    //getStringWidth(str, offset, length); //157
    //const bool hasRenderer = m_renderer; //159 | ?
    
     //.empty

    //= getStringWidth(str, offset, length);
    // //int i; //162
    //const std::map<int, Sprite*>::const_iterator& it = m_glyphs.find(offset); //164
    //Sprite* sprite = it->second; //167

    //m_renderer(context, sprite, x, y); //170*/
}

std::string BitmapFont::filter(const std::string& str) const //185-199 | TODO
{
    /*lang::u32string unicode = lang::string::toUTF32string(str); //188
    //if (unicode.empty())

    lang::u32string filtered = lang::string::toUTF32string(str); //191

    for (size_t i = 0; i < m_glyphs.size(); i++) //193
    {
        if (&m_glyphs.find(i)) //195
            filtered = m_glyphs[i];
    }

    return lang::string::toUTF8string(filtered); //199*/
    lang::u32string filtered = lang::string::toUTF32string(str);
    return string::toUTF8string(filtered);
}

bool BitmapFont::isCharacterSupported(int character) const //202
{
    return &m_glyphs.find(character); //204
}

int BitmapFont::getStringWidth(const std::string& str, int offset, int length) const //207 | TODO
{
    /*if (str.empty()) //210
        return 0;

    lang::u32string unicode = lang::string::toUTF32string(str); //214
    int size = unicode.length(); //215

    return getStringWidth(unicode, offset, size); //225*/

    assert("int BitmapFont::getStringWidth(const std::string& str, int offset, int length) const was not yet decompiled. Returning 0.");
    return 0; //225
}

int BitmapFont::getStringWidth(const lang::u32string& str, int offset, int length) const //228 | TODO
{
    /*assert(str.c_str()); //Recreation
    int size = str.size(); //234

    int width; //244
    for (int i = 0; i < ?; i++) //246
    {
        std::map<int, Sprite*>::const_iterator it = m_glyphs.find(i); //248
        it->second->getWidth();
        if (> width)
            width += ?;
    }
    return width;*/

    assert("int BitmapFont::getStringWidth(const lang::u32string& str, int offset, int length) const was not yet decompiled. Returning 0.");
    return 0;
}

int BitmapFont::getStringHeight(const std::string& str, int offset, int length) const //259-278 | TODO
{
    /*if (str.empty()) //262
        return 0;

    lang::u32string unicode = lang::string::toUTF32string(str); //266
    int size = unicode.length(); //267

    return getStringHeight(unicode, offset, size); //277*/

    assert("int BitmapFont::getStringHeight(const std::string& str, int offset, int length) const was not yet decompiled. Returning 0.");
    return 0;
}

int BitmapFont::getStringHeight(const lang::u32string& str, int offset, int length) const //280 | TODO
{
    /*//assert(str.c_str());
    int size = str.size(); //286
    int height; //296
    for (int i = 0; i < size; i++) //298
    {
        const std::map<int, Sprite*>::iterator& it = m_glyphs.find(i); //300
        int glyphHeight = it->second->getHeight(); //303
        if (glyphHeight > height)
            height += glyphHeight;
    }
    return height;*/

    assert("int BitmapFont::getStringHeight(const lang::u32string& str, int offset, int length) const was not yet decompiled. Returning 0.");
    return 0;
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

Rect BitmapFont::getBounds(const std::string& str, Anchor anchor, int offset, int length) const //337 | TODO
{
    /*int x; //339
    int y; //340
    int width = getStringWidth(str, offset, length); //341
    int height = getStringHeight(str, offset, length); //342
    switch (anchor.h)
    {
    case Anchor::HCENTER: this->m_maxAscending - ((this->m_maxAscending + this->m_maxDescending) >> 1); break;
    case Anchor::RIGHT: x -= width; break;
    }

    y = - getMaxPivotY(string::toUTF32string(str), offset, length); //370
    return Rect(x, y, x + height, y + height); //371*/

    assert("Rect BitmapFont::getBounds(const std::string& str, Anchor anchor, int offset, int length) const was not yet decompiled. Returning blank rect.");
    return Rect();
}

int BitmapFont::getMaxPivotY(const lang::u32string& str, int offset, int length) const //374 | TODO
{
    /*if (str.empty())
        return 0;

    int size = str.size(); //380

    int maxPivotY = 0; //390

    for (int i = 0; i < size; i++) //392
    {
        std::map<int, Sprite*>::const_iterator it = m_glyphs.find(i); //m_glyphs.find() //394
        if (it->first == i)
        {
            int pivotY = it->second->getPivotY(); //397

            if (pivotY > maxPivotY)
                pivotY += maxPivotY; //?
        }
    }

    return maxPivotY;*/

    assert("int BitmapFont::getMaxPivotY(const lang::u32string& str, int offset, int length) const was not yet decompiled. Returning 0.");
    return 0;
}

void BitmapFont::setGlyphRenderer(const std::function<void(Context*, Sprite*, float, float)>& renderer) //406
{
    m_renderer = renderer;
}

}