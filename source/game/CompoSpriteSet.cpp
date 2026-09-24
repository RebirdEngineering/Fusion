#include <game/CompoSpriteSet.h>
#include <game/CompoSprite.h>

namespace game
{

CompoSpriteSet::CompoSpriteSet()
{
    //assert(sp);
}

void CompoSpriteSet::add(const std::string& id, CompoSprite* compo)
{
    m_composites[id] = compo;
}

CompoSprite* CompoSpriteSet::getCompoSprite(const std::string& id) const //Unknown where this is.
{
    return m_composites.find(id)->second;
}

void CompoSpriteSet::removeSprite(const std::string& id) //Unknown where this is.
{
    m_composites.erase(id);
}

}