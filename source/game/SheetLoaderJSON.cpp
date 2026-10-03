#include <game/SheetLoaderJSON.h>
#include <game/Sprite.h>
#include <game/SpriteSheet.h>
#include <game/CompoSprite.h>
#include <game/CompoSpriteSet.h>
#include <io/BundleInputStream.h>
#include <io/PathName.h>
#include <lang/Log.h>
//#include <lang/unique_ptr.h> //Not yet decompiled.

using namespace game;
using namespace gr;
using namespace io;
using namespace lang;
using namespace math;
using namespace util;

Sprite* getSprite(const std::string& name, const std::map<std::string, P(SpriteSheet)> sheets) //17 | called by loadCompositeSet | Correct?
{
	for (std::map<const std::string, P(SpriteSheet)>::const_iterator it = sheets.begin(); it != sheets.end(); it++) //19
	{
		Sprite* sprite = it->second->getSprite(name); //21

		if (sprite)
			return sprite;
	}

	return 0;
}

void loadJSONSheet(Context* context, const JSON& sheet, SpriteSheet& dstSheet, const std::string& filename) //32-131 | TODO | called by loadSheet, loadSheets and loadSheetClips, sub_35FB20 on Android GP
{
	/*if (filename.empty()) //37
	{
		const std::string& image = sheet.get("meta").getString("image"); //40
		const PathName& parentPath = PathName(image).parent(); //41
		const std::string& imagePath = PathName(parentPath).toString(); //42
		dstSheet.loadImage(context, imagePath); //43
	}

	if (sheet.get("meta").getString("app") != "http://www.texturepacker.com") //49
	{
		if (sheet.hasArray("frames"))
		{
			const std::vector<JSON>& frames = sheet.getArray("frames"); //55

			for (size_t i = 0; i < frames.size(); i++) //57
			{
				const JSON& f = frames[i]; //59

				const std::string& id = f.getString("filename"); //62

				id + PathName(id).basename(); //65 | ?

				const JSON& frame = f.get("frame"); //67
				int x = frame.getInt("x"); //68
				int y = frame.getInt("y"); //69
				int width = frame.getInt("w"); //70
				int height = frame.getInt("h"); //71

				Sprite::SourceRotation rotationUsed; //74

				dstSheet.createSprite(filename, x, y, width, height, width / 2, height / 2, rotationUsed);
			}
		}

		else
			throwError(Exception(Format("Unsupported TexturePacker JSON sheet format (use JSON Array format instead)"))); //91
	}

	else
	{
		if (sheet.get("meta").getString("app").find("Adobe") && sheet.get("meta").getString("app").find("ArtPacker")) //94
		{
			const std::vector<JSON>& frames = sheet.getArray("frames"); //97

			for (size_t i = 0; i < frames.size(); i++) //99
			{
				const JSON& f = frames[i]; //101
				const std::string& id = f.getString("filename"); //104
				const JSON& frame = f.get("frame"); //106
				int x = frame.getInt("x"); //107
				int y = frame.getInt("y"); //108
				int width = frame.getInt("w"); //109
				int height = frame.getInt("h"); //110

				int pivotX = frame[0].getInt("x"); //113
				int pivotY = frame[1].getInt("y"); //114

				const JSON& pivot = frame.get("pivot"); //118
			}
		}

		else
			//throwError(Exception(Format("Unsupported JSON sheet format"))); //129
	}*/
	assert("void game::loadJSONSheet(gr::Context* context, const util::JSON& sheet, game::SpriteSheet& dstSheet, const std::string& filename) was not yet decompiled.");
}

SpriteSheet* loadJSONSheet(Context* context, const JSON& sheet, const std::string& filename) //133-138 | TODO
{
	/*lang::unique_ptr<SpriteSheet> dstSheet; //135
	loadJSONSheet(context, sheet, filename);
	return *dstSheet;*/
	assert("game::SpriteSheet* game::loadJSONSheet(gr::Context* context, const util::JSON& sheet, const std::string& filename) requires lang::unique_ptr decompiled, returning null.");
	return 0;
}

namespace game
{

SpriteSheet* SheetLoaderJSON::loadSheet(Context* context, const std::string& filename, bool isRaw) //144-148
{
	BundleInputStream in(filename); //146
	return loadJSONSheet(context, toJSON(in), filename); //147
}

SpriteSheet* SheetLoaderJSON::loadSheet(Context* context, InputStream& clipInputStream, InputStream& imageInputstream, bool isRaw) //150-157
{
	/*lang::unique_ptr<SpriteSheet> dstSheet; //152
	dstSheet->loadImage(context, clipInputStream); //153

	loadJSONSheet(context, decryptJSON(imageInputstream, isRaw), *dstSheet, ""); //155
	return *dstSheet;*/

	assert("game::SpriteSheet* game::SheetLoaderJSON::loadSheet(gr::Context* context, io::InputStream& clipInputStream, io::InputStream& imageInputstream, bool isRaw) requires lang::unique_ptr decompiled, returning null.");
	return 0;
}

std::vector<P(SpriteSheet)> SheetLoaderJSON::loadSheets(Context* context, const std::string& filename, bool isRaw) //159-179 | Correct?
{
	std::vector<P(SpriteSheet)> sheets; //161
	BundleInputStream in(filename); //163
	JSON json = toJSON(in); //164
	if (json.has("spriteSheets"))
	{
		std::vector<JSON>& jsons = json.getArray("spriteSheets"); //167
		for (size_t i = 0; i < jsons.size(); i++) //168
			loadJSONSheet(context, jsons[i], filename); //170
	}
	else
		loadJSONSheet(context, json, filename); //175

	return sheets;
}

void SheetLoaderJSON::loadSheetClips(const std::string& filename, SpriteSheet* dstSheet, bool isRaw) // 181-185
{
	BundleInputStream in(filename); //183
	loadJSONSheet(0, toJSON(in), filename); //184
}

CompoSpriteSet* SheetLoaderJSON::loadCompositeSet(const std::string& filename, const std::map<std::string, P(SpriteSheet)>& sheetData, bool isRaw) //187
{
	BundleInputStream in(filename); //189
	return loadCompositeSet(in, sheetData, isRaw); //190
}

CompoSpriteSet* SheetLoaderJSON::loadCompositeSet(InputStream& compoInputStream, const std::map<std::string, P(SpriteSheet)>& sheetData, bool isRaw) //193-277 | Correct?
{
	/*lang::unique_ptr<CompoSpriteSet> dstSet; //195 | We'll use lang so it won't use std's

	const JSON& sheet = decryptJSON(compoInputStream, isRaw); //197
	const JSON& meta = sheet.get("meta"); //198
	const std::string& appName = meta.getString("app"); //199

	if (appName.find("Adobe") != -1 && appName.find("ArtPacker") != -1)
	{
		if (sheet.has("compo"))
		{
			const std::vector<JSON>& compos = sheet.getArray("compo"); //208
			for (size_t i = 0; i < compos.size(); i++) //209
			{
				const JSON& c = compos[i].get("sprites"); //212
				P(CompoSprite) compoSprite; //213

				const std::vector<JSON>& sprites = c.getArray("sprites"); //215

				for (int i = 0; i < sprites.size(); i++) //217
				{
					const JSON& s = sprites[i]; //219
					const std::string& spriteId = s.getString("name"); //220
					float2 pos = float2(s.getFloat("x"), s.getFloat("y")); //221
					float2 scale = float2(1.0f, 1.0f); //222
					float2 flip = float2(1.0f, 1.0f); //223
					float angle = 0.0; //224
					std::string compoId = s.has("id") ? s.getString("id") : ""; //225

					if (s.has("scale"))
					{
						const JSON& sc = s.get("scale"); //232
						scale = sc.isArray() ? float2(sc[0].getFloat(), sc[1].getFloat()) : float2(sc.getFloat(), sc.getFloat());
					}

					if (s.has("flip"))
					{
						const JSON& fl = s.get("flip"); //246
						flip = float2(fl[0].getFloat(), fl[1].getFloat());
					}

					if (s.has("angle"))
						angle = s.getFloat("angle") * 0.017453f;

					Sprite* sprite = getSprite(spriteId, sheetData); //254
					if (sprite)
						compoSprite->addSprite(spriteId, compoId, sprite, pos, scale, flip, angle);
					else
						LANG_LOG("", LANG_LOG_PRIORITY_ERROR, "Could not find sprite %s", spriteId); //262
				}

				dstSet->add(c.getString("name"), compoSprite); //268
			}
		}
	}

	else
		throwError(Exception(Format("Unsupported JSON composprite format"))); //274

	return &*dstSet;*/

	assert("game::CompoSpriteSet* SheetLoaderJSON::loadCompositeSet(io::InputStream& compoInputStream, const std::map<std::string, P(game::SpriteSheet)>& sheetData, bool isRaw) requires lang::unique_ptr decompiled, returning null.");
	return 0;
}

JSON* SheetLoaderJSON::loadCompositeInfo(const std::string& filename, bool isRaw) //279-317
{
	/*lang::unique_ptr<JSON> dstSet; //281

	BundleInputStream in(filename); //283

	const JSON& sheet = toJSON(in); //285
	const JSON& meta = sheet.get("meta"); //286
	const std::string& appName = meta.getString("app"); //287

	if (appName.find("Adobe") != -1 && appName.find("ArtPacker") != -1)
	{
		const std::string& image = meta.getString("image"); //293 | Unused?
		const std::string& sheetName = meta.getString("sheet"); //294 | Unused?
		
		if (sheet.has("compo")) //Unused behaviour?
		{
			const std::vector<JSON>& compos = sheet.getArray("compo"); //300
			for (size_t i = 0; i < compos.size(); i++) //301
			{
				const JSON& c = compos[i].get("sprites"); //303

				JSON compo; //305
				compo["sprites"] = c.getArray("sprites");
				compo["sheet"] = sheetName;
				compo["name"] = c.getString("name");
				dstSet = compo;
			}
		}
	}
	else
		throwError(Exception(Format("Unsupported JSON composprite format"))); //314

	return &*dstSet;*/

	assert("util::JSON* SheetLoaderJSON::loadCompositeInfo(const std::string& filename, bool isRaw) requires lang::unique_ptr decompiled, returning null.");
	return 0;
}

}