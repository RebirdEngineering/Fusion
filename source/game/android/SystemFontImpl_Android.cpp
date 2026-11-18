#include <game/SystemFont.h>
#include <lang/String.h>

//!!!TODO!!!

//#include <java/jni.h>

using namespace gr;
//using namespace java;
using namespace lang;

namespace game
{
	class SystemFont::Impl : //0x64 bytes
		public Object
	{
	public:
		Impl(Context* context, const std::string& fontName, int fontSize, const Color& fontColor, int style) :
			m_name(fontName),
			m_size(fontSize),
			m_color(fontColor),
			m_style(style)
		{
			//JNIEnv* jniEnv = jni::getJNIEnv();
			//std::string jniClass = jni::FindClass("com/rovio/fusion/SystemFontRenderer");
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
			//if (str.empty())
				return 0;

			//u32string toConv = string::toUTF32String(str);
			//std::string converted = string::toUTF8String(toConv);
			//jni::to
			//return 0;
		}

		int getHeight() const
		{
			return m_descending + m_ascending; //Ordering is mismatched
		}

		int getMaxAscending() const
		{
			return m_ascending;
		}

		int getMaxDescending() const
		{
			return m_descending;
		}

		int getLeading() const
		{
			return m_leading;
		}

		int getTracking() const
		{
			return 0;
		}

		Rect getBounds(const std::string& str, Anchor anchor, int offset, int length) const
		{
			return Rect();
		}

	private:
		int m_name;
		int m_size;
		gr::Color m_color;
		int m_style;
		int m_ascending;
		int m_descending;
		int m_leading;

		//Android stuff!
		GlobalRef* mainClassGlobalRef34;
		GlobalRef* pjava__globalref38;
		jmethodID* dword3C;
		int java__globalref40;
		jmethodID* drawStringFunc44;
		jmethodID* getWidthFunc48;
		jmethodID* getHeightFunc4C;
		jmethodID* getLeftFunc50;
		jmethodID* getTopFunc54;
		jmethodID* getLeadingFunc58;
		jmethodID* getAscenderFunc5C;
		jmethodID* getDescenderFunc60;

		static void drawString(Context* context, const u32string& str, int w, int h, float y, float x, Anchor anchor) const //Android only! Unknown params
		{
			//SurfaceFormat fmt;
			//LabelPool::Label* label;
			//Image* img = context->createImage(fmt.getMemoryUsage(?), fmt.getMemoryUsage(1), 0, fmt, 0);
			//label.m_image = img;
			//label.m_width = img->width();
			//label.m_height = img->height();
			//label.m_pivotX = 0;
			//label.m_pivotY = 0;

			//...

			//s_labelpool.addLabel(m_name, m_size, m_color.getColorAsInt(), m_style, label);
			//m_image->draw(context, w - label->m_pivotX, h - label->m_pivotY, 0, 0, label->m_width, label->m_height, label->m_width, label->m_height);
		}
	};

#include <game/common/SystemFont.h>

}