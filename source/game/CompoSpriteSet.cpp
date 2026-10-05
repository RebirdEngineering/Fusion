#include <game/CompoSpriteSet.h>
#include <game/CompoSprite.h>

namespace game
{

CompoSpriteSet::CompoSpriteSet()
{
    //assert(sp);
}

void CompoSpriteSet::add(const std::string& id, CompoSprite* compo) //17
{
    m_composites[id] = compo; //19
}

CompoSprite* CompoSpriteSet::getCompoSprite(const std::string& id) const //Unknown where this is.
{
    return m_composites.find(id)->second;
}

void CompoSpriteSet::removeSprite(const std::string& id) //Unknown where this is.
{
    m_composites.erase(id);
}

const std::map<std::string, P(CompoSprite)>& CompoSpriteSet::getCompoSprites() const
{
    return m_composites;
}

}