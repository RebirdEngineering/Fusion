#ifndef _GAME_TEXTGROUPSET_H
#define _GAME_TEXTGROUPSET_H

#include <lang/Object.h>

namespace game
{

class TextGroup;

class TextGroupSet :
	public lang::Object
{
public:
	explicit TextGroupSet(const std::string& filename);

	virtual ~TextGroupSet();

	void loadLocaleCodes();

	TextGroup* loadTextGroup(const std::string& localeCode);

	void releaseTextGroup(const std::string& localeCode);

	const TextGroup* getTextGroup(const std::string& localeCode) const;

	const std::vector<std::string> getLocales() const;
private:
	std::vector<std::string> m_locales;
	std::map<std::string, P(TextGroup)> m_textGroups;
	std::string m_filename;

	TextGroupSet(const TextGroupSet&);
	TextGroupSet& operator=(const TextGroupSet&);
};

}

#endif