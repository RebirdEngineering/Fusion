#ifndef _GAME_SHEETLOADERDAT_H
#define _GAME_SHEETLOADERDAT_H

#include <game/SheetLoader.h>

namespace game
{
class SheetLoaderDAT :
	public SheetLoader
{
public:
	SpriteSheet* loadSheet(gr::Context* context, const std::string& filename);
	SpriteSheet* loadSheet(gr::Context* context, io::InputStream& clipInputStream, io::InputStream& imageInputstream);
	std::vector<P(SpriteSheet)> loadSheets(gr::Context* context, const std::string& filename);
	void loadSheetClips(const std::string& filename, SpriteSheet* dstSheet);
	CompoSpriteSet* loadCompositeSet(const std::string& filename, const std::map<std::string, P(SpriteSheet)>& sheetData);
	CompoSpriteSet* loadCompositeSet(io::InputStream& compoInputStream, const std::map<std::string, P(SpriteSheet)>& sheetData);
	util::JSON* loadCompositeInfo(const std::string& filename);
};

}

#endif