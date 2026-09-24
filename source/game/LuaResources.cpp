#include <game/LuaResources.h>
#include <game/SystemFont.h>
#include <game/CompoSprite.h>
#include <pf/Launcher.h>
#include <lang/Log.h>
#include <audio/AudioOutput.h>
#include <audio/AudioClip.h>

using namespace audio;
using namespace gr;
using namespace lua;
using namespace pf;

namespace game
{

LuaResources::LuaResources(LuaState* lua, Context* context) : //12 | They must've included very little then... | TODO
    LuaObject(lua),
    m_resources(context)
{
    registerMethod("setPath", this, &LuaResources::setPath);
    registerLuaMethod("createSpriteSheet", this, &LuaResources::createSpriteSheet);
    registerLuaMethod("createCompoSpriteSet", this, &LuaResources::createCompoSpriteSet);
    registerLuaMethod("createBitmapFont", this, &LuaResources::createBitmapFont);
    registerLuaMethod("createSystemFont", this, &LuaResources::createSystemFont);
    registerLuaMethod("createTextGroupSet", this, &LuaResources::createTextGroupSet);
    //registerMethod("createAudioOutput", this, &LuaResources::createAudioOutput); //CHECK LuaObject.inl?
    //registerMethod("createAudioInput", this, &LuaResources::createAudioInput); //CHECK LuaObject.inl
    registerLuaMethod("createAudio", this, &LuaResources::createAudio);
    registerMethod("createCompositeAudio", this, &LuaResources::createCompositeAudio);
    registerMethod("captureSprite", this, &LuaResources::captureSprite);
    registerLuaMethod("releaseSpriteSheet", this, &LuaResources::releaseSpriteSheet);
    registerMethod("releaseCompoSpriteSet", this, &LuaResources::releaseCompoSpriteSet);
    registerMethod("releaseFont", this, &LuaResources::releaseFont);
    registerMethod("releaseTextGroupSet", this, &LuaResources::releaseTextGroupSet);
    registerLuaMethod("releaseAudio", this, &LuaResources::releaseAudio);
    registerMethod("loadLocale", this, &LuaResources::loadLocale);
    registerMethod("useLocale", this, &LuaResources::useLocale);
    registerMethod("useFont", this, &LuaResources::useFont);
    registerMethod("getAvailableSystemFonts", this, &LuaResources::getAvailableSystemFonts);
    registerLuaMethod("drawSprite", this, &LuaResources::drawSprite);
    registerLuaMethod("drawCompoSprite", this, &LuaResources::drawCompoSprite);
    registerLuaMethod("drawString", this, &LuaResources::drawString);
    //registerMethod("setClipRect", this, &LuaResources::setClipRect); //CHECK LuaObject.inl
    registerLuaMethod("getClipRect", this, &LuaResources::getClipRect);
    registerMethod("getString", this, &LuaResources::getString);
    registerLuaMethod("playAudio", this, &LuaResources::playAudio);
    registerLuaMethod("stopAudio", this, &LuaResources::stopAudio);
    registerMethod("stopAllAudio", this, &LuaResources::stopAllAudio);
    registerLuaMethod("isAudioPlaying", this, &LuaResources::isAudioPlaying);
    registerLuaMethod("getSpriteBounds", this, &LuaResources::getSpriteBounds);
    registerLuaMethod("getSpritePivot", this, &LuaResources::getSpritePivot);
    registerLuaMethod("getCompoSpriteBounds", this, &LuaResources::getCompoSpriteBounds);
    registerLuaMethod("getCompoSpriteData", this, &LuaResources::getCompoSpriteData);
    registerLuaMethod("getCompoSpriteEntry", this, &LuaResources::getCompoSpriteEntry);
    registerLuaMethod("setCompoSpriteEntry", this, &LuaResources::setCompoSpriteEntry);
    registerMethod("getStringWidth", this, &LuaResources::getStringWidth);
    registerMethod("getFontMaxAscending", this, &LuaResources::getFontMaxAscending);
    registerMethod("getFontMaxDescending", this, &LuaResources::getFontMaxDescending);
    registerMethod("getFontLeading", this, &LuaResources::getFontLeading);
    registerMethod("getFontTracking", this, &LuaResources::getFontTracking);
    registerMethod("getFontHeight", this, &LuaResources::getFontHeight);
    registerMethod("getLocale", this, &LuaResources::getLocale);
    registerMethod("startAudioOutput", this, &LuaResources::startAudioOutput);
    registerMethod("stopAudioOutput", this, &LuaResources::stopAudioOutput);
    registerMethod("startAudioInput", this, &LuaResources::startAudioInput);
    registerMethod("stopAudioInput", this, &LuaResources::stopAudioInput);
    //registerMethod("setMasterVolume", this, &LuaResources::setMasterVolume);
    //registerMethod("setTrackVolume", this, &LuaResources::setTrackVolume);
    //registerMethod("getTrackVolume", this, &LuaResources::getTrackVolume);
    registerMethod("openURL", this, &LuaResources::openURL);
    lua->globals().setTable("res", this);
}

LuaResources::~LuaResources() //82
{
}

void LuaResources::setPath(std::string filename) //85
{
    m_resources.setPath(filename);
}

int LuaResources::createSpriteSheet(LuaState* lua) //90-100
{
    assert(lua->top() >= 1 && lua->top() <= 2); //Assert on line 96
    std::string filename = lua->toString(1); //94
    bool forceLoad = lua->isBoolean(2) ? lua->toBoolean(2) : false; //95
    bool loadImage = !lua->isBoolean(3) ? lua->toBoolean(3) : false; //96
    m_resources.createSpriteSheet(filename, forceLoad, loadImage);
    return 0;
}

int LuaResources::createCompoSpriteSet(LuaState* lua) //102-111
{
    assert(lua->top() >= 1 && lua->top() <= 2);
    std::string filename = lua->toString(1); //106
    bool forceLoad = lua->isBoolean(2) ? lua->toBoolean(2) : false; //107
    m_resources.createCompoSpriteSet(filename, forceLoad);
    return 0;
}

int LuaResources::createBitmapFont(LuaState* lua) //113-122
{
    assert(lua->top() >= 1 && lua->top() <= 2);
    std::string filename = lua->toString(1); //117
    bool forceLoad = lua->isBoolean(2) ? lua->toBoolean(2) : false; //118
    m_resources.createBitmapFont(filename, forceLoad);
    return 0;
}

int LuaResources::createSystemFont(LuaState* lua) //124-141
{
    assert(lua->top() >= 1 && lua->top() <= 2); //Assert on line 118
    std::string id = lua->toString(1); //128
    std::string fontName = lua->toString(2); //129
    int fontSize = lua->toNumber(3); //130
    int A = lua->toNumber(4); //131
    int R = lua->toNumber(5); //132
    int G = lua->toNumber(6); //133
    int B = lua->toNumber(7); //134
    unsigned int color = lua->toNumber(8); //135
    int style = lua->toNumber(9); //136
    bool forceLoad = lua->isBoolean(9) ? lua->toBoolean(9) : false; //137
    m_resources.createSystemFont(id, fontName, fontSize, Color(color), style, forceLoad);
    return 0;
}

int LuaResources::createTextGroupSet(LuaState* lua) //143-152
{
    assert(lua->top() >= 1 && lua->top() <= 2); //Assert on line 129
    std::string filename = lua->toString(1); //147
    bool forceLoad = lua->isBoolean(2) ? lua->toBoolean(2) : false; //148
    m_resources.createTextGroupSet(filename, forceLoad);
    return 0;
}

void LuaResources::captureSprite(std::string spriteId) //154
{
    m_resources.captureSprite(spriteId);
}

void LuaResources::createAudioOutput(float channels, float bitrate, float samplerate) //159
{
    AudioConfiguration conf(channels, bitrate, samplerate); //161
    m_resources.createAudioOutput(conf);
}

void LuaResources::createAudioInput(float channels, float bitrate, float samplerate) //165
{
    AudioConfiguration conf(channels, bitrate, samplerate); //167
    m_resources.createAudioInput(conf);
}

int LuaResources::createAudio(LuaState* lua) //171-179
{
    if (lua->top() < 3) //lua->top() < 3 ? m_resources.createAudio(lua->toString(1), lua->toString(2), true) : m_resources.createAudio(lua->toString(1), lua->toString(2), lua->toBoolean(3));
        m_resources.createAudio(lua->toString(1), lua->toString(2), true);
    else
        m_resources.createAudio(lua->toString(1), lua->toString(2), lua->toBoolean(3));
    
    return 0;
}

void LuaResources::createCompositeAudio(std::string id, LuaTable clipids) //181-193 | ?
{
    std::vector<P(AudioClip)> clips; //183

    for (int i = 0; clipids.isString(i); i++) //185
    {
        AudioClip* clip = m_resources.getAudioClip(clipids.getString(i)); //187
        clips.push_back(clip);
    }

    m_resources.createCompositeAudio(id, clips);
}

int LuaResources::releaseSpriteSheet(LuaState* lua) //195-203
{
    if (lua->top() < 2) //lua->top() < 2 ? m_resources.releaseSpriteSheet(lua->toString(1)) : m_resources.releaseSpriteSheet(lua->toString(1), lua->toBoolean(2));
        m_resources.releaseSpriteSheet(lua->toString(1));
    else
        m_resources.releaseSpriteSheet(lua->toString(1), lua->toBoolean(2));
    
    return 0;
}

void LuaResources::releaseCompoSpriteSet(std::string filename) //205
{
    m_resources.releaseCompoSpriteSet(filename);
}

void LuaResources::releaseFont(std::string filename) //210
{
    m_resources.releaseFont(filename);
}

void LuaResources::releaseTextGroupSet(std::string filename) //215
{
    m_resources.releaseTextGroupSet(filename);
}

int LuaResources::releaseAudio(LuaState* lua) //220-224
{
    m_resources.releaseAudio(lua->toString(1));
    return 0;
}

void LuaResources::loadLocale(std::string textGroupSet, std::string locale) //226 | DarkestFear
{
    m_resources.loadLocale(textGroupSet, locale);
}

void LuaResources::useLocale(std::string locale) //231
{
    m_resources.useLocale(locale);
}

std::string LuaResources::getLocale()
{
    return m_resources.getLocale();
}

void LuaResources::useFont(std::string fontName) //241
{
    m_resources.useFont(fontName);
}

LuaTable LuaResources::getAvailableSystemFonts() //ABSW 1.1.0+
{
    LuaTable fonts(luaState()); //248
    const std::vector<std::string>& names = SystemFont::getAvailableFontNames(); //249
    for (size_t i = 0; i < names.size(); i += 4) //250
        fonts.setString(i, names[i]);

    return fonts;
}

int LuaResources::drawSprite(LuaState* lua) //257-318
{
    bool useNewImpl = lua->isNumber(2); //259

    if (useNewImpl)
    {
        int count = lua->top(); //263
        assert(count >= 4 && count <= 8); //205

        std::string spriteId = lua->toString(1); //266
        float x = lua->toNumber(2); //267
        float y = lua->toNumber(3); //268

        Anchor anchor(Anchor::VPIVOT, Anchor::HPIVOT); //270
        anchor.fromString(lua->toString(4));
        anchor.fromString(lua->toString(5));

        float width = lua->toNumber(6); //274
        float height = lua->toNumber(7); //275 | 0.0?

        if (count >= 4 && count > 4 && count > 6)
            m_resources.drawSprite(spriteId, x, y, width, height, anchor);
        else
            m_resources.drawSprite(spriteId, x, y, anchor);
    }
    else
    {
        int count = lua->top(); //290
        assert(count >= 4 && count <= 8); //
        std::string spriteId = lua->toString(2); //293

        float x = lua->toNumber(3); //295
        float y = lua->toNumber(4); //296

        Anchor anchor(Anchor::VPIVOT, Anchor::HPIVOT); //298

        anchor.fromString(lua->toString(5));

        float width = lua->toNumber(7); //302
        float height = lua->toNumber(8); //303 | 0?

        if (count >= 5)
            m_resources.drawSprite(spriteId, x, y, anchor);
        else
            m_resources.drawSprite(spriteId, x, y, width, height, anchor);
    }
    return 0;
}

int LuaResources::drawCompoSprite(LuaState* lua) //320
{
    return drawSprite(lua);
}

int LuaResources::drawString(LuaState* lua) //325-342
{
    int count = lua->top(); //327
    assert(count >= 4 && count <= 6); //Line 268 | 288 on ABS 3.0.0 OSX

    std::string groupId = lua->toString(1); //330
    std::string textId = lua->toString(2); //331
    float x = lua->toNumber(3); //332
    float y = lua->toNumber(4); //333

    Anchor anchor; //335

    if (count >= 5) anchor.fromString(lua->toString(5));
    if (count >= 6) anchor.fromString(lua->toString(6));

    m_resources.drawString(groupId, textId, x, y, anchor);
    return 0;
}

void LuaResources::setClipRect(float x, float y, float w, float h) //344
{
    Rect rect; //346
    rect.setLeft(x);
    rect.setRight(x + y);
    rect.setTop(w);
    rect.setBottom(w + h);
    m_resources.setClipRect(rect);
}

int LuaResources::getClipRect(LuaState* lua) //354 | Seasons 3.0.0 / Android Space 1.3.1+
{
    Rect clipRect = m_resources.getClipRect(); //356
    lua->pushNumber(clipRect.left());
    lua->pushNumber(clipRect.right());
    lua->pushNumber(clipRect.width()); //360
    lua->pushNumber(clipRect.height()); //361

    return 4;
}

std::string LuaResources::getString(std::string group, std::string textId) //366
{
    return m_resources.getString(group, textId);
}

int LuaResources::playAudio(LuaState* lua) //371-388
{
    int count = lua->top(); //373
    assert(count >= 1 && count <= 4); //Line 303

    float volume = 1.0; //376
    bool looping = false; //377
    int track = 0; //378

    std::string id = lua->toString(1); //380
    if (count >= 2) volume = lua->toNumber(2);
    if (count >= 3) looping = lua->toBoolean(3);
    if (count >= 4) track = lua->toNumber(4);

    intptr_t handle = m_resources.playAudio(id, volume, looping, track); //385
    lua->pushLightUserData(&handle);
    return 1;
}

int LuaResources::stopAudio(LuaState* lua) //390-408
{
    int count = lua->top(); //392
    if (lua->isLightUserData(1))
    {
        void* userData = lua->toUserData(1); //397
        m_resources.stopAudio((int)userData);
    }
    else if (lua->isString(1))
        m_resources.stopAudio(lua->toString(1));

    return 0;
}

void LuaResources::stopAllAudio() //Seasons
{
    m_resources.stopAllAudio();
}

int LuaResources::isAudioPlaying(LuaState* lua) //415-431
{
    bool isPlaying = false; //417

    if (lua->isLightUserData(1))
        isPlaying = m_resources.isAudioPlaying((int)(lua->toLightUserData(1)));
    else if (lua->isString(1))
        isPlaying = m_resources.isAudioPlaying((int)(lua->toString(1)));

    lua->pushBoolean(isPlaying);
    return 1;
}

int LuaResources::getSpriteBounds(LuaState* lua) //434-445 | DarkestFear
{
    std::string spriteId = lua->toString(lua->top() == 1 ? 1 : 2); //436 | There was originally an assert but it's completely gone according to line numbers.

    int width = m_resources.getSpriteWidth(spriteId); //438
    int height = m_resources.getSpriteHeight(spriteId); //439

    lua->pushNumber(width);
    lua->pushNumber(height);

    return 2;
}

int LuaResources::getSpritePivot(LuaState* lua) //447-458
{
    std::string spriteId = lua->toString(lua->top() == 1 ? 1 : 2); //449 | There was originally an assert but it's completely gone according to line numbers.

    int pivotX = m_resources.getSpritePivotX(spriteId); //451
    int pivotY = m_resources.getSpritePivotY(spriteId); //452

    lua->pushNumber(pivotX);
    lua->pushNumber(pivotY);

    return 2;
}

int LuaResources::getCompoSpriteBounds(LuaState* lua) //460-486
{
    std::string compoId = lua->toString(lua->top() == 1 ? 1 : 2); //462 | There was originally an assert but it's completely gone according to line numbers.

    CompoSprite* sprite = m_resources.getCompoSprite(compoId); //464

    if (!sprite)
	{
        LANG_LOG("", LANG_LOG_PRIORITY_ERROR, "Could not find composprite (for get): %s", compoId); //468
        return 0;
	}

    sprite->calculateBounds();

    int width = sprite->getWidth(); //475
    int height = sprite->getHeight(); //476
    int pivotX = sprite->getPivotX(); //477
    int pivotY = sprite->getPivotY(); //478

    lua->pushNumber(-pivotX);
    lua->pushNumber(-pivotY);
    lua->pushNumber(width - pivotX);
    lua->pushNumber(height - pivotY);

    return 4;
}

int LuaResources::getCompoSpriteEntry(LuaState* lua) //488-530 | Classic 4.0.0 iOS+ 2013-01-01
{
    std::string compoId = lua->toString(1); //490
    LuaTable ret(lua); //491
    CompoSprite* sprite = m_resources.getCompoSprite(compoId); //492

    if (!sprite)
    {
        LANG_LOG("", LANG_LOG_PRIORITY_ERROR, "Could not find composprite (for get): %s", compoId); //496
        return 0;
    }

    CompoSprite::Entry entry; //501
    if (lua->isNumber(2))
    {
        int spriteIdx = lua->toNumber(2); //504
        entry = sprite->getSpriteEntry(spriteIdx); //505
    }
    else if (!lua->isString(2)) return 0;

    std::string spriteId = lua->toString(2); //509
    entry = sprite->getSpriteEntry(2); //510
    ret.setString("name", entry.m_spriteEntryName);
    ret.setNumber("x", entry.m_pos.x + 1);
    ret.setNumber("y", entry.m_pos.y);
    ret.setNumber("scaleX", entry.m_scale.x + 1);
    ret.setNumber("scaleY", entry.m_scale.y);
    ret.setBoolean("flipX", entry.m_flip.x < 0.0);
    ret.setBoolean("flipY", entry.m_flip.y < 0.0);
    ret.setNumber("angle", entry.m_angle);
    ret.setBoolean("visible", entry.m_visible);
    ret.luaState()->pushTable(this); //528
    return 1;
}

int LuaResources::setCompoSpriteEntry(LuaState* lua) //532-594 Classic 4.0.0 iOS+ 2013-01-01
{
    std::string compoId = lua->toString(1); //534
    CompoSprite* sprite = m_resources.getCompoSprite(compoId); //535

    if (!sprite)
    {
        LANG_LOG("", LANG_LOG_PRIORITY_ERROR, "Could not find composprite (for set): %s", compoId); //538
        return 0;
    }

    CompoSprite::Entry* entry; //543
    if (lua->isNumber(2))
    {
        int spriteIdx = lua->toNumber(2); //546
        entry = &sprite->getSpriteEntry(spriteIdx);
    }
    else if (!lua->isString(2)) return 0;

    std::string spriteId = lua->toString(2); //551
    entry = &sprite->getSpriteEntry(2);

    LuaTable entryData = lua->toTable(3); //560

    std::string name = "name"; //564 
    //compare //565
    if (!entryData.isNil(name))
    {
        std::string spriteId = entryData.getString(name); //567
        long unsigned int pos = spriteId.find('#'); //568
        if (pos != -1)
            entry->m_spriteEntryName = spriteId;

        sprite->replaceSprite(entry->m_spriteEntryName, spriteId, m_resources.getSprite(spriteId));
    }

    if (!entryData.isNil("x"))
        entry->m_pos.x = entryData.getNumber("x");

    if (!entryData.isNil("y"))
        entry->m_pos.y = entryData.getNumber("y");

    if (!entryData.isNil("scaleX"))
        entry->m_scale.x = entryData.getNumber("scaleX");

    if (!entryData.isNil("scaleY"))
        entry->m_scale.y = entryData.getNumber("scaleY");

    if (!entryData.isNil("flipX"))
        entry->m_flip.x = entryData.getBoolean("flipX") ? 1.0 : -1.0;

    if (!entryData.isNil("flipY"))
        entry->m_flip.y = entryData.getBoolean("flipY") ? 1.0 : -1.0;

    if (!entryData.isNil("angle"))
        entry->m_angle = entryData.getNumber("angle");

    if (!entryData.isNil("visible"))
        entry->m_visible = entryData.getBoolean("visible");

    return 0;
}

int LuaResources::getCompoSpriteData(LuaState* lua) //596-614 | Classic 1.6.3 Bada / 1.5.2 Mobile / 1.5.1 Mac
{
    std::string spriteId = lua->toString(1); //598
    LuaTable ret(lua); //599
    CompoSprite* sprite = m_resources.getCompoSprite(spriteId); //600

    for (int i = 1; i - 1 < sprite->getSpriteCount(); i++) //602
    {
        CompoSprite::Entry entry = sprite->getSpriteEntry(i - 1); //604 | This makes sense
        LuaTable luaEntry(lua); //605
        luaEntry.setString(1, entry.m_spriteEntryName);
        luaEntry.setNumber(2, entry.m_pos.x); //?
        luaEntry.setNumber(3, entry.m_pos.y); //?
        ret.setTable(i, luaEntry);
    }

    lua->pushTable(ret); //612
    return 1;
}

float LuaResources::getStringWidth(std::string str)
{
    return m_resources.getStringWidth(str, 0, -1);
}

float LuaResources::getFontMaxAscending()
{
    return m_resources.getFontMaxAscending();
}

float LuaResources::getFontMaxDescending()
{
    return m_resources.getFontMaxDescending();
}

float LuaResources::getFontLeading()
{
    return m_resources.getFontLeading();
}

float LuaResources::getFontTracking()
{
    return m_resources.getFontTracking();
}

float LuaResources::getFontHeight()
{
    return m_resources.getFontHeight();
}

bool LuaResources::startAudioOutput()
{
    return m_resources.startAudioOutput();
}

void LuaResources::stopAudioOutput()
{
    m_resources.stopAudioOutput();
}

void LuaResources::startAudioInput()
{
    m_resources.startAudioInput();
}

void LuaResources::stopAudioInput()
{
    m_resources.stopAudioInput();
}

float LuaResources::getMasterVolume()
{
    return m_resources.getMasterVolume();
}

void LuaResources::setMasterVolume(float volume) //671
{
    m_resources.setMasterVolume(volume);
}

void LuaResources::setTrackVolume(float track, float volume) //676
{
    m_resources.getAudioOutput()->setTrackVolume(track, volume);
}

float LuaResources::getTrackVolume(float track) //681
{
    return m_resources.getAudioOutput()->getTrackVolume(track);
}

bool LuaResources::openURL(std::string url) //686
{
    Launcher launcher;
    return launcher.openURL(url);
}

Resources* LuaResources::getResources() //DarkestFear
{
    return &m_resources;
}

}