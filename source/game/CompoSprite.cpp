#include <game/CompoSprite.h>
#include <lang/Log.h>
#include <lang/Format.h>
#include <math/Transform.h>

using namespace lang;
using namespace gr;
using namespace math;

namespace game
{

void CompoSprite::addSprite(const std::string& spriteId, float x, float y, Sprite* sprite) //17
{
    unsigned int numSprites = getSpriteCount(); //19
    const std::string& entryName = spriteId; //20

    Entry* entry = new Entry(); //22
    entry->m_spriteEntryName = entryName; //23
    entry->m_sprite = sprite;
    entry->m_pos = float2(x, y);
    entry->m_flip = float2(x, y);
    entry->m_angle = 0.0f;
    entry->m_visible = true;

    m_sprites.push_back(entry); //30

    m_namedSprites[spriteId] = entry; //32

    calculateBounds(); //34
}

void CompoSprite::addSprite(const std::string& spriteId, //37 | ?
    const std::string& spriteCompoId, //38
    Sprite* sprite, //39
    const float2& pos, //40
    const float2& scale, //41
    const float2& flip, //42
    float angle) //43
{
    unsigned int numSprites = getSpriteCount(); //45
    const std::string& entryName = spriteCompoId.length() ? Format("{0}#{1}", entryName, spriteCompoId).format() : spriteId; //46

    Entry* entry = new Entry(); //52
    entry->m_spriteEntryName = entryName;
    entry->m_sprite = sprite;
    entry->m_pos = pos;
    entry->m_scale = scale;
    entry->m_flip = flip;
    entry->m_angle = angle;
    entry->m_visible = true;
    m_sprites.push_back(entry); //60

    m_namedSprites[entryName] = entry; //62
}

void CompoSprite::removeSprite(int index) //TODO
{
    /*m_sprites.erase(index + m_sprites.begin());
    m_namedSprites.erase(m_sprites[index]->m_spriteEntryName); //?
    calculateBounds();*/
    assert("void game::CompoSprite::removeSprite(int index) was not yet decompiled.");
}

void CompoSprite::removeSprite(const std::string& id) //TODO
{
    /*m_namedSprites.erase(id);
    calculateBounds();*/
    assert("void game::CompoSprite::removeSprite(const std::string& id) was not yet decompiled.");
}

void CompoSprite::replaceSprite(const std::string& spriteIdOld, const std::string& spriteIdNew, Sprite* sprite) //89-98
{
    m_namedSprites[spriteIdNew] = m_namedSprites[spriteIdOld]; //91
    m_namedSprites[spriteIdNew]->m_spriteEntryName = spriteIdNew; //92
    m_namedSprites[spriteIdNew]->m_sprite = sprite; //93

    m_namedSprites.erase(spriteIdOld); //95

    calculateBounds(); //97
}

void CompoSprite::draw(Context* context, float x, float y, Anchor anchor) //100 | TODO
{
    /*float2 vertpos[3] = { {0.0, 0.0}, {}, {} }; //134
    const RenderState2D state = context->getRenderState2D();
    state.resetTransform();
    Transform M = state.getTransform(); //143
    //state.resetTransform(); //144

    float2 sc = M.getScale2D(); //146
    float2 pos = M.getTranslation2D(); //147
    for (std::vector<P(Entry)>::iterator it = m_sprites.begin(); it != m_sprites.end(); it++); //149
    {
        P(Entry) entry = *it; //151
        float2 epiv; //159
        Transform T_1; //162
        Transform T; //163
        .setRotation(entry->m_angle); //164
        //f2 * //165
        .setTranslation(entry->m_pos); //166
        //f2 + //169
    }*/

    assert("void game::CompoSprite::draw(gr::Context* context, float x, float y, Anchor anchor) was not yet decompiled.");
}

void CompoSprite::calculateBounds() //-226 | TODO
{
    /*int x0; //180
    int y0; //181
    int x1; //182
    int y1; //183
    float2 vertpos[] = { { 0.0 } }; //185

    for (std::vector<P(Entry)>::iterator it = m_sprites.begin(); it != m_sprites.end(); it++) //191
    {
        P(Entry) entry = *it; //193
        if (!entry->m_visible) //194
            return;

        Transform T_1; //202
        Transform T; //203
        .setRotation(); //204
        float2 * //205
        float2 t2; //206

        float2 + .getTranslation2D //208

        for (int i = 0; i < sizeof(vertpos); i++) //210
        {
            float3 v; //212 transform ?
            
            min( //214
            min( //215

            max( //216

            max( //218
        }
    }

    m_width = ;
    m_height = ;
    m_pivotX = ;
    m_pivotY = ; //225 */

    assert("void game::CompoSprite::calculateBounds() was not yet decompiled.");
}

CompoSprite::Entry& CompoSprite::getSpriteEntry(int index) //228
{
    return *m_sprites[index]; //230
}

CompoSprite::Entry& CompoSprite::getSpriteEntry(const std::string& spriteId) //233
{
    if (!&m_namedSprites.find(spriteId)) //235
        LANG_LOG("", LANG_LOG_PRIORITY_ERROR, "Composite part(%s) not found!", spriteId); //237

    return *m_namedSprites[spriteId]; //240
}

int CompoSprite::getSpriteCount() const //243-246
{
    return m_sprites.size(); //245
}

int CompoSprite::getWidth() const //248-251
{
    return m_width; //250
}

int CompoSprite::getHeight() const //253-256
{
    return m_height; //255
}

int CompoSprite::getPivotX() const //258-261
{
    return m_pivotX; //260
}

int CompoSprite::getPivotY() const //263-266
{
    return m_pivotY; //265
}

}