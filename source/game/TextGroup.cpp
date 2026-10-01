#include <game/TextGroup.h>

namespace game
{

TextGroup::TextGroup()
{
}

const std::string& TextGroup::get(const std::string& id) const //12
{
	for (std::map<std::string, std::string>::const_iterator it = m_entries.find(id); it != m_entries.end(); it++) //15 | Ok so the dump suggets its a reg iterator but gets a const itr
	{
		if (it->first == id) //17
			return it->second;
	}
	return id;
}

std::string TextGroup::getFormatted(const std::string& id, const TextFormatter& formatter) const //Seen on Android.
{
	std::string formatted = formatter.format(get(id), this);
	return formatted;
}

void TextGroup::getIDs(std::vector<std::string>& idlist) const //Seen on Android.
{
	//idlist.resize(m_entries.size());
	//std::map<std::string, std::string>::const_iterator it = m_entries.find(idlist);
	//int i;
	/*if (m_entries.size() != idlist.size())
	{
		m_entries
		it++;
	}*/
	assert("void TextGroup::getIDs(std::vector<std::string>& idlist) const was not yet decompiled.");
}

}