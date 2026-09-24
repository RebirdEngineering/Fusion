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

	class SheetLoader :
		public lang::Object
	{
	public:
		virtual SpriteSheet* loadSheet(gr::Context* context, const std::string& filename) = 0;

		virtual SpriteSheet* loadSheet(gr::Context* context, io::InputStream& clipInputStream, io::InputStream& imageInputstream) = 0;

		virtual std::vector<P(SpriteSheet)> loadSheets(gr::Context* context, const std::string& filename) = 0;

		virtual void loadSheetClips(const std::string& filename, SpriteSheet* dstSheet) = 0;

		virtual CompoSpriteSet* loadCompositeSet(const std::string& filename, const std::map<std::string, P(SpriteSheet)>& sheetData) = 0;

		virtual CompoSpriteSet* loadCompositeSet(io::InputStream& compoInputStream, const std::map<std::string, P(SpriteSheet)>& sheetData) = 0;

		virtual util::JSON* loadCompositeInfo(const std::string& filename) = 0;

		static void setEncryptionKey(const lang::optional<std::vector<unsigned char>>& encryptionKey);

		static void setCompressionEnabled(bool compressionEnabled);
	protected:
		util::JSON decryptJSON(io::InputStream& in, bool isRaw);
	private:
		static lang::optional<std::vector<unsigned char>> m_emptyKey;
		static lang::optional<std::vector<unsigned char>> m_encryptionKey;
		static bool m_compressionEnabled;
	};
}

#endif