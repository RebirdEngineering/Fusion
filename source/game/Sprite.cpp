#include <game/Sprite.h>
#include <game/SpriteSheet.h>
#include <gr/Context.h>
#include <gr/Image.h>

using namespace gr;
using namespace math;

namespace game
{

Sprite::Sprite(SpriteSheet* sheet, const std::string& name, int x, int y, int width, int height, short pivotX, short pivotY, SourceRotation rotation) : //13-71 | TODO
    m_sheet(sheet),
    m_name(name),
    m_x(x),
    m_y(y),
    m_width(width),
    m_height(height),
    m_pivotX(pivotX),
    m_pivotY(pivotY)
{
    /*if (!sheet->getImage() || !sheet->getImage()->getTexture())
        return;

    float texWidth = sheet->getImage()->width(); //26
    float texHeight = sheet->getImage()->height(); //27

    float texXStart = x / texWidth; //29
    float texYStart = y / texHeight; //30

    int rotSizeX = (height + x) / texWidth; //31
    int rotSizeY = (width + y) / texHeight; //32
    if (rotation == ROTATION_CW_90_DEGREES) //33
    {
        texWidth = height;
        texHeight = width;
    }

    float texXEnd = height + x; //39
    float texYEnd = width + y; //40

    //float2 //44
    //float2 //51

    switch (rotation)
    {
    //case ROTATION_CW_90_DEGREES: m_UVs[0] = float2(rotSizeX, texYStart); m_UVs[1] = float2(rotSizeX, rotSizeY); m_UVs[2] = float2(texXStart, texYStart); m_UVs[3] = float2(texXStart, rotSizeY); break;
    //case FLIP_HORIZONTAL: m_UVs[0] = float2(texXEnd, texYStart); m_UVs[1] = float2(texXStart, texYStart); m_UVs[2] = float2(texXEnd, texYEnd); m_UVs[3] = float2(texXStart, texYEnd); break;
    //case FLIP_VERTICAL: m_UVs[0] = float2(texYEnd, texXEnd); m_UVs[1] = float2(texYEnd, texXStart); m_UVs[2] = float2(texXEnd, texYEnd); m_UVs[3] = float2(texXStart, texYEnd); break;
    }*/
    assert("game::Sprite::Sprite(game::SpriteSheet* sheet, const std::string& name, int x, int y, int width, int height, short pivotX, short pivotY, game::Sprite::SourceRotation rotation) was not yet decompiled.");
}

void Sprite::draw(Context* context, float x, float y, Anchor anchor) const //73
{
    //m_sheet->getImage()->draw(context, x, y, m_width, m_height, m_UVs);
};

void Sprite::draw(Context* context, const Transform& tm, const float2* corners, Shader* shader) const //151
{
    draw(context, tm, corners, shader, 0);
};

void Sprite::draw(Context* context, const Transform& tm, const float2* corners, Shader* shader, float4* vertexColors) const //156
{
    //?

    float3 verts[4]; //160
    tm.transform(verts[0]); //161
    tm.transform(verts[1]); //162
    tm.transform(verts[2]); //163
    tm.transform(verts[3]); //164
    m_sheet->getImage()->draw(context, (float3*)corners, m_UVs, shader); //165 | Correct?
};

SpriteSheet* Sprite::getSheet() const //170
{
    return m_sheet;
};

const std::string& Sprite::getName() const //180
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

int Sprite::getPivotX() const //180
{
    return m_pivotX;
};

int Sprite::getPivotY() const //190
{
    return m_pivotY;
};

int Sprite::getPositionInSheetX() const //200
{
    return m_x;
};

int Sprite::getPositionInSheetY() const //205
{
    return m_y;
};

}