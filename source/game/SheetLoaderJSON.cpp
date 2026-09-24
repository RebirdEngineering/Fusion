#include <game/SheetLoaderJSON.h>
#include <game/Sprite.h>
#include <game/SpriteSheet.h>
#include <game/CompoSpriteSet.h>
#include <io/BundleInputStream.h>
#include <io/PathName.h>

using namespace game;
using namespace gr;
using namespace io;
using namespace util;

Sprite* getSprite(const std::string& name, const std::map<std::string, P(SpriteSheet)> sheets) //called by loadCompositeSet
{
	std::map<const std::string, P(SpriteSheet)>::iterator it;
	assert("game::Sprite* getSprite(const std::string& name, const std::map<std::string, P(SpriteSheet)> sheets) was not yet decompiled. Returning 0.");
	return 0;
}

void loadJSONSheet(Context* context, const JSON& sheet, SpriteSheet& dstSheet, const std::string& filename) //TODO | called by loadSheet, loadSheets and loadSheetClips
{
	const std::string& image = sheet.getString("image");
	const PathName& parentPath = PathName(image).parent();
	const PathName& imagePath = PathName(parentPath).toString();
	const std::vector<JSON>& frames = sheet.getArray("frames");
	size_t i = frames.size();
	const JSON& frame = frames[i].get("frame");

	int x = frame.getInt("x");
	int y = frame.getInt("y");

	int pivotX = frame[0].getInt("x");
	int pivotY = frame[1].getInt("y");

	int width = frame.getInt("w");
	int height = frame.getInt("h");

	//const JSON& f = ;
	const std::string& id = frame.getString("filename");
	const JSON& pivot = frame.get("pivot");

	//Sprite::SourceRotation rotationUsed = .getBool("rotation");
}

SpriteSheet* loadJSONSheet(Context* context, const JSON& sheet, const std::string& filename) //TODO
{
	//lang::unique_ptr<SpriteSheet> dstSheet; //135
	assert("game::SpriteSheet* loadJSONSheet(gr::Context* context, const util::JSON& sheet, const std::string& filename) was not yet decompiled. Returning 0.");
	return 0;
}

namespace game
{

SpriteSheet* SheetLoaderJSON::loadSheet(Context* context, const std::string& filename, bool isRaw) //144
{
	BundleInputStream in(filename); //146
	return loadJSONSheet(context, toJSON(in), filename);
}

SpriteSheet* SheetLoaderJSON::loadSheet(Context* context, const std::string& filename)
{
	return loadSheet(context, filename, false);
}

SpriteSheet* SheetLoaderJSON::loadSheet(Context* context, InputStream& clipInputStream, InputStream& imageInputstream) //TODO
{
	//lang::unique_ptr<SpriteSheet> dstSheet;
	assert("SpriteSheet* SheetLoaderJSON::loadSheet(Context* context, InputStream& clipInputStream, InputStream& imageInputstream) is not yet decompiled. Returning 0.");
	return 0;
}

std::vector<P(SpriteSheet)> SheetLoaderJSON::loadSheets(Context* context, const std::string& filename) //TODO
{
	std::vector<P(SpriteSheet)> sheets;
	/*BundleInputStream in(filename);
	JSON json; //= toJSON(in);
	if (json.has("spriteSheets"))
		std::vector<JSON>& jsons = json.getArray("spriteSheets");
	size_t i = jsons;*/
	//loadJSONSheet()
	assert("std::vector<P(SpriteSheet)> SheetLoaderJSON::loadSheets(Context* context, const std::string& filename) is not yet decompiled. Returning empty Ptr vector.");
	return sheets;
}

void SheetLoaderJSON::loadSheetClips(const std::string& filename, SpriteSheet* dstSheet, bool isRaw) //TODO
{
	BundleInputStream in(filename);
}

CompoSpriteSet* SheetLoaderJSON::loadCompositeSet(const std::string& filename, const std::map<std::string, P(SpriteSheet)> sheetData, bool isRaw)
{
	BundleInputStream in(filename);
	return loadCompositeSet(in, sheetData, isRaw);
}

CompoSpriteSet* SheetLoaderJSON::loadCompositeSet(InputStream& compoInputStream, const std::map<std::string, P(SpriteSheet)> sheetData, bool isRaw)
{
	/*
	//lang::unique_ptr<CompoSpriteSet> dstSet;
	const JSON& sheet = decryptJSON(compoInputStream, isRaw);
	const JSON& meta = sheet.get("meta");
	const std::string& appName = sheet.getString("app");

	if (appName.find("Adobe") && appName.find("ArtPacker"))
		throwError(Exception(Format("Unsupported JSON composprite format")));

	if (sheet.has("compo"))
	{
		const std::vector<JSON>& compos = sheet.getArray("compo");
	}
	size_t i;
	const JSON& c = compos.getArray("sprites");
	P(CompoSprite) compoSprite = compos.getArray("sprites");

	const std::vector<JSON> sprites = compos.getArray("sprites");
	int i;

	std::string name;

	std::string s;
	std::string spriteId;
	/*float2 pos = .get("pos");
	float2 scale = .get("scale");
	float2 flip = .get("flip");
	float angle = .get("angle");
	std::string compoId;
	Sprite* sprite;
	const JSON& sc;	
	const JSON& fl;	*/
	assert("std::vector<P(SpriteSheet)> SheetLoaderJSON::loadSheets(Context* context, const std::string& filename) is not yet decompiled. Returning 0.");
	return 0;
	//return CompoSpriteSet();
}

/*JSON* SheetLoaderJSON::loadCompositeInfo(const std::string& filename, bool isRaw)
{
	//BundleInputStream in(filename);
	//const JSON& sheet = toJSON(in)
	//return loadCompositeInfo(in, sheetData, isRaw);
}*/

}