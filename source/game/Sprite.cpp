#include <game/Sprite.h>
#include <game/SpriteSheet.h>
#include <gr/Context.h>
#include <gr/Image.h>

using namespace gr;
using namespace math;

namespace game
{

Sprite::Sprite(SpriteSheet* sheet, const std::string& name, int x, int y, int width, int height, short pivotX, short pivotY, SourceRotation rotation)
{
    m_sheet = sheet;
    m_name = name;
    m_x = x;
    m_y = y;
    m_width = width;
    m_height = height;
    m_pivotX = pivotX;
    m_pivotY = pivotY;

    if (!sheet->getImage())
        return;

    //if (!sheet->getImage()->)
    //    return;

    float texWidth = sheet->getImage()->width();

    int rotSizeX;
    int rotSizeY;

    float texHeight;

    float texXStart;
    float texYStart;

    float texXEnd;
    float texYEnd;
}

void Sprite::draw(Context* context, float x, float y, Anchor anchor) const
{
    //Todo
    //m_pivotX = m_width >> 1;
    //m_sheet->getImage()->draw(context, )
};

void Sprite::draw(Context* context, const Transform& tm, const float2* corners, Shader* shader) const
{
    draw(context, tm, corners, shader, 0);
};

void Sprite::draw(Context* context, const Transform& tm, const float2* corners, Shader* shader, float4* vertexColors) const
{
    /*float3 corners(*corners, 1.0);
    //Todo
    if (tm.m_mode)
        tm->m_tm(corners);*/
    //m_sheet->getImage()->draw(context, )
};

SpriteSheet* Sprite::getSheet() const
{
    return m_sheet;
};

const std::string& Sprite::getName() const
{
    return m_name;
}

int Sprite::getWidth() const
{
    return m_width;
}

int Sprite::getHeight() const
{
    return m_height;
}

int Sprite::getPivotX() const
{
    return m_pivotX;
};

int Sprite::getPivotY() const
{
    return m_pivotY;
};

int Sprite::getPositionInSheetX() const
{
    return m_x;
};

int Sprite::getPositionInSheetY() const
{
    return m_y;
};

}