#ifndef _GAME_TEXTGROUP_H
#define _GAME_TEXTGROUP_H

#include <game/TextFormatter.h>

namespace game
{
class TextGroup :
	public lang::Object
{
public:
	const std::string& get(const std::string& id) const;

	std::string getFormatted(const std::string& id, const TextFormatter& formatter) const; //Recover names from ABFM

	void getIDs(std::vector<std::string>& idlist) const; //Recover name from ABFM
private:
	std::map<std::string, std::string> m_entries;

	TextGroup();
	TextGroup(const TextGroup&);
	TextGroup& operator=(const TextGroup&);
};

}

#endif