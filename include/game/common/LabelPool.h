#ifndef _GAME_COMMON_LABELPOOL_H
#define _GAME_COMMON_LABELPOOL_H

#include <lang/Object.h>

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
	const int MAX_POOL_SIZE = 5242880;
public:
	struct Text
	{
		Text(const std::string& fontname, int size, int color, const std::string& str, int style); //assert(it != m_labels.end()); //ABC_CHN ABTTCH
		bool operator<(const Text&) const;
		unsigned long m_hash;
	};
	class Label : public Object
	{
	public:
		Label(gr::Image*);

		void draw(gr::Context*, int, int) const;

		int getMemoryUsage() const;

		void blt(void*);

		void setPivot(int, int);
	private:
		P(gr::Image) m_image;
		int m_width;
		int m_height;
		int m_pivotX;
		int m_pivotY;
	};
	LabelPool();

	Label* getLabel(const std::string& name, int size, int color, const std::string& str, int style) const;

	void addLabel(const std::string& name, int size, int color, const std::string& str, int style, Label* label);

	void addUser();

	void removeUser();
private:
	void reset()
	{
		//m_labels.clear();
		//m_order.clear();
	}

	int m_size;
	std::map<Text, P(Label)> m_labels;
	std::vector<Text> m_order;
	int m_users;
};

}

#endif