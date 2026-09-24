#include <game/Resources.h>
#include <game/BitmapFont.h>
#include <game/IFont.h>
#include <game/TextGroup.h>
#include <game/TextGroupSet.h>
#include <game/CompoSprite.h>
#include <game/CompoSpriteSet.h>
#include <game/SpriteSheet.h>
#include <game/SheetLoaderJSON.h>
#include <game/SheetLoaderDAT.h>
#include <game/SystemFont.h>
#include <gr/Context.h>
#include <gr/Image.h>
#include <lang/Exception.h>
#include <io/AppDataInputStream.h>
#include <io/BundleInputStream.h>
#include <io/FileFormat.h>
#include <audio/AudioClip.h>
#include <audio/AudioOutput.h>
#include <audio/AudioInput.h>
#include <audio/CompositeAudioClip.h>

using namespace audio;
using namespace lang;
using namespace io;
using namespace gr;

const int BLOCK_SIZE = 4096;

namespace game
{

Resources::Resources(Context* context) : //Access using _G.res!
    m_context(context)
{
    m_audioOutput = 0;
    m_audioInput = 0;
    m_currentFont = 0;
    m_currentFontName = "";
    m_useLocale = "en_EN";
}

Resources::~Resources()
{
}

void Resources::setPath(const std::string& path)
{
    m_path = PathName(path);
}

void Resources::addCompoSpriteSet(const std::string& name, CompoSpriteSet* composet) //TODO
{
    /*for (std::map<std::string, P(CompoSpriteSet)>::const_iterator it = m_composites.find(name); it != m_composites.end(); it++)
    {
        SpriteEntry entry = m_sprites[it->first];
        if (it->second == composet)
            removeSpritesFromRegistry(it->second);

        addSpritesToRegistry(it->second, name);

        std::string set = name;
    }*/
}

void Resources::addSpriteSheet(const std::string& name, SpriteSheet* sheet) //?
{
    if (m_sheets.find(name) != m_sheets.find(name)) //?
        removeSpritesFromRegistry(m_sheets[name]);
    //m_sheets.find("name")->first != name
    //?
    /*if (m_sheets.find("name")->first != "name") //?
    {
        if (m_sheets.find(name) != m_sheets[name]->getSprites())
    }*/
    //m_sheets.find(name);
    //m_sheets[name]->getSprites();
     
    addSpritesToRegistry(sheet, name);  

    //if (m_sheets[name]->getSprites() !=)

    //delete m_sheets[name];
    m_sheets[name] = sheet;
}

void Resources::addSpritesToRegistry(SpriteSheet* sheet, const std::string& name) //Name isn't used?
{
    for (std::map<std::string, SpriteEntry>::const_iterator it = m_sprites.begin(); it != m_sprites.end(); it++)
    {
        SpriteEntry entry = m_sprites[it->first];
        entry.m_type = SpriteEntry::SPRITE;
        entry.m_sheetName = it->first;
        entry.m_sprite = it->second.m_sprite;
        m_sprites.insert(*it);
    }
}

void Resources::removeSpritesFromRegistry(SpriteSheet* sheet)
{
    for (std::map<std::string, SpriteEntry>::const_iterator it = m_sprites.begin(); it != m_sprites.end(); it++) //?
        m_sprites.erase(it);
}

void Resources::addSpritesToRegistry(CompoSpriteSet* composet, const std::string& name)
{
    for (std::map<std::string, P(CompoSpriteSet)>::const_iterator it = m_composites.find(name); it != m_composites.end(); it++) //?
    {
        SpriteEntry entry = m_sprites[it->first];
        entry.m_type = SpriteEntry::COMPOSPRITE;
        entry.m_sheetName = it->first;
        entry.m_compoSprite = it->second->getCompoSprite(entry.m_sheetName); //?
        m_composites.insert(*it);
    }
}

void Resources::removeSpritesFromRegistry(CompoSpriteSet* composet) //Not on iOS.
{
    for (std::map<std::string, P(CompoSpriteSet)>::const_iterator it = m_composites.begin(); it != m_composites.end(); it++) //?
        m_composites.erase(it);
}

SpriteSheet* Resources::createSpriteSheet(const std::string& filename, bool forceLoad, bool loadImage)
{
    /*PathName pathName(filename);
    std::string name = pathName.basename(); //Confirmed
    std::string fullPath = PathName(name).toString();

    m_sprites.count(fullPath);

    pathName.suffix()

    //new SpriteSheet()
    P(SheetLoader) loader = new SheetLoader();*/
    // .suffix()
    P(SpriteSheet) sheet = m_sheets[filename];
    /*m_ptr = ? ;
    pathnamea = SpriteSheet::getSprites(m_ptr);
    Sprites = SpriteSheet::getSprites(m_ptr);
    addSpritesToRegistry(sheet, &__k);
    //?*/
    /*m_sheets.count(fullPath);
    if (forceLoad)
    {
        if (!strcmp(pathName.suffix(), ".dat"))
        {
            loader = new SheetLoaderDAT();
        }
        else if (!strcmp(pathName.suffix(), ".json"))
        {
            loader = new SheetLoaderJSON();
        }

        m_sheets.find(fullPath);
    }*/

    //addSpritesToRegistry(, filename)
    return sheet;
}

CompoSpriteSet* Resources::createCompoSpriteSet(const std::string& filename, bool forceLoad) //TODO
{
    PathName pathName(filename);
    std::string name = pathName.basename();
    std::string fullPath = pathName.toString();

    P(SheetLoader) loader;
    P(CompoSpriteSet) set = m_composites.find(filename)->second;
    /*if (forceLoad)
    {
        if (!strcmp(pathName.suffix(), ".dat"))
        {
            loader = new SheetLoaderDAT();
        }
        else if (!strcmp(pathName.suffix(), ".json"))
        {
            loader = new SheetLoaderJSON();
        }
        loader->loadCompositeSet(fullPath, m_sheets);
    }
    if (set->getCompoSprites())
    {
        pathnamea = set.getCompoSprites();
        Sprites = set.getCompoSprites();
        addSpritesToRegistry(sheet, &__k);
    }*/
    CompoSpriteSet* composet = m_composites[name];
    return composet;
}

void Resources::captureSprite(const std::string& spriteId)
{
    std::map<std::string, P(SpriteSheet)>::const_iterator it = m_sheets.find(spriteId);

    P(Image) image = it->second->getImage();
    if (it != m_sheets.end())
    {
        m_context->capture(image);
    }

    else
    {
        SpriteSheet* sheet = new SpriteSheet(image);
        sheet->createSprite(spriteId, 0, 0, image->width(), image->height(), 0, 0, image->flipped() ? Sprite::FLIP_VERTICAL : Sprite::ROTATION_NONE);
        addSpriteSheet(spriteId, sheet);
    }
}

BitmapFont* Resources::createBitmapFont(const std::string& filename, bool forceLoad)
{
    std::string name = PathName(filename).basename();
    std::string fullPath = PathName(name).toString();
    if (forceLoad)
    {
        m_fonts.count(name);
        if (m_fonts.find(filename) != m_fonts.end())
            return (BitmapFont*)&m_fonts[filename];
    }
    P(BitmapFont) font = new BitmapFont(m_context, fullPath);
    m_fonts[name] = (BitmapFont*)font;
    return font;
}

SystemFont* Resources::createSystemFont(const std::string& id, const std::string& fontName, int fontSize, const Color& fontColor, int style, bool forceLoad)
{
    if (forceLoad)
    {
        if (m_fonts.find(id) != m_fonts.end())
            return (SystemFont*)&m_fonts[id];
    }
    P(SystemFont) font = new SystemFont(m_context, fontName, fontSize, fontColor, style);
    m_fonts[fontName] = (SystemFont*)font;
    return font;
}

TextGroupSet* Resources::createTextGroupSet(const std::string& filename, bool forceLoad)
{
    std::string name = PathName(filename).basename();
    std::string fullPath = PathName(name).toString();
    if (forceLoad)
    {
        m_textGroupSets[name] = new TextGroupSet(fullPath);
        m_textGroupSets[name]->loadLocaleCodes();
    }
    else
    {
        if (m_textGroupSets.find(name) == m_textGroupSets.end())
            m_textGroupSets.find(name)->second->loadLocaleCodes();
    }
    return m_textGroupSets[name];
}

AudioOutput* Resources::createAudioOutput(const AudioConfiguration& conf)
{
    m_audioOutput = new AudioOutput(conf);

    return m_audioOutput;
}

AudioInput* Resources::createAudioInput(const AudioConfiguration& conf)
{
    m_audioInput = new AudioInput(conf);

    return m_audioInput;
}

AudioClip* Resources::createAudio(P(InputStream) in, const std::string& id, bool stream)
{
    FileFormat fmt = guessFileFormat(in->toString());

    P(AudioClip) audioclip;
    if (stream)
    {
        audioclip = new AudioClip(in, fmt);
        return audioclip;
    }
    /*else
    {
        P(AudioReader) reader = new AudioReader(in, fmt);
        std::vector<char> data;
        int read = data.size();
        unsigned int offset;
        data.resize(in->available());
        reader->readData(&data, 0, data.size());
        AudioConfiguration conf;
        conf.m_channels = reader->channels();
        conf.m_bitsPerSample = reader->bitsPerSample();
        conf.m_samplesPerSecond = reader->sampleRate();
        audioclip = new AudioClip(&data, read, conf);
    }*/
    return 0;
}

AudioClip* Resources::createAudio(const std::string& filename, const std::string& id, bool stream)
{
    std::string fullPath = PathName(filename).toString();
    P(InputStream) in = new BundleInputStream(fullPath);
    return createAudio(in, id, stream);
}

CompositeAudioClip* Resources::createCompositeAudio(const std::string& id, const std::vector<P(AudioClip)>& clips) //?
{
    P(CompositeAudioClip) audioclip = new CompositeAudioClip(clips);

    if (m_audioClips.find(id) != m_audioClips.end()) //?
        m_audioOutput->stopClip(m_audioClips[id]);

    //m_audioClips[id] = audioclip.ptr(); //?

    return audioclip;
}

void Resources::releaseSpriteSheet(const std::string& filename, bool releaseOnlyImages)
{
    std::string name = PathName(filename).basename();
    //if (m_sheets.count(name) < 0)
        //m_sheets.find(name)->second->
    //m_sheets[name]->getSprites();

    if (releaseOnlyImages)
        m_sheets[name]->unload();
    else
        m_sheets.erase(name);

    //removeSpritesFromRegistry()
}

void Resources::releaseCompoSpriteSet(const std::string& filename)
{
    std::string name = PathName(filename).basename();
    //if (m_composites.count(filename))
        //m_composites.insert();
    //removeSpritesFromRegistry(m_composites.find(name)->second);
}

void Resources::releaseFont(const std::string& filename)
{
    std::string name = PathName(filename).basename();
    if (m_fonts.count(name))
        m_fonts.erase(name);
}

void Resources::releaseTextGroupSet(const std::string& filename)
{
    std::string name = PathName(filename).basename();
    if (m_textGroupSets.count(name))
        m_textGroupSets.erase(name);
}

void Resources::releaseAudio(const std::string& id)
{
    std::map<std::string, P(AudioClip)>::iterator it = m_audioClips.find(id);
    if (it != m_audioClips.end())
    {
        if (m_audioOutput)
            m_audioOutput->stopClip(it->second);
        m_audioClips.erase(it);
    }
}

void Resources::loadLocale(const std::string& textGroupSet, const std::string& locale) //Correct?
{
    std::map<std::string, P(TextGroupSet)>::iterator it = m_textGroupSets.find(textGroupSet);
    if (it != m_textGroupSets.end())
    {
        it->second->releaseTextGroup("ALL");
        it->second->loadTextGroup(locale);
    }
}

TextGroupSet* Resources::getTextGroupSet(const std::string& textGroupSet) const
{
    std::map<std::string, P(TextGroupSet)>::const_iterator it = m_textGroupSets.find(textGroupSet);
    if (it != m_textGroupSets.end())
        return it->second;
    return 0;
}

void Resources::useFont(const std::string& fontName) //Correct?
{
    std::map<std::string, P(IFont)>::iterator it = m_fonts.find(fontName);
    if (it != m_fonts.end())
    {
        m_currentFont = it->second;
        m_currentFontName = fontName;
    }
}

IFont* Resources::getFont() const
{
    return m_currentFont;
}

void Resources::useLocale(const std::string& localeName)
{
    m_useLocale = localeName;
}

const std::string& Resources::getLocale() const
{
    return m_useLocale;
}

Sprite* Resources::getSprite(const std::string& spriteId)
{
    std::map<std::string, SpriteEntry>::iterator it = m_sprites.find(spriteId);
    if (it != m_sprites.end())
        return it->second.m_sprite;
    return 0;
}

SpriteSheet* Resources::getSpriteSheet(const std::string& sheetId) const
{
    std::map<std::string, P(SpriteSheet)>::const_iterator it = m_sheets.find(sheetId);
    if (it != m_sheets.end())
        return it->second;
    return 0;
}

SpriteSheet* Resources::findSpriteSheet(const std::string& spriteId) const //Correct?
{
    std::map<std::string, SpriteEntry>::const_iterator it = m_sprites.find(spriteId);
    if (it != m_sprites.end()) //? //return it->second.m_sprite->getSheet(); //Or this?
    {
        std::map<std::string, P(SpriteSheet)>::const_iterator it2 = m_sheets.find(spriteId);
        if (it2 != m_sheets.end()) //?
            return it2->second;
    }

    return 0;
}

CompoSprite* Resources::getCompoSprite(const std::string& spriteId) const
{
    std::map<std::string, SpriteEntry>::const_iterator it = m_sprites.find(spriteId);
    if (it != m_sprites.end())
        return it->second.m_compoSprite;
    return 0;
}

void Resources::drawSprite(const std::string& spriteId, float x, float y, Anchor anchor) const
{
    std::map<std::string, SpriteEntry>::const_iterator it = m_sprites.find(spriteId);
    if (it != m_sprites.end())
    {
        switch (it->second.m_type)
        {
        case SpriteEntry::SPRITE: it->second.m_sprite->draw(m_context, x, y, anchor); break;
        case SpriteEntry::COMPOSPRITE: it->second.m_compoSprite->draw(m_context, x, y, anchor); break;
        }
    }
}

void Resources::drawSprite(const std::string& spriteId, float x, float y, float width, float height, Anchor anchor) const
{
    std::map<std::string, SpriteEntry>::const_iterator it = m_sprites.find(spriteId);
    if (it != m_sprites.end())
    {
        switch (it->second.m_type)
        {
        case SpriteEntry::COMPOSPRITE: it->second.m_compoSprite->draw(m_context, x, y, anchor); break;
        case SpriteEntry::SPRITE: it->second.m_sprite->draw(m_context, x, y, width, height, anchor); break;
        }
    }
}

void Resources::drawString(const std::string& textgroup, const std::string& textId, float x, float y, Anchor anchor) const
{
    if (!m_currentFont)
        throwError(Exception(Format("No font is set while trying to draw string")));
    m_currentFont->drawString(m_context, getString(textgroup, textId), x, y, anchor);
}

int Resources::playAudio(const std::string& id, float volume, bool looping, int track) const //This EXISTS in RCS but has no code.
{
    if (!m_audioOutput)
        throwError(Exception(Format("Trying to play audio clip but no audio output has been created")));

    std::map<std::string, P(AudioClip)>::const_iterator it = m_audioClips.find(id);
    if (it != m_audioClips.end())
        return m_audioOutput->playClip(it->second, volume, looping, track);

    return -1;
}

void Resources::stopAudio(const std::string& id)
{
    if (!m_audioOutput)
        throwError(Exception(Format("Trying to stop audio clip but no audio output has been created")));

    for (std::map<std::string, P(AudioClip)>::const_iterator it = m_audioClips.begin(); it != m_audioClips.end(); it++)
        m_audioOutput->stopClip(m_audioClips[id]);
}

void Resources::stopAudio(int handle)
{
    if (!m_audioOutput)
        throwError(Exception(Format("Trying to stop audio clip but no audio output has been created")));

    m_audioOutput->stopClip(handle);
}

bool Resources::isAudioPlaying(const std::string& id) const
{
    if (!m_audioOutput)
        return false;

    std::map<std::string, P(AudioClip)>::const_iterator it = m_audioClips.find(id);
    return it != m_audioClips.end() ? m_audioOutput->isClipPlaying(it->second) : false;
}

bool Resources::isAudioPlaying(int id) const
{
    return m_audioOutput ? m_audioOutput->isClipPlaying(id) : false;
}

int Resources::getSpriteWidth(const std::string& spriteId) const
{
    std::map<std::string, SpriteEntry>::const_iterator it = m_sprites.find(spriteId);
    if (it != m_sprites.end())
    {
        switch (it->second.m_type)
        {
        case SpriteEntry::SPRITE: return it->second.m_sprite->getWidth();
        case SpriteEntry::COMPOSPRITE: return it->second.m_compoSprite->getWidth();
        }
    }
    return 0;
}

int Resources::getSpriteHeight(const std::string& spriteId) const
{
    std::map<std::string, SpriteEntry>::const_iterator it = m_sprites.find(spriteId);
    if (it != m_sprites.end())
    {
        switch (it->second.m_type)
        {
        case SpriteEntry::SPRITE: return it->second.m_sprite->getHeight();
        case SpriteEntry::COMPOSPRITE: return it->second.m_compoSprite->getHeight();
        }
    }
    return 0;
}

int Resources::getSpritePivotX(const std::string& spriteId) const
{
    std::map<std::string, SpriteEntry>::const_iterator it = m_sprites.find(spriteId);
    if (it != m_sprites.end())
    {
        switch (it->second.m_type)
        {
        case SpriteEntry::SPRITE: return it->second.m_sprite->getPivotX();
        case SpriteEntry::COMPOSPRITE: return it->second.m_compoSprite->getPivotX();
        }
    }
    return 0;
}

int Resources::getSpritePivotY(const std::string& spriteId) const
{
    std::map<std::string, SpriteEntry>::const_iterator it = m_sprites.find(spriteId);
    if (it != m_sprites.end())
    {
        switch (it->second.m_type)
        {
        case SpriteEntry::SPRITE: return it->second.m_sprite->getPivotY();
        case SpriteEntry::COMPOSPRITE: return it->second.m_compoSprite->getPivotY();
        }
    }
    return 0;
}

const std::string& Resources::getString(const std::string& textgroup, const std::string& textId) const
{
    std::map<std::string, P(TextGroupSet)>::const_iterator it = m_textGroupSets.find(textgroup);
    return it != m_textGroupSets.end() ? it->second->getTextGroup(m_useLocale)->get(textId) : textId;
}

int Resources::getStringWidth(const std::string& str, int offset, int length) const
{
    if (!m_currentFont)
        throwError(Exception(Format("No font is set while trying to get string width")));

    return m_currentFont->getStringWidth(str, offset, length);
}

int Resources::getFontMaxAscending() const
{
    if (!m_currentFont)
        throwError(Exception(Format("No font is set while trying to get font max ascending")));

    return m_currentFont->getMaxAscending();
}

int Resources::getFontMaxDescending() const
{
    if (!m_currentFont)
        throwError(Exception(Format("No font is set while trying to get font max descending")));

    return m_currentFont->getMaxDescending();
}

int Resources::getFontLeading() const
{
    if (!m_currentFont)
        throwError(Exception(Format("No font is set while trying to get font leading")));

    return m_currentFont->getLeading();
}

int Resources::getFontTracking() const
{
    if (!m_currentFont)
        throwError(Exception(Format("No font is set while trying to get font tracking")));

    return m_currentFont->getTracking();
}

int Resources::getFontHeight() const
{
    if (!m_currentFont)
        throwError(Exception(Format("No font is set while trying to get font height!"))); //Why an exclaimation mark?

    return m_currentFont->getHeight();
}

float Resources::getMasterVolume() const
{
    return m_audioOutput ? m_audioOutput->getMasterVolume() : 0.0;
}

void Resources::setMasterVolume(float volume) const
{
    if (m_audioOutput)
        m_audioOutput->setMasterVolume(volume);
}

bool Resources::startAudioOutput()
{
    if (!m_audioOutput)
        throwError(Exception(Format("Trying to start audio output but no audio output has been created")));
    return m_audioOutput->startOutput();
}

void Resources::stopAudioOutput()
{
    if (m_audioOutput)
        m_audioOutput->stopOutput();
}

bool Resources::startAudioInput()
{
    if (!m_audioInput)
        throwError(Exception(Format("Trying to start audio input but no audio output has been created")));
    return m_audioInput->startInput();
}

void Resources::stopAudioInput()
{
    if (m_audioInput)
        return m_audioInput->stopInput();
}

AudioOutput* Resources::getAudioOutput() const
{
    return m_audioOutput;
}

AudioInput* Resources::getAudioInput() const
{
    return m_audioInput;
}

AudioClip* Resources::getAudioClip(const std::string& id) const
{
    std::map<std::string, P(AudioClip)>::const_iterator it = m_audioClips.find(id);
    return it != m_audioClips.end() ? it->second : false;
}

const Rect& Resources::getClipRect() const
{
    return m_clipRect;
}

void Resources::setClipRect(const Rect& clip)
{
    m_context->setClipRect(clip); //?
}


//NOT ON IOS

CompoSpriteSet* Resources::createCompoSpriteSet(const std::string& filename, P(InputStream) in, bool forceLoad) //Not on iOS?
{
    std::map<std::string, P(CompoSpriteSet)>::const_iterator it = m_composites.find(filename);

    if (forceLoad)
    {
        //P(SheetLoader) loader = new SheetLoader();
        if (it != m_composites.end())
            return m_composites[filename];
    }
    
    return 0;

    /*if (getCompoSprites)
    {
        pathnamea = CompoSpriteSet::getCompoSprites(m_ptr);
        Sprites = CompoSpriteSet::getCompoSprites(m_ptr);
        addSpritesToRegistry(sheet, &__k);
    }*/
}

AudioClip* Resources::createAudioFromAppData(const std::string& filename, const std::string& id, bool stream) //Not defined on iOS.
{
    AppDataInputStream* adis = new AppDataInputStream(filename);
    return createAudio(adis, id, stream);
}

AudioClip* Resources::createAudio(const std::string& filename, const void* data, int size, const AudioConfiguration& conf) //Not defined on iOS.
{
    P(AudioClip) audioClip = new AudioClip(data, size, conf);

    /* In legacy versions
    if (!m_audioOutput)
        throwError(Exception(Format("Trying to create audio but no audio output has been created");
    */

    if (&m_audioClips.find(filename))
    {
        m_audioOutput->stopClip(m_audioClips[filename]);
    }
    return audioClip;
}

void Resources::queueCreateSpriteSheet(const std::string&)
{
    /*QueueEntry entry;
    entry.m_type = QueueEntry::SPRITESHEET;
    entry.m_filename = "";
    entry.m_id = "";
    m_queue.push_back(entry);*/
}

void Resources::queueCreateCompoSpriteSet(const std::string&)
{
    /*QueueEntry entry;
    entry.m_type = QueueEntry::COMPOSPRITESET;
    entry.m_filename = "";
    entry.m_id = "";
    m_queue.push_back(entry);*/
}

void Resources::queueCreateBitmapFont(const std::string&)
{
    /*QueueEntry entry;
    entry.m_type = QueueEntry::BITMAPFONT;
    entry.m_filename = "";
    entry.m_id = "";
    m_queue.push_back(entry);*/
}

void Resources::queueCreateTextGroupSet(const std::string&)
{
    /*QueueEntry entry;
    entry.m_type = QueueEntry::TEXTGROUPSET;
    entry.m_filename = "";
    entry.m_id = "";
    m_queue.push_back(entry);*/
}

void Resources::queueCreateAudio(const std::string&, const std::string&)
{
    /*QueueEntry entry;
    entry.m_type = QueueEntry::AUDIOCLIP;
    entry.m_filename = "";
    entry.m_id = "";
    m_queue.push_back(entry);*/
}

int Resources::queueSize() const //?
{
    return 0;
    //return 0xAABBBBBB * (())
}

void Resources::loadQueued()
{
    /*QueueEntry entry;
    if (entry.m_filename != entry.m_id)
        return;
    //m_queue.erase(entry); //?
    switch (entry.m_type)
    {
    case QueueEntry::SPRITESHEET: createSpriteSheet(entry.m_filename); break;
    case QueueEntry::COMPOSPRITESET: createCompoSpriteSet(entry.m_filename); break;
    case QueueEntry::BITMAPFONT: createBitmapFont(entry.m_filename); break;
    case QueueEntry::TEXTGROUPSET: createTextGroupSet(entry.m_filename); break;
    case QueueEntry::AUDIOCLIP: createAudio(entry.m_filename, entry.m_id, true); break;
    default: break;
    }*/
}

void Resources::loadAllQueued()
{
    while (queueSize())
        loadQueued();
}

void Resources::releaseAudioOutput()
{
    m_audioOutput->release();
}

void Resources::releaseAudioInput()
{
    m_audioInput->release();
}

void Resources::drawNumber(float value, int digits, float x, float y, Anchor anchor) const //Only on Android ABS410. Not seen on ABS410 iOS/PC AT ALL, the string isn't even there!
{
    const int MAX_DIGITS = 9;

    if (digits > MAX_DIGITS)
        throwError(Exception(Format("drawNumber supports only digits up to 9, trying to use {0}", digits)));

    char buffer[32];
    strcpy(buffer, "%.0f");

    if (digits <= 0)
    {
        strcpy(buffer, "d");
        sprintf(buffer, "d", value);
    }
    else
    {
        sprintf(buffer, "", value);
    }

    drawString("", buffer, 0, strlen(buffer), x, y, anchor);
}

void Resources::resumeAllAudio() const
{
    if (!m_audioOutput)
        throwError(Exception(Format("Trying to resume all audio clips but no audio output has been created")));
    
    m_audioOutput->resumeClips();
}

void Resources::pauseAllAudio() const
{
    if (!m_audioOutput)
        throwError(Exception(Format("Trying to pause all audio clips but no audio output has been created")));
    
    m_audioOutput->pauseClips();
}

void Resources::stopAllAudio() const
{
    if (!m_audioOutput)
        throwError(Exception(Format("Trying to stop all audio clips but no audio output has been created")));
    
    m_audioOutput->stopClips();
}

const std::string& Resources::getFontName() const
{
    return m_currentFontName;
}

CompoSpriteSet* Resources::getCompoSpriteSet(const std::string& spriteId) const
{
    std::map<std::string, P(CompoSpriteSet)>::const_iterator it = m_composites.find(spriteId);
    return it != m_composites.end() ? it->second : 0;
}

CompoSpriteSet* Resources::findCompoSpriteSet(const std::string& spriteId) const //Not defined on iOS.
{
    for (std::map<std::string, SpriteEntry>::const_iterator spriteIt = m_sprites.find(spriteId); spriteIt != m_sprites.end(); spriteIt++)
    {
        std::map<std::string, P(CompoSpriteSet)>::const_iterator compoIt = m_composites.find(spriteIt->first);
        if (compoIt->second)
            return compoIt->second;
    }
    return 0;
}

}