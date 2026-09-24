#include <game/TextGroup.h>

namespace game
{

TextGroup::TextGroup()
{
}

const std::string& TextGroup::get(const std::string& id) const
{
	for (std::map<std::string, std::string>::const_iterator it = m_entries.find(id); it != m_entries.end(); it++) //Ok so the dump suggets its a reg iterator but gets a const itr
	{
		//if (it->first == id)
			//return it->second;
	}
	return id;
}

std::string TextGroup::getFormatted(const std::string& id, const TextFormatter& formatter) const //UNOFFICIAL NAMES
{
	std::string formatted = formatter.format(get(id), this);
	return formatted;
}

void TextGroup::getIDs(std::vector<std::string>& entries) const //UNOFFICIAL NAMES
{
	entries.resize(m_entries.size());
	/*if (m_entries.size() != entries.size())
	{
		m_entries
	}*/
}

}