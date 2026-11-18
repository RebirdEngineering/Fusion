#include <game/SystemFont.h>
#include <game/common/LabelPool.h>
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
		const std::vector<std::string>& getAvailableFontNames() //45C800 | TODO
		{
			std::vector<std::string> ret;
			//ULONG_PTR tkn;
			//Gdiplus::GdiplusStartupInput start;
			//if (s_59ADB4)
			//{
			//	Gdiplus::GdiplusStartup(&tkn, &start, NULL);
			//	s_59ADB4 = true;
			//}
			//
			//if (s_labelPool)
			//{
			//	Gdiplus::InstalledFontCollection ifc;
			//	int families = ifc.GetFamilyCount();
			//
			//	//Gdiplus::FontFamily fontFamily(;
			//}

			//Gdiplus::GdiplusBase();

			//return s_labelPool.
			return ret;
		}

		std::string findBestFontMatch(const std::string& param1, const std::string& param2) //TODO | Is this a function?
		{
			return "";
		}

		Impl(Context* context, const std::string& fontName, int fontSize, const Color& fontColor, int style) : //45B2E0 | TODO
			m_name(fontName),
			m_size(fontSize),
			m_color(fontColor),
			m_style(style)
		{
			if (s_59ADB4) //Init var
			{
				Gdiplus::GdiplusStartupInput startup;
				ULONG_PTR token;
				Gdiplus::GdiplusStartup(&token, &startup, NULL);
				s_59ADB4 = true;
			}

			Gdiplus::FontFamily fontFamily(string::towstring(fontName).c_str());
			if (!fontFamily.IsAvailable())
				throwError(Exception(Format("Font {0} is not available.", fontName)));

			if (fontFamily.IsStyleAvailable(m_style))
			{
				const char* style = toString((Style)m_style);

				if (!style)
					throwError(Exception(Format("Style {0} is not available for font {1}.", style, fontName)));
			}

			dword50_solidbrush = new Gdiplus::SolidBrush(fontColor.getColorAsInt());
			m_font = new Gdiplus::Font(&fontFamily, fontSize, style);
			dword4C_gfx = new Gdiplus::Graphics(sub_534D30());

			m_ascending = ceil(fontFamily.GetCellAscent(m_font->GetStyle()));
			m_descending = ceil(fontFamily.GetCellDescent(m_font->GetStyle()));
			m_leading = ceil(fontFamily.GetLineSpacing(m_font->GetStyle()));

			s_labelPool.addUser();
		}

		~Impl() //45BEF0 | TODO?
		{
			s_labelPool.removeUser();

			delete dword50_solidbrush;
			delete m_font;
			delete dword4C_gfx;
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

		std::string filter(const std::string& str) const //45AD70 | Same as iOS impl!
		{
			return str;
		}

		bool isCharacterSupported(int character) const //45A610
		{
			return true;
		}

		int getStringWidth(const std::string& str, int offset, int length) const //45B890 | TODO
		{
			if (str.empty())
				return 0;

			int result; //= 45B890();
			return ceil(result);
		}

		int getStringHeight(const std::string& str, int offset, int length) const //45B890 | TODO same function!
		{
			//if (str.empty())
			//	return 0;
			//
			//std::wstring unicode = string::towstring(str.substr(offset, length));
			//int size = unicode.size();
			//
			//Gdiplus::PointF l_r;
			//Gdiplus::RectF b;
			//
			//Gdiplus::Status status = dword40_gfx->MeasureString(unicode.data(), size, dword54_createFont, l_r, 0, 0);

			//if (status)
				//dword40_gfx =

			//Gdiplus::Graphics::MeasureString()
			int result; //=
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

		Rect getBounds(const std::string& str, Anchor anchor, int offset, int length) const //45BC70 | Correct?
		{
			float x = 0.0f; //x0
			float y = 0.0f; //y0
			float width = ceil(getStringWidth(str, offset, length)); //x1
			float height = ceil(getStringHeight(str, offset, length)); //y1

			switch (anchor.h)
			{
			case Anchor::HCENTER: x = -0.5 * width; break;
			case Anchor::RIGHT: x = -width; break;
			}

			switch (anchor.v)
			{
			case Anchor::VCENTER: y = getHeight() / -2; break;
			case Anchor::BOTTOM: y = -getHeight(); break;
			case Anchor::BASELINE: y = -getMaxAscending(); break;
			}

			return Rect(x, y, x + width, y + height);
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
		Gdiplus::Graphics* dword4C_gfx; //0x4C | HWND?
		Gdiplus::SolidBrush* dword50_solidbrush; //0x50
		Gdiplus::Font* m_font; //0x54

		static bool s_59ADB4; //init
		static LabelPool s_labelPool; //59ADCC
		static HWND s_hwnd;

		HWND sub_534D30() //Grabs the HWND
		{
			return s_hwnd;
		}

		//sub_45A8D0()
		//{
		//}

		//REMOVED DUE TO GR::COLOR::getColorAsInt

		//void sub_45D3B0(float r[4], const Color& clr) //Clamp color? | Correct?
		//{
		//	float values[4] =
		//	{
		//		clr.red(),
		//		clr.green(),
		//		clr.blue(),
		//		clr.alpha()
		//	};
		//
		//	for (int i = 0; i < 4; i++)
		//	{
		//		if (values[i])
		//			r[i] = min(values[i], 1.0f);
		//		else
		//			r[i] = 0.0f;
		//	}
		//}
		//
		//int sub_45D480(const Color& clr) //45D480 | Convert to GDI ARGB, CORRECT?
		//{
		//	float cl[4];
		//	sub_45D3B0(cl, clr);
		//
		//	const auto r = static_cast<std::uint32_t>(cl[0] * 255.0f);
		//	const auto g = static_cast<std::uint32_t>(cl[1] * 255.0f);
		//	const auto b = static_cast<std::uint32_t>(cl[2] * 255.0f);
		//	const auto a = static_cast<std::uint32_t>(cl[3] * 255.0f);
		//
		//	return (a << 24) | (r << 16) | (g << 8) | b;
		//}
	};

#include <game/common/SystemFont.h>

}