#include <game/SystemFont.h>
#include <lang/Exception.h>

#include <windows.h>
#include <gdiplus.h>

using namespace lang;
using namespace gr;

//We don't declare using Gdi namespace since that would collide with gr::Color

namespace game
{
	class SystemFont::Impl : //GDI (0x58) bytes
		public lang::Object
	{
	public:
		/*const std::vector<std::string>& getAvailableFontNames() //45C800
		{
		}*/

		Impl(Context* context, const std::string& fontName, int fontSize, const Color& fontColor, int style) : //45B2E0 | TODO
			m_name(fontName),
			m_size(fontSize),
			m_color(fontColor),
			m_style(style)
		{
			//if (?) //Init var
			//{
			//	Gdiplus::GdiplusStartupInput startup;
			//	ULONG_PTR token;
			//	Gdiplus::GdiplusStartup(&token, &startup, NULL);
			//	? = true;
			//}

			//u16string s = sub_4F5410()

			//Gdiplus::FontCollection collection;
			//Gdiplus::FontFamily fontFamily(?, 0, &collection);

			//std::string name = .c_str();

			//if (collection.)
				//throwError(Exception(Format("Font {0} is not available.", name)));
			//SolidBrush
			//GdipDeleteFontFamily();

			//throwError(Exception(Format("Style {0} is not available for font {1}.", )));


			//int baseLineSpacing;

			//Gdiplus::GdiplusBase();
			//Gdiplus::Graphics(sub_534D30(), )

			//Gdiplus::GpGraphics* 

			//m_ascending = ceil(baseLineSpacing * ?);
			//m_leading = ceil(baseLineSpacing * ?);
		}

		~Impl() //45BEF0 | TODO?
		{
			//GdipDeleteFont();
			//GdipDeleteGraphics();
		}

		void drawString(Context* context, const std::string& str, float y, float x, Anchor anchor) const //45C230 | TODO
		{
			if (str.empty())
				return;

			//switch (anchor.h)
			{
			}
		}

		void drawString(Context* context, const std::string& str, int offset, int length, float x, float y, Anchor anchor) const //45C230
		{
			drawString(context, str, 0.0f, 0.0f, anchor);
		}

		std::string filter(const std::string& str) const //45AD70
		{
			return str;
		}

		bool isCharacterSupported(int character) const //45A610
		{
			return true;
		}

		int getStringWidth(const std::string& str, int offset, int length) const //45B890 | TODO
		{
			int result; //= 45B890();
			return ceil(result);
		}

		int getStringHeight(const std::string& str, int offset, int length) const //45B890 | TODO
		{
			int result; //= 45B890();
			return ceil(result);
		}

		int getHeight() const //45A620 | Same as iOS impl!
		{
			return m_ascending - m_descending;
		}

		int getMaxAscending() const //45A630 | Same as iOS impl!
		{
			return m_ascending;
		}

		int getMaxDescending() const //45A640 | Same as iOS impl!
		{
			return m_descending;
		}

		int getLeading() const //45A650 | Same as iOS impl!
		{
			return m_leading;
		}

		int getTracking() const //495DC0 | Same as iOS impl!
		{
			return 0;
		}

		gr::Rect getBounds(const std::string& str, Anchor anchor, int offset, int length) const //45BC70 | TODO
		{
			int x0 = 0;
			int y0 = 0;
			//if (length ==1)


			int x1 = 0; //ceil(;
			int y1 = 0; //ceil(;

			return gr::Rect(x0, y0, x0 + x1, y0 + y1);
		}

	private:
		//Assuming from iOS
		std::string m_name; //0x0C
		int m_size; //0x28
		gr::Color m_color; //0x2C
		int m_style; //0x3C
		int m_ascending; //0x40
		int m_descending; //0x44
		int m_leading; //0x48
		Gdiplus::GpStatus dword40_hwnd; //0x4C
		Gdiplus::GpStatus dword44_solidbrush; //0x50
		Gdiplus::GpStatus dword54_createFont; //0x54

		/*
		int *pint0;
		_BYTE gap4[36];
		_DWORD dword28;
		_BYTE gap2C[16];
		_DWORD dword3C;
		int int40;
		_DWORD dword44;
		_BYTE gap48[8];
		_DWORD dword50;
		_DWORD dword54;
		*/

		/*HWND sub_534D30() //Grabs the HWND
		{
			return s_hwnd;
		}*/
	};

#include <game/common/SystemFont.h>

}