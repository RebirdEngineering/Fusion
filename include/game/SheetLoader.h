#ifndef _GAME_SHEETLOADER_H
#define _GAME_SHEETLOADER_H

#include <lang/Optional.h>
#include <util/JSON.h>
#include <io/InputStream.h>

namespace gr
{
	class Context;
}

namespace game
{
	class CompoSpriteSet;
	class SpriteSheet;

	class SheetLoader : //23
		public lang::Object
	{
	public:
		virtual SpriteSheet* loadSheet(gr::Context* context, const std::string& filename) = 0; //32

		virtual SpriteSheet* loadSheet(gr::Context* context, io::InputStream& clipInputStream, io::InputStream& imageInputstream) = 0; //40

		virtual std::vector<P(SpriteSheet)> loadSheets(gr::Context* context, const std::string& filename) = 0; //47

		virtual void loadSheetClips(const std::string& filename, SpriteSheet* dstSheet) = 0; //54

		virtual CompoSpriteSet* loadCompositeSet(const std::string& filename, const std::map<std::string, P(SpriteSheet)>& sheetData) = 0; //61

		virtual CompoSpriteSet* loadCompositeSet(io::InputStream& compoInputStream, const std::map<std::string, P(SpriteSheet)>& sheetData) = 0; //68

		virtual util::JSON* loadCompositeInfo(const std::string& filename) = 0; //74

		static void setEncryptionKey(const lang::optional<std::vector<unsigned char>>& encryptionKey); //77

		static void setCompressionEnabled(bool compressionEnabled); //80

	protected:
		util::JSON decryptJSON(io::InputStream& in, bool isRaw); //83

	private:
		static lang::optional<std::vector<unsigned char>> m_emptyKey; //86
		static lang::optional<std::vector<unsigned char>> m_encryptionKey; //87
		static bool m_compressionEnabled; //88
	};
}

#endif