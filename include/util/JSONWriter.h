#ifndef _UTIL_JSONWRITER_H
#define _UTIL_JSONWRITER_H

#include <util/JSON.h>

namespace util
{

class JSONWriter : //13
	public JSON::Visitor
{
public:
	JSONWriter(bool readable); //17

	void visit(const std::string& name); //19
	void visit(const std::string& name, bool b); //20
	void visit(const std::string& name, double d, int64_t); //21
	void visit(const std::string& name, const std::string& str); //22

	void startObject(const std::string& name); //24
	void endObject(); //25

	void startArray(const std::string& name); //27
	void endArray(); //28

	std::string getText() const { return m_json; }; //30

	struct Entry //33
	{
		Entry(const JSON::Type); //35

		const JSON::Type& getType() const; //37

		bool isObject() const { return m_type == JSON::Object; } //39
		bool isArray() const { return m_type == JSON::Array; } //40
		bool isList() const; //41
		bool isFirst() const { return m_first; } //42

		void consumeFirst(); //44

		JSON::Type m_type; //47
		bool m_first; //48
	};
private:
	std::stack<Entry> m_nesting; //51
	std::string m_json; //52
	bool m_readable; //53

	JSONWriter(const JSONWriter&); //55
	JSONWriter& operator=(const JSONWriter&); //56

	bool isReadable() const { return m_readable; }; //58
	void appendKey(const std::string& name); //60
	void appendEscapedString(const std::string& str); //61
	void appendIndentation(); //62
};

}

#endif