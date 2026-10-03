#ifndef _GAME_SHEETLOADERJSON_H
#define _GAME_SHEETLOADERJSON_H

#include <game/SheetLoader.h>

namespace game
{

class SheetLoaderJSON : //17
	public SheetLoader
{
public:
	SpriteSheet* loadSheet(gr::Context* context, const std::string& filename) //22
	{
		return loadSheet(context, filename, false); //24 | Set encryption toggle compiler define?
	}

	SpriteSheet* loadSheet(gr::Context* context, io::InputStream& clipInputStream, io::InputStream& imageInputStream) //27
	{
		return loadSheet(context, clipInputStream, imageInputStream, false); //29 | Set encryption toggle compiler define?
	}

	std::vector<P(SpriteSheet)> loadSheets(gr::Context* context, const std::string& filename) //32
	{
		return loadSheets(context, filename, false); //34 | Set encryption toggle compiler define?
	}

	void loadSheetClips(const std::string& filename, SpriteSheet* dstSheet) //37
	{
		return loadSheetClips(filename, dstSheet, false); //39 | Set encryption toggle compiler define?
	}

	CompoSpriteSet* loadCompositeSet(const std::string& filename, const std::map<std::string, P(SpriteSheet)>& sheetData) //42
	{
		return loadCompositeSet(filename, sheetData, false); //44 | Set encryption toggle compiler define?
	}

	CompoSpriteSet* loadCompositeSet(io::InputStream& compoInputStream, const std::map<std::string, P(SpriteSheet)>& sheetData) //46
	{
		return loadCompositeSet(compoInputStream, sheetData, false); //48 | Set encryption toggle compiler define?
	}

	util::JSON* loadCompositeInfo(const std::string& filename) //51
	{
		return loadCompositeInfo(filename, false); //53 | Set encryption toggle compiler define?
	}

	SpriteSheet* loadSheet(gr::Context* context, const std::string& filename, bool isRaw); //61
	SpriteSheet* loadSheet(gr::Context* context, io::InputStream& clipInputStream, io::InputStream& imageInputStream, bool isRaw); //61
	std::vector<P(SpriteSheet)> loadSheets(gr::Context* context, const std::string& filename, bool isRaw); //63
	void loadSheetClips(const std::string& filename, SpriteSheet* dstSheet, bool isRaw); //64
	CompoSpriteSet* loadCompositeSet(const std::string& filename, const std::map<std::string, P(SpriteSheet)>& sheetData, bool isRaw); //65
	CompoSpriteSet* loadCompositeSet(io::InputStream& compoInputStream, const std::map<std::string, P(SpriteSheet)>& sheetData, bool isRaw); //66
	util::JSON* loadCompositeInfo(const std::string& filename, bool isRaw); //67
};

}

#endif