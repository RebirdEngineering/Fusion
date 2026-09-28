#include <game/SystemFont.h>
#include <lang/Exception.h>

#include <gdiplus.h>

using namespace lang;
using namespace gr;

namespace game
{
	class SystemFont::Impl : //GDI (0x58) bytes
		public lang::Object
	{
	public:

		/*const std::vector<std::string>& getAvailableFontNames()
		{
		}*/

		Impl(Context* context, const std::string& fontName, int fontSize, const Color& fontColor, int style) :
			m_name(fontName),
			m_size(fontSize),
			m_color(fontColor),
			m_style(style)
		{
			//std::string name = .c_str();

			//throwError(Exception(Format("Font {0} is not available.", )));
			//SolidBrush
			//GdipDeleteFontFamily();

			//throwError(Exception(Format("Style {0} is not available for font {1}.", )));
		}

		~Impl()
		{
			//GdipDeleteFont();
			//GdipDeleteGraphics();
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

		//Assuming fron iOS
		std::string m_name;
		int m_size;
		gr::Color m_color;
		int m_style;
		int m_ascending;
		int m_descending;
		int m_leading;
	};

#include <game/common/SystemFont.h>

}