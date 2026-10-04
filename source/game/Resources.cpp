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

const int BLOCK_SIZE = 4096; //334

namespace game
{

Resources::Resources(Context* context) : //23 | Access using _G.res!
    m_context(context)
{
    m_audioOutput = 0;
    m_audioInput = 0;
    m_currentFont = 0;
    m_currentFontName = "";
    m_useLocale = "en_EN";
}

Resources::~Resources() //33
{
}

void Resources::setPath(const std::string& path) //36-39
{
    m_path = PathName(path); //38
}

void Resources::addCompoSpriteSet(const std::string& name, CompoSpriteSet* set) //TODO
{
    /*if (m_composites.count(name))
        removeSpritesFromRegistry(m_composites[name]);

    addSpritesToRegistry(set, name);
    m_composites[name] = set;*/

    assert("void game::Resources::addCompoSpriteSet(const std::string& name, game::CompoSpriteSet* set) was not yet decompiled.");
}

void Resources::addSpriteSheet(const std::string& name, SpriteSheet* sheet) //53-65 | ?
{
    /*if (m_sheets.count(name)) //if (m_sheets.find(name) != m_sheets.find(name))  //55 | ?
        removeSpritesFromRegistry(m_sheets[name]); //57

    addSpritesToRegistry(sheet, name); //61

    m_sheets[name] = sheet; //64*/
    assert("void game::Resources::addSpriteSheet(const std::string& name, game::SpriteSheet* sheet) was not yet decompiled.");
}

void Resources::addSpritesToRegistry(SpriteSheet* sheet, const std::string& name) //67-84 | Name isn't used?
{
    for (std::map<std::string, P(Sprite)>::const_iterator it = sheet->getSprites().begin(); it != sheet->getSprites().end(); it++) //69
    {
        SpriteEntry entry = m_sprites[it->first]; //78

        entry.m_type = SpriteEntry::SPRITE;
        entry.m_sheetName = name; //81
        entry.m_sprite = it->second; //82
    }
}

void Resources::removeSpritesFromRegistry(SpriteSheet* sheet) //86
{
    for (std::map<std::string, P(Sprite)>::const_iterator it = sheet->getSprites().begin(); it != sheet->getSprites().end(); it++) //88
        m_sprites.erase(it->first); //90
}

void Resources::addSpritesToRegistry(CompoSpriteSet* composet, const std::string& name) //94-111
{
    for (std::map<std::string, P(CompoSprite)>::const_iterator it = composet->getCompoSprites().begin(); it != composet->getCompoSprites().end(); it++) //96
    {
        SpriteEntry entry = m_sprites[it->first]; //105

        entry.m_type = SpriteEntry::COMPOSPRITE;
        entry.m_sheetName = name;
        entry.m_compoSprite = it->second;
    }
}

void Resources::removeSpritesFromRegistry(CompoSpriteSet* composet) //Not on iOS.
{
    for (std::map<std::string, P(CompoSpriteSet)>::const_iterator it = m_composites.begin(); it != m_composites.end(); it++) //?
        m_composites.erase(it);
}

SpriteSheet* Resources::createSpriteSheet(const std::string& filename, bool forceLoad, bool loadImage) //121-155 | TODO
{
    /*PathName pathName(filename); //123
    std::string name = pathName.basename(); //124
    std::string fullPath = PathName(name).toString(); //125

    if (m_sprites.count(fullPath) && forceLoad) //127
    {
        P(SheetLoader) loader; //129
        if (!strcmp(pathName.suffix(), ".dat")) //130
            loader = new SheetLoaderDAT(); //132

        else if (!strcmp(pathName.suffix(), ".json")) //134
            loader = new SheetLoaderJSON(); //136

        P(SpriteSheet) sheet; // = m_sheets[filename]; //142

        if (m_sheets.count(fullPath)) //145
            //removeSpritesFromRegistry(sheet, filename) //146

        m_sheets[fullPath] = sheet; //152

        return sheet; //154
    }
    
    m_ptr = ? ;
    pathnamea = sheet->getSprites(m_ptr);
    Sprites = sheet->getSprites(m_ptr);
    addSpritesToRegistry(sheet, &__k);
    //?
    
    //-> //146
    if (forceLoad)
    {
        if (!strcmp(pathName.suffix(), ".dat")) //130
            loader = new SheetLoaderDAT(); //132

        else if (!strcmp(pathName.suffix(), ".json")) //134
            loader = new SheetLoaderJSON(); //136

        loader->loadSheet(m_context, fullPath); //142
    }

    m_sheets[fullPath] = sheet; //152

    return sheet; //154

    */

    assert("game::SpriteSheet* game::Resources::createSpriteSheet(const std::string& filename, bool forceLoad, bool loadImage) was not yet decompiled. Returning blank sheet.");
    return 0; //m_sheets[fullPath];
}

CompoSpriteSet* Resources::createCompoSpriteSet(const std::string& filename, bool forceLoad) //TODO | 157-194 (?)
{
    /*PathName pathName(filename); //159
    std::string name = pathName.basename(); //160
    std::string fullPath = pathName.toString(); //161
    if (m_composites.count() || forceLoad) //162
    {
        P(SheetLoader) loader; //164

        if (!strcmp(pathName.suffix(), ".dat")) //166
            loader = new SheetLoaderDAT(); //168

        else if (!strcmp(pathName.suffix(), ".json")) //170
            loader = new SheetLoaderJSON(); //172

        loader->loadCompositeSet(fullPath, m_sheets);

        P(CompoSpriteSet) set = m_composites.find(filename)->second; //179

        //m_composites.size(); //181
        
        //m_composites.count(); //184
            addSpritesToRegistry() //186 | removeSpritesFromRegistry
    }

    else
    {
    }

    
    /*if (forceLoad)
    {
        if (!strcmp(pathName.suffix(), ".dat"))
            loader = new SheetLoaderDAT(); //168

        else if (!strcmp(pathName.suffix(), ".json"))
            loader = new SheetLoaderJSON(); //172

        loader->loadCompositeSet(fullPath, m_sheets);
    }

    if (set->getCompoSprites())
    {
        pathnamea = set.getCompoSprites();
        Sprites = set.getCompoSprites();
        addSpritesToRegistry(sheet, &__k);
    }
    CompoSpriteSet* composet = m_composites[name];*/

    assert("game::CompoSpriteSet* game::Resources::createCompoSpriteSet(const std::string& filename, bool forceLoad, bool loadImage) was not yet decompiled. Returning blank sheet.");
    return 0;
}

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

void Resources::captureSprite(const std::string& spriteId) //219-242 | TODO
{
    /*std::map<std::string, P(SpriteSheet)>::const_iterator it = m_sheets.find(spriteId); //221

    if (it->second == m_sheets[spriteId]) //223 | ?
        m_context->capture((Image*)0); //228

    P(Image) image = m_context->capture((Image*)0); //232

    SpriteSheet* sheet = new SpriteSheet(image); //234

    if (image->flipped()) //236
        sheet->createSprite(spriteId, 0, 0, image->width(), image->height(), 0, 0, Sprite::FLIP_VERTICAL); //237
    else
        sheet->createSprite(spriteId, 0, 0, image->width(), image->height(), 0, 0, Sprite::ROTATION_NONE); //239

    addSpriteSheet(spriteId, sheet); //241*/

    assert("void game:;Resources::captureSprite(const std::string& spriteId) was not yet decompiled.");
}

BitmapFont* Resources::createBitmapFont(const std::string& filename, bool forceLoad) //244-258 | TODO?
{
    /*std::string name = PathName(filename).basename(); //246
    std::string fullPath = PathName(name).toString(); //247
    if (m_fonts.count(name) || forceLoad) //248
    {
        P(BitmapFont) font = new BitmapFont(m_context, fullPath); //250
        m_fonts[name] = (BitmapFont*)font; //251

        font = (BitmapFont*)&m_fonts[name]; //256
        return font; //257
    }*/

    assert("game::BitmapFont* game::Resources::createBitmapFont(const std::string& filename, bool forceLoad) was not yet decompiled. Returning 0.");
    return 0;
}

SystemFont* Resources::createSystemFont(const std::string& id, const std::string& fontName, int fontSize, const Color& fontColor, int style, bool forceLoad) //260-272 | Correct?
{
    /*if (m_fonts.count(id) || forceLoad) //262
    {
        P(SystemFont) font = new SystemFont(m_context, fontName, fontSize, fontColor, style); //264
        m_fonts[id] = (SystemFont*)font;
        return font;
    }

    else
        return (SystemFont*)m_fonts[id].ptr(); //271

    */

    assert("game::SystemFont* game::Resources::createSystemFont(const std::string& id, const std::string& fontName, int fontSize, const gr::Color& fontColor, int style, bool forceLoad) was not yet decompiled. Returning 0.");
    return 0;
}

TextGroupSet* Resources::createTextGroupSet(const std::string& filename, bool forceLoad) //274-284
{
    std::string name = PathName(filename).basename(); //276
    std::string fullPath = PathName(name).toString(); //277
    if (m_textGroupSets.count(name) || forceLoad) //278
    {
        m_textGroupSets[name] = new TextGroupSet(fullPath); //280
        m_textGroupSets[name]->loadLocaleCodes(); //281
    }
    return m_textGroupSets[name]; //283
}

AudioOutput* Resources::createAudioOutput(const AudioConfiguration& conf) //286 | Correct?
{
    m_audioOutput = new AudioOutput(conf);

    return m_audioOutput;
}

AudioInput* Resources::createAudioInput(const AudioConfiguration& conf) //296
{
    m_audioInput = new AudioInput(conf);

    return m_audioInput;
}

AudioClip* Resources::createAudio(P(InputStream) in, const std::string& id, bool stream) //312-362
{
    FileFormat fmt = guessFileFormat(in->toString()); //315

    P(AudioClip) audioclip; //316

    if (stream)
    {
        audioclip = new AudioClip(in, fmt); //320
        return audioclip;
    }
    else
    {
        P(AudioReader) reader = new AudioReader(in, fmt); //325

        std::vector<char> data; //327

        unsigned int offset; //332
        int read = data.size(); //333
        //BLOCK_SIZE //334

        //.size 338
        //max 339
        //[] 340
        data.resize(in->available()); //344
        reader->readData(&data, 0, data.size());
        AudioConfiguration conf(reader->channels(), reader->bitsPerSample(), reader->sampleRate()); //352
        audioclip = new AudioClip(&data, read, conf); //353
        return audioclip;
    }

    if (m_audioClips.count(id)) //357
        m_audioOutput->stopClip(m_audioClips[id]);

    m_audioClips[id] = audioclip.ptr();

    return audioclip;
}

AudioClip* Resources::createAudio(const std::string& filename, const std::string& id, bool stream) //364-369
{
    std::string fullPath = PathName(filename).toString(); //366
    P(InputStream) in = new BundleInputStream(fullPath); //367
    return createAudio(in, id, stream);
}

CompositeAudioClip* Resources::createCompositeAudio(const std::string& id, const std::vector<P(AudioClip)>& clips) //383-393
{
    P(CompositeAudioClip) audioclip = new CompositeAudioClip(clips); //385

    if (m_audioClips.count(id)) //388
        m_audioOutput->stopClip(m_audioClips[id]); //389

    m_audioClips[id] = audioclip.ptr(); //391
    return audioclip;
}

void Resources::releaseSpriteSheet(const std::string& filename, bool releaseOnlyImages) //496-508
{
    std::string name = PathName(filename).basename(); //498
    if (m_sheets.count(name) > 0) //499
        m_sheets.find(name)->second->release();

    //m_sheets[name]->getSprites(); //502 |?
    //.find(); //504 |?

    //removeSpritesFromRegistry()

    if (releaseOnlyImages)
    {
        m_sheets[name]->unload();
    }
    else
        m_sheets.erase(name);

    //.erase(); //506 |?
    //removeSpritesFromRegistry();
}

void Resources::releaseCompoSpriteSet(const std::string& filename) //510-519
{
    std::string name = PathName(filename).basename(); //512
    if (m_composites.count(name))
    {
        removeSpritesFromRegistry(m_composites.find(name)->second); //516
        m_composites.erase(name); //517
    }
}

void Resources::releaseFont(const std::string& filename) //521-529
{
    std::string name = PathName(filename).basename(); //523
    if (m_fonts.count(name)) //524
        m_fonts.erase(name); //527
}

void Resources::releaseTextGroupSet(const std::string& filename) //531-539
{
    std::string name = PathName(filename).basename();  //533
    if (m_textGroupSets.count(name)) //534
        m_textGroupSets.erase(name); //537
}

void Resources::releaseAudio(const std::string& id) //551
{
    std::map<std::string, P(AudioClip)>::iterator it = m_audioClips.find(id); //553
    if (it != m_audioClips.end())
    {
        if (m_audioOutput) //556
            m_audioOutput->stopClip(it->second); //557
        m_audioClips.erase(it); //558
    }
}

void Resources::loadLocale(const std::string& textGroupSet, const std::string& locale) //562 | Correct?
{
    std::map<std::string, P(TextGroupSet)>::iterator it = m_textGroupSets.find(textGroupSet); //564
    if (it != m_textGroupSets.end())
    {
        it->second->releaseTextGroup("ALL"); //567
        it->second->loadTextGroup(locale); //568
    }
}

TextGroupSet* Resources::getTextGroupSet(const std::string& textGroupSet) const //572
{
    std::map<std::string, P(TextGroupSet)>::const_iterator it = m_textGroupSets.find(textGroupSet); //574
    return it->second;
}

void Resources::useFont(const std::string& fontName) //578 | Correct?
{
    std::map<std::string, P(IFont)>::iterator it = m_fonts.find(fontName); //580
    if (it != m_fonts.end())
    {
        m_currentFont = it->second; //583
        m_currentFontName = fontName; //584
    }
}

IFont* Resources::getFont() const
{
    return m_currentFont;
}

void Resources::useLocale(const std::string& localeName) //598
{
    m_useLocale = localeName; //600
}

const std::string& Resources::getLocale() const
{
    return m_useLocale;
}

Sprite* Resources::getSprite(const std::string& spriteId) //608-618
{
    std::map<std::string, SpriteEntry>::iterator it = m_sprites.find(spriteId); //610
    if (it == m_sprites.end()) //?
        return 0;

    if (it->second.m_type == SpriteEntry::SPRITE)
        return it->second.m_sprite;
    else
        return 0; //617
}

SpriteSheet* Resources::getSpriteSheet(const std::string& sheetId) const //620
{
    std::map<std::string, P(SpriteSheet)>::const_iterator it = m_sheets.find(sheetId); //622
    return it->second; //623
}

SpriteSheet* Resources::findSpriteSheet(const std::string& spriteId) const //626 | Correct?
{
    std::map<std::string, SpriteEntry>::const_iterator it = m_sprites.find(spriteId); //628
    if (it != m_sprites.end()) //? //return it->second.m_sprite->getSheet(); //Or this?
    {
        std::map<std::string, P(SpriteSheet)>::const_iterator it2 = m_sheets.find(spriteId); //632
        return it2->second;
    }

    return 0; //636
}

CompoSprite* Resources::getCompoSprite(const std::string& spriteId) const //639
{
    std::map<std::string, SpriteEntry>::const_iterator it = m_sprites.find(spriteId); //641

    if (it->second.m_type == SpriteEntry::COMPOSPRITE)
        return it->second.m_compoSprite; //645
    else
        return 0;
}

void Resources::drawSprite(const std::string& spriteId, float x, float y, Anchor anchor) const //669
{
    std::map<std::string, SpriteEntry>::const_iterator it = m_sprites.find(spriteId); //671
    if (it != m_sprites.end())
    {
        if (it->second.m_type == SpriteEntry::SPRITE)
            it->second.m_sprite->draw(m_context, x, y, anchor); //676

        else if (it->second.m_type == SpriteEntry::COMPOSPRITE)
            it->second.m_compoSprite->draw(m_context, x, y, anchor); //680
    }
}

void Resources::drawSprite(const std::string& spriteId, float x, float y, float width, float height, Anchor anchor) const //685
{
    std::map<std::string, SpriteEntry>::const_iterator it = m_sprites.find(spriteId); //687
    if (it != m_sprites.end()) //?
    {
        if (it->second.m_type == SpriteEntry::SPRITE)
            it->second.m_sprite->draw(m_context, x, y, width, height, anchor); //692

        else if (it->second.m_type == SpriteEntry::COMPOSPRITE)
            it->second.m_compoSprite->draw(m_context, x, y, anchor); //697
    }
}

void Resources::drawString(const std::string& textgroup, const std::string& textId, float x, float y, Anchor anchor) const //702-708
{
    if (!m_currentFont)
        throwError(Exception(Format("No font is set while trying to draw string"))); //705
    m_currentFont->drawString(m_context, getString(textgroup, textId), x, y, anchor);
}

int Resources::playAudio(const std::string& id, float volume, bool looping, int track) const //743 | This EXISTS in RCS but has no code.
{
    if (!m_audioOutput) //745
        throwError(Exception(Format("Trying to play audio clip but no audio output has been created"))); //746

    std::map<std::string, P(AudioClip)>::const_iterator it = m_audioClips.find(id); //748

    if (it != m_audioClips.end())
        return m_audioOutput->playClip(it->second, volume, looping, track); //751

    return -1;
}

void Resources::stopAudio(const std::string& id) //756-766
{
    if (!m_audioOutput)
        throwError(Exception(Format("Trying to stop audio clip but no audio output has been created"))); //759

    std::map<std::string, P(AudioClip)>::const_iterator it = m_audioClips.find(id); //761

    if (it != m_audioClips.end())
        m_audioOutput->stopClip(m_audioClips[id]); //764
}

void Resources::stopAudio(int handle) //768-774
{
    if (!m_audioOutput) //770
        throwError(Exception(Format("Trying to stop audio clip but no audio output has been created"))); //771

    m_audioOutput->stopClip(handle); //773
}

void Resources::stopAllAudio() const //-799
{
    if (!m_audioOutput) //795
        throwError(Exception(Format("Trying to stop all audio clips but no audio output has been created"))); //796

    m_audioOutput->stopClips(); //798
}

bool Resources::isAudioPlaying(const std::string& id) const //801-812
{
    if (!m_audioOutput) //803
        return false;

    std::map<std::string, P(AudioClip)>::const_iterator it = m_audioClips.find(id); //806

    if (it != m_audioClips.end())
        return m_audioOutput->isClipPlaying(it->second); //809

    return false;
}

bool Resources::isAudioPlaying(int id) const //814
{
    if (m_audioOutput) //816
        return m_audioOutput->isClipPlaying(id); //816

    else
        return false; //819
}

int Resources::getSpriteWidth(const std::string& spriteId) const //822
{
    std::map<std::string, SpriteEntry>::const_iterator it = m_sprites.find(spriteId); //824
    if (it != m_sprites.end()) //?
    {
        if (it->second.m_type == SpriteEntry::SPRITE)
            return it->second.m_sprite->getWidth(); //829

        else if (it->second.m_type == SpriteEntry::COMPOSPRITE)
            return it->second.m_compoSprite->getWidth(); //833
    }

    return 0;
}

int Resources::getSpriteHeight(const std::string& spriteId) const //840
{
    std::map<std::string, SpriteEntry>::const_iterator it = m_sprites.find(spriteId); //842
    if (it != m_sprites.end()) //?
    {
        if (it->second.m_type == SpriteEntry::SPRITE)
            return it->second.m_sprite->getHeight(); //847

        else if (it->second.m_type == SpriteEntry::COMPOSPRITE)
            return it->second.m_compoSprite->getHeight(); //851
    }

    return 0;
}

int Resources::getSpritePivotX(const std::string& spriteId) const //858
{
    std::map<std::string, SpriteEntry>::const_iterator it = m_sprites.find(spriteId); //860
    if (it != m_sprites.end()) //?
    {
        if (it->second.m_type == SpriteEntry::SPRITE)
            return it->second.m_sprite->getPivotX(); //865

        else if (it->second.m_type == SpriteEntry::COMPOSPRITE)
            return it->second.m_compoSprite->getPivotX(); //869
    }

    return 0;
}

int Resources::getSpritePivotY(const std::string& spriteId) const //876
{
    std::map<std::string, SpriteEntry>::const_iterator it = m_sprites.find(spriteId); //878
    if (it != m_sprites.end()) //?
    {
        if (it->second.m_type == SpriteEntry::SPRITE)
            return it->second.m_sprite->getPivotX(); //883

        else if (it->second.m_type == SpriteEntry::COMPOSPRITE)
            return it->second.m_compoSprite->getPivotX(); //887
    }

    return 0;
}

const std::string& Resources::getString(const std::string& textgroup, const std::string& textId) const //894
{
    std::map<std::string, P(TextGroupSet)>::const_iterator it = m_textGroupSets.find(textgroup); //896

    if (it != m_textGroupSets.end())
        return it->second->getTextGroup(m_useLocale)->get(textId); //899

    return textId; //904
}

int Resources::getStringWidth(const std::string& str, int offset, int length) const //907-913
{
    if (!m_currentFont)
        throwError(Exception(Format("No font is set while trying to get string width"))); //910

    return m_currentFont->getStringWidth(str, offset, length);
}

int Resources::getFontMaxAscending() const //915-921
{
    if (!m_currentFont)
        throwError(Exception(Format("No font is set while trying to get font max ascending"))); //918

    return m_currentFont->getMaxAscending();
}

int Resources::getFontMaxDescending() const //923-929
{
    if (!m_currentFont)
        throwError(Exception(Format("No font is set while trying to get font max descending"))); //926

    return m_currentFont->getMaxDescending();
}

int Resources::getFontLeading() const //931-937
{
    if (!m_currentFont)
        throwError(Exception(Format("No font is set while trying to get font leading"))); //934

    return m_currentFont->getLeading();
}

int Resources::getFontTracking() const //939-945
{
    if (!m_currentFont)
        throwError(Exception(Format("No font is set while trying to get font tracking"))); //942

    return m_currentFont->getTracking();
}

int Resources::getFontHeight() const //947-953
{
    if (!m_currentFont)
        throwError(Exception(Format("No font is set while trying to get font height!"))); //950 | Why an exclaimation mark?

    return m_currentFont->getHeight();
}

float Resources::getMasterVolume() const //955-961
{
    if (m_audioOutput) //957
        return m_audioOutput->getMasterVolume();
    
    return 0.0;
}

void Resources::setMasterVolume(float volume) const //963-966
{
    if (m_audioOutput) //965
        m_audioOutput->setMasterVolume(volume);
}

bool Resources::startAudioOutput() //969-975
{
    if (!m_audioOutput) //971
        throwError(Exception(Format("Trying to start audio output but no audio output has been created"))); //972

    return m_audioOutput->startOutput();
}

void Resources::stopAudioOutput()
{
    if (m_audioOutput) //979
        m_audioOutput->stopOutput();
}

bool Resources::startAudioInput() //983-989
{
    if (!m_audioInput) //985
        throwError(Exception(Format("Trying to start audio input but no audio output has been created"))); //986

    return m_audioInput->startInput();
}

void Resources::stopAudioInput() //992-995
{
    if (m_audioInput) //993
        return m_audioInput->stopInput();
}

AudioOutput* Resources::getAudioOutput() const //997-1000
{
    return m_audioOutput; //999
}

AudioInput* Resources::getAudioInput() const //1002-1005
{
    return m_audioInput; //1004
}

AudioClip* Resources::getAudioClip(const std::string& id) const //1007-1011
{
    std::map<std::string, P(AudioClip)>::const_iterator it = m_audioClips.find(id); //1009
    return it->second; //1010
}

const Rect& Resources::getClipRect() const //1013-1016
{
    return m_clipRect; //1015
}

void Resources::setClipRect(const Rect& clip) //1018
{
    m_context->setClipRect(clip);
    m_context->getRenderState2D().setClip(clip); //1021
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
        if (spriteIt->second.m_type == SpriteEntry::COMPOSPRITE)
        {
            std::map<std::string, P(CompoSpriteSet)>::const_iterator compoIt = m_composites.find(spriteIt->first);
            return compoIt->second;
        }
    }

    return 0;
}

}