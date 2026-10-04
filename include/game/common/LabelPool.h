#ifndef _GAME_COMMON_LABELPOOL_H
#define _GAME_COMMON_LABELPOOL_H

#include <gr/Context.h>

namespace gr
{
	class Context;
	class Image;
}

namespace game
{
class LabelPool :
	public lang:: Object
{
	
public:
	struct Text { //13
		Text(const std::string& fontname, int size, int color, const std::string& str, int style); //14 /*//assert(it != m_labels.end()); //ABC_CHN ABTTCH
		{
			//unsigned char* strp; //17
			//int c; //18
			//.c_str(); //17
			//.c_str(); //21
		}*/

		bool operator<(const Text& text) const; //29
		/*{
			return this < &text; //?
		}*/

		unsigned long m_hash; //34
	};

	const int MAX_POOL_SIZE = 5242880; //38

	class Label : public lang::Object //40
	{
	public:
		Label(gr::Image* image); /*: //43
			m_width(image->width()),
			m_height(image->height()) //46
			m_image(image), //49
		{
		}*/

		void draw(gr::Context* context, int x, int y) const; //51
		//{
			//m_image->draw(context, x, y, 0, 0, m_width, m_height, x, y); //53 | ?
		//}

		int getMemoryUsage() const; //56
		/*{
			return m_image->format().getMemoryUsage(m_width, m_height);
		}*/

		void blt(void* data) //58
		{
			img::SurfaceFormat format; //60
			m_image->blt(0, 0, data, format.getMemoryUsage(m_width, 1), 0, m_width, m_height, format); //61
		}

		void setPivot(int x, int y) //64 | Unknown parameters.
		{
			m_pivotX = x;
			m_pivotY = y;
		}

	private:
		P(gr::Image) m_image; //71
		int m_width; //72
		int m_height; //73
		int m_pivotX; //74
		int m_pivotY; //75
	};
public:
	LabelPool(); //78

	Label* getLabel(const std::string& fontname, int size, int color, const std::string& str, int style) const; //80-91
	//{
		//std::map<const Text, P(Label)>::const_iterator = m_labels.begin(); //82
		
		//-> //85
	//}

	void addLabel(const std::string& name, int size, int color, const std::string& str, int style, Label* label); //93-119
	/*{
		//Text text(name, size, color, str, style); //95
		//label->getMemoryUsage(); //96
		//ptr //100
		//.begin() //101
		
		//std::map<const Text, P(Label)>::iterator it = m_labels.begin(); //108-119
		
		//*Label //110
		//getMemoryUsage //111
		//m_labels.erase(); //112
		//m_labels.pop_back(); //113
		
		//m_labels[]; //115
		//m_order.begin(); //116
	}*/

	void addUser(); //121

	void removeUser(); //123
private:
	void reset() //132
	{
		m_labels.clear(); //134
		m_order.clear(); //135
	}

	int m_size; //140
	std::map<Text, P(Label)> m_labels; //141
	std::vector<Text> m_order; //142
	int m_users; //143
};

}

#endif