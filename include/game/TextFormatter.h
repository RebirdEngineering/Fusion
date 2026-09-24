#ifndef _GAME_TEXTFORMATTER_H
#define _GAME_TEXTFORMATTER_H

#include <lang/Object.h>

namespace game
{

class TextGroup;

class TextFormatter :
	public lang::Object
{
public:
	TextFormatter();
	~TextFormatter();

	std::string format(const std::string&, const TextGroup*) const;

	void addPair(const std::string&, const std::string&, bool);

	void removePair(const std::string&);
private:
	std::map<std::string, std::pair<std::string, bool>> m_pairs;

	TextFormatter(const TextFormatter&);
	TextFormatter& operator=(const TextFormatter&);
};

}

#endif