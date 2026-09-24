#ifndef _GAME_SHEETLOADERJSON_H
#define _GAME_SHEETLOADERJSON_H

#include <game/SheetLoader.h>

namespace game
{

class SheetLoaderJSON :
	public SheetLoader
{
public:
	SpriteSheet* loadSheet(gr::Context* context, const std::string& filename);

	SpriteSheet* loadSheet(gr::Context* context, io::InputStream& clipInputStream, io::InputStream& imageInputStream);

	std::vector<P(SpriteSheet)> loadSheets(gr::Context* context, const std::string& filename);

	void loadSheetClips(const std::string& filename, SpriteSheet* dstSheet);

	CompoSpriteSet* loadCompositeSet(const std::string& filename, const std::map<std::string, P(SpriteSheet)>& sheetData);

	CompoSpriteSet* loadCompositeSet(io::InputStream& compoInputStream, const std::map<std::string, P(SpriteSheet)>& sheetData);

	util::JSON* loadCompositeInfo(const std::string& filename);

	SpriteSheet* loadSheet(gr::Context* context, const std::string& filename, bool isRaw);
	SpriteSheet* loadSheet(gr::Context* context, io::InputStream& clipInputStream, io::InputStream& imageInputStream, bool isRaw);
	std::vector<P(SpriteSheet)> loadSheets(gr::Context* context, const std::string& filename, bool isRaw);
	void loadSheetClips(const std::string& filename, SpriteSheet* dstSheet, bool isRaw);
	CompoSpriteSet* loadCompositeSet(const std::string& filename, const std::map<std::string, P(SpriteSheet)> sheetData, bool isRaw);
	CompoSpriteSet* loadCompositeSet(io::InputStream& compoInputStream, const std::map<std::string, P(SpriteSheet)> sheetData, bool isRaw);
	util::JSON* loadCompositeInfo(const std::string& filename, bool isRaw);
};

}

#endif