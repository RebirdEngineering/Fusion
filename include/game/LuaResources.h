#ifndef _GAME_LUARESOURCES_H
#define _GAME_LUARESOURCES_H

#include <lua/LuaObject.h>
#include <game/Resources.h>

namespace lua
{
	class LuaState;
}

namespace game
{
class LuaResources : public lua::LuaObject //13 | Demangled symbols suggest strings are not const&
{
public:
	LuaResources(lua::LuaState* lua, gr::Context* context); //16
	~LuaResources(); //16

	void setPath(std::string filename); //19
	int createSpriteSheet(lua::LuaState* lua); //20
	int createCompoSpriteSet(lua::LuaState* lua); //21
	int createBitmapFont(lua::LuaState* lua); //22
	int createSystemFont(lua::LuaState* lua); //23
	int createTextGroupSet(lua::LuaState* lua); //24
	void captureSprite(std::string spriteId); //25

	void createAudioOutput(float channels, float bitrate, float samplerate); //27
	void createAudioInput(float channels, float bitrate, float samplerate); //28

	int createAudio(lua::LuaState* lua); //30
	void createCompositeAudio(std::string id, LuaTable clipids); //31

	int releaseSpriteSheet(lua::LuaState* lua); //33
	void releaseCompoSpriteSet(std::string filename); //34
	void releaseFont(std::string filename); //35
	void releaseTextGroupSet(std::string filename); //36
	int releaseAudio(lua::LuaState* lua); //37

	void loadLocale(std::string textGroupSet, std::string locale); //39
	void useLocale(std::string locale); //40
	void useFont(std::string fontName); //41
	LuaTable getAvailableSystemFonts(); //42

	int drawSprite(lua::LuaState* lua); //44
	int drawCompoSprite(lua::LuaState* lua); //45
	int drawString(lua::LuaState* lua); //46

	void setClipRect(float x, float y, float w, float h); //48
	int getClipRect(lua::LuaState* lua); //49

	int playAudio(lua::LuaState* lua); //59
	int stopAudio(lua::LuaState* lua); //60

	int isAudioPlaying(lua::LuaState* lua); //71
	
	void stopAllAudio(); //73
	
	int getSpriteBounds(lua::LuaState* lua); //75
	int getSpritePivot(lua::LuaState* lua); //76
	int getCompoSpriteBounds(lua::LuaState* lua); //77
	int getCompoSpriteData(lua::LuaState* lua); //78

	int getCompoSpriteEntry(lua::LuaState* lua); //96

	int setCompoSpriteEntry(lua::LuaState* lua); //113

	std::string getString(std::string group, std::string textId); //115
	std::string getLocale(); //116
	float getStringWidth(std::string str); //117
	float getFontMaxAscending(); //118
	float getFontMaxDescending(); //119
	float getFontLeading(); //120
	float getFontTracking(); //121
	float getFontHeight(); //122
	
	bool startAudioOutput(); //124
	void stopAudioOutput(); //125

	void startAudioInput(); //127
	void stopAudioInput(); //128
	
	float getMasterVolume(); //130
	void setMasterVolume(float volume); //131
	void setTrackVolume(float track, float volume); //132
	float getTrackVolume(float track); //133
	
	bool openURL(std::string url); //135

	Resources* getResources(); //140

private:
	Resources m_resources; //143
};

}

#endif