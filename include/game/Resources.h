#ifndef _GAME_RESOURCES_H
#define _GAME_RESOURCES_H

#include <game/SpriteProvider.h>
#include <game/Anchor.h>
#include <audio/AudioConfiguration.h>
#include <io/PathName.h>
#include <gr/Color.h>

namespace audio
{
	class AudioClip;
	class AudioInput;
	class AudioOutput;
	class CompositeAudioClip;
}

namespace io
{
	class InputStream;
}

namespace gr
{
	class Context;
}

namespace game
{
	class CompoSprite;
	class CompoSpriteSet;
	class BitmapFont;
	class IFont;
	class SystemFont;
	class SpriteSheet;
	class TextGroupSet;

class Resources :
	public lang::Object, public SpriteProvider //38
{
public:	
	Resources(gr::Context* context); //46

	~Resources(); //51

	void setPath(const std::string& path); //56

	void addCompoSpriteSet(const std::string& name, CompoSpriteSet* composet); //62 | assumption

	void addSpriteSheet(const std::string& name, SpriteSheet* sheet); //68

	SpriteSheet* createSpriteSheet(const std::string& filename, bool forceLoad = false, bool loadImage = true); //75

	CompoSpriteSet* createCompoSpriteSet(const std::string& filename, bool forceLoad = false); //82

	CompoSpriteSet* createCompoSpriteSet(const std::string& filename, P(io::InputStream) in, bool forceLoad = false); //89

	void captureSprite(const std::string& spriteId); //95

	BitmapFont* createBitmapFont(const std::string& filename, bool forceLoad = false); //102

	SystemFont* createSystemFont(const std::string& id, const std::string& fontName, int fontSize, const gr::Color& fontColor, int style, bool forceLoad = false); //209

	TextGroupSet* createTextGroupSet(const std::string& filename, bool forceLoad = false); //116
	
	audio::AudioOutput* createAudioOutput(const audio::AudioConfiguration& conf); //123

	audio::AudioInput* createAudioInput(const audio::AudioConfiguration& conf); //130

	audio::AudioClip* createAudio(const std::string& filename, const std::string& id, bool stream); //137

	audio::AudioClip* createAudioFromAppData(const std::string& filename, const std::string& id, bool stream); //144

	audio::AudioClip* createAudio(const std::string& filename, const void* data, int size, const audio::AudioConfiguration& conf); //149

	audio::CompositeAudioClip* createCompositeAudio(const std::string& id, const std::vector<P(audio::AudioClip)>& clips); //156

	void queueCreateSpriteSheet(const std::string& filename); //162 | Not defined on iOS. Param name recovered from ABFM

	void queueCreateCompoSpriteSet(const std::string& filename); //168 | Not defined on iOS. Param name recovered from ABFM

	void queueCreateBitmapFont(const std::string& filename); //174 | Not defined on iOS. Param name recovered from ABFM

	void queueCreateTextGroupSet(const std::string& filename); //180 | Not defined on iOS. Param name recovered from ABFM

	void queueCreateAudio(const std::string&, const std::string& filename); //186 | Not defined on iOS. Param name recovered from ABFM

	int queueSize() const; //191

	void loadQueued(); //198

	void loadAllQueued(); //204

	void releaseSpriteSheet(const std::string& filename, bool releaseOnlyImages = false); //209

	void releaseCompoSpriteSet(const std::string& filename); //214

	void releaseFont(const std::string& filename); //219

	void releaseTextGroupSet(const std::string& filename); //224

	void releaseAudioOutput(); //229

	void releaseAudioInput(); //234

	void releaseAudio(const std::string& id); //239

	void loadLocale(const std::string& textGroupSet, const std::string& locale); //244

	void useFont(const std::string& fontName); //249

	void useLocale(const std::string& localeName); //254

	void drawSprite(const std::string& spriteId, float x, float y, Anchor anchor) const; //259

	void drawSprite(const std::string& spriteId, float x, float y, float width, float height, Anchor anchor) const; //264

	void drawString(const std::string& textgroup, const std::string& textId, float x, float y, Anchor anchor) const; //269

	void drawString(const std::string& textgroup, const std::string& textId, int offset, int length, float x, float y, Anchor anchor) const; //274 | Param name recovered from ABFM

	void drawNumber(float value, int digitCount, float x, float y, Anchor anchor) const; //279 | Not on iOS at all.

	int playAudio(const std::string& id, float height, bool looping, int track) const; //284

	void stopAudio(const std::string& id); //289

	void stopAudio(int handle); //294

	void resumeAllAudio() const; //299

	void pauseAllAudio() const; //304

	void stopAllAudio() const; //309

	bool isAudioPlaying(const std::string& id) const; //314

	bool isAudioPlaying(int id) const; //319

	int getSpriteWidth(const std::string& spriteId) const; //324

	int getSpriteHeight(const std::string& spriteId) const; //329

	int getSpritePivotX(const std::string& spriteId) const; //334
	
	int getSpritePivotY(const std::string& spriteId) const; //339

	int getStringWidth(const std::string& str, int offset, int length) const; //344

	IFont* getFont() const; //349

	const std::string& getFontName() const; //354

	int getFontMaxAscending() const; //359

	int getFontMaxDescending() const; //364

	int getFontHeight() const; //369

	int getFontLeading() const; //374

	int getFontTracking() const; //379

	TextGroupSet* getTextGroupSet(const std::string& textGroupSet) const; //384

	const std::string& getString(const std::string& textgroup, const std::string& textId) const; //389

	const std::string& getLocale() const; //394

	Sprite* getSprite(const std::string& spriteId); //399

	SpriteSheet* getSpriteSheet(const std::string& sheetId) const; //404

	SpriteSheet* findSpriteSheet(const std::string& spriteId) const; //409

	CompoSprite* getCompoSprite(const std::string& spriteId) const; //414

	CompoSpriteSet* getCompoSpriteSet(const std::string& spriteId) const; //419

	CompoSpriteSet* findCompoSpriteSet(const std::string& spriteId) const; //424

	float getMasterVolume() const; //430

	void setMasterVolume(float volume) const; //436

	bool startAudioOutput(); //442

	void stopAudioOutput(); //448

	bool startAudioInput(); //454

	void stopAudioInput(); //460

	audio::AudioOutput* getAudioOutput() const; //465

	audio::AudioInput* getAudioInput() const; //470

	audio::AudioClip* getAudioClip(const std::string& id) const; //475

	const gr::Rect& getClipRect() const; //480

	void setClipRect(const gr::Rect& clip); //485

	struct QueueEntry //488
	{
		enum AssetType { SPRITESHEET, COMPOSPRITESET, BITMAPFONT, TEXTGROUPSET, AUDIOCLIP }; //491
		std::string m_filename; //492
		std::string m_id; //492
		AssetType m_type; //493
	};

	struct SpriteEntry //497
	{
		enum SpriteType { UNDEFINED, SPRITE, COMPOSPRITE }; //500

		SpriteEntry(); //502

		SpriteType m_type; //504
		std::string m_sheetName; //505

		union //507
		{
			Sprite* m_sprite; //509
			CompoSprite* m_compoSprite; //510
		};
	};
private:
	gr::Context* m_context; //514
	gr::Rect m_clipRect; //515
	P(audio::AudioOutput) m_audioOutput; //516
	P(audio::AudioInput) m_audioInput; //517

	IFont* m_currentFont; //519
	std::string m_currentFontName; //520
	io::PathName m_path; //521
	std::string m_useLocale; //522

	std::map<std::string, P(TextGroupSet)> m_textGroupSets; //524
	std::map<std::string, P(SpriteSheet)> m_sheets; //525
	std::map<std::string, P(CompoSpriteSet)> m_composites; //526
	std::map<std::string, P(IFont)> m_fonts; //527
	std::map<std::string, P(audio::AudioClip)> m_audioClips; //528
	std::map<std::string, SpriteEntry> m_sprites; //529

	std::vector<QueueEntry> m_queue; //531
	
	void addSpritesToRegistry(SpriteSheet* sheet, const std::string& name); //533
	void removeSpritesFromRegistry(SpriteSheet* sheet); //534
	void addSpritesToRegistry(CompoSpriteSet* composet, const std::string& name); //535
	void removeSpritesFromRegistry(CompoSpriteSet* composet); //536

	audio::AudioClip* createAudio(P(io::InputStream) in, const std::string& id, bool stream); //538
};

}

#endif