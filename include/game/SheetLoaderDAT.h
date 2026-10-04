#ifndef _GAME_SHEETLOADERDAT_H
#define _GAME_SHEETLOADERDAT_H

#include <game/SheetLoader.h>

namespace game
{
class SheetLoaderDAT : //13
	public SheetLoader
{
public:
	SpriteSheet* loadSheet(gr::Context* context, const std::string& filename); //17
	SpriteSheet* loadSheet(gr::Context* context, io::InputStream& clipInputStream, io::InputStream& imageInputstream); //18
	std::vector<P(SpriteSheet)> loadSheets(gr::Context* context, const std::string& filename); //19
	void loadSheetClips(const std::string& filename, SpriteSheet* dstSheet); //20
	CompoSpriteSet* loadCompositeSet(const std::string& filename, const std::map<std::string, P(SpriteSheet)>& sheetData); //21
	CompoSpriteSet* loadCompositeSet(io::InputStream& compoInputStream, const std::map<std::string, P(SpriteSheet)>& sheetData); //22
	util::JSON* loadCompositeInfo(const std::string& filename); //23
};

}

#endif