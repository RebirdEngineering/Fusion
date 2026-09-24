#include <game/CompoSprite.h>
#include <lang/Log.h>
#include <lang/Format.h>

using namespace lang;
using namespace gr;
using namespace math;

namespace game
{

void CompoSprite::addSprite(const std::string& spriteId, float x, float y, Sprite* sprite)
{
    unsigned int numSprites = getSpriteCount();
    const std::string& entryName = spriteId;

    Entry* entry = new Entry();
    
    entry->m_spriteEntryName = entryName;
    entry->m_sprite = sprite;
    entry->m_pos.x = x;
    entry->m_pos.y = y;
    entry->m_flip.x = x;
    entry->m_flip.y = y;
    entry->m_angle = 0.0f;
    entry->m_visible = true;
    m_sprites.push_back(entry);
    m_namedSprites[spriteId] = entry;
    calculateBounds();
}

void CompoSprite::addSprite(const std::string& spriteId, const std::string& spriteCompoId, Sprite* sprite, const float2& pos, const float2& scale, const float2& flip, float angle) //?
{
    unsigned int numSprites = getSpriteCount();
    const std::string& entryName = spriteCompoId.empty() ? Format("{0}#{1}", entryName, spriteCompoId).format() : spriteId;
    Entry* entry = new Entry();
    entry->m_spriteEntryName = entryName;
    entry->m_sprite = sprite;
    entry->m_pos = pos;
    entry->m_scale = scale;
    entry->m_flip = flip;
    entry->m_angle = angle;
    entry->m_visible = true;
    m_sprites.push_back(entry);
    m_namedSprites[entryName] = entry;
}

void CompoSprite::removeSprite(int index)
{
    //m_sprites.erase(); //?
    //m_namedSprites.erase();
    calculateBounds();
}

void CompoSprite::removeSprite(const std::string& id)
{
    //for (std::map<std::string, P(Sprite)>::const_iterator it = m_sprites.begin(); it != m_sprites.end(); it++);
        //m_sprites.erase(it->second);
    m_namedSprites.erase(id);
    calculateBounds();
}

void CompoSprite::replaceSprite(const std::string& spriteIdOld, const std::string& spriteIdNew, Sprite* sprite)
{
    m_namedSprites[spriteIdNew] = m_namedSprites[spriteIdOld];
    m_namedSprites[spriteIdNew]->m_spriteEntryName = spriteIdNew;
    m_namedSprites[spriteIdNew]->m_sprite = sprite;
    m_namedSprites.erase(m_namedSprites.equal_range(spriteIdOld).first, m_namedSprites.equal_range(spriteIdOld).second); //?
    calculateBounds();
}

void CompoSprite::draw(Context* context, float x, float y, Anchor anchor)
{
    /*float2 vertpos[3] = { {}, {}, {} };
    const RenderState2D state;
    state.resetTransform();
    Transform M = state.getTransform();
    //state.resetTransform();
    float2 sc = M.getScale2D();
    float2 pos;
    for (std::vector<P(Entry)>::iterator it = m_sprites.begin(); it != m_sprites.end(); it++);
    {
        P(Entry) entry;
        Transform T_1;
        Transform T;
        float2 epiv;
        //epiv + 
    }
    P(Entry) entry;

    getTranslation2D

    context->*/
}

void CompoSprite::calculateBounds()
{
    /*int x0;
    int y0;
    int x1;
    int y1;
    float2 vertpos[] = { {} };
    for (std::vector<P(Entry)>::iterator it = m_sprites.begin(); it != m_sprites.end(); it++)
    {
        P(Entry) entry = it->ptr();
        if (!entry->m_visible)
            return;
    }

    m_width = ;
    m_height = ;
    m_pivotX = ;
    m_pivotY = ;*/
}

CompoSprite::Entry& CompoSprite::getSpriteEntry(int index)
{
    return *m_sprites[index];
}

CompoSprite::Entry& CompoSprite::getSpriteEntry(const std::string& spriteId)
{
    if (!&m_namedSprites.find(spriteId))
        LANG_LOG("", LANG_LOG_PRIORITY_ERROR, "Composite part(%s) not found!", spriteId); //237
    return *m_namedSprites[spriteId];
}

int CompoSprite::getSpriteCount() const
{
    return m_sprites.size();
}

int CompoSprite::getWidth() const
{
    return m_width;
}

int CompoSprite::getHeight() const
{
    return m_height;
}

int CompoSprite::getPivotX() const
{
    return m_pivotX;
}

int CompoSprite::getPivotY() const
{
    return m_pivotY;
}

}