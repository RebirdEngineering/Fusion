#include <game/SystemFont.h>

using namespace gr;

namespace game
{
	class SystemFont::Impl : //Used in FunFusion
		public lang::Object
	{
	public:
		Impl(Context* context, const std::string& fontName, int fontSize, const Color& fontColor, int style)
		{
		}

		~Impl()
		{
		}

		void drawString(Context* context, const std::string& str, float y, float x, Anchor anchor) const
		{
		}

		void drawString(Context* context, const std::string& str, int offset, int length, float x, float y, Anchor anchor) const
		{
		}

		std::string filter(const std::string& str) const
		{
			return "";
		}

		bool isCharacterSupported(int character) const
		{
			return false;
		}

		int getStringWidth(const std::string& str, int offset, int length) const
		{
			return 0;
		}

		int getStringHeight(const std::string& str, int offset, int length) const
		{
			return 0;
		}

		int getHeight() const
		{
			return 0;
		}

		int getMaxAscending() const
		{
			return 0;
		}

		int getMaxDescending() const
		{
			return 0;
		}

		int getLeading() const
		{
			return 0;
		}

		int getTracking() const
		{
			return 0;
		}

		Rect getBounds(const std::string& str, Anchor anchor, int offset, int length) const
		{
			return Rect();
		}

		const char* toString(Style)
		{
			return "";
		}
	};
}

#include <game/common/SystemFont.h>