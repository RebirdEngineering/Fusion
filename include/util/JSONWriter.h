#ifndef _UTIL_JSONWRITER_H
#define _UTIL_JSONWRITER_H

#include <util/JSON.h>

namespace util
{

class JSONWriter :
	public JSON::Visitor
{
public:
	JSONWriter(bool readable);

	void visit(const std::string& name);
	void visit(const std::string& name, bool b);
	void visit(const std::string& name, double d, int64_t);
	void visit(const std::string& name, const std::string& str);

	void startObject(const std::string& name);
	void endObject();

	void startArray(const std::string& name);
	void endArray();

	std::string getText() const { return m_json; };

	struct Entry
	{
		JSON::Type m_type;
		bool m_first;
		Entry(const JSON::Type);

		const JSON::Type& getType() const;

		bool isObject() const;
		bool isArray() const;
		bool isList() const;
		bool isFirst() const;

		void consumeFirst();
	};
private:
	JSONWriter(const JSONWriter&);
	JSONWriter& operator=(const JSONWriter&);

	bool isReadable() const;
	void appendKey(const std::string& name);
	void appendEscapedString(const std::string& str);
	void appendIndentation();

	std::stack<Entry> m_nesting;
	std::string m_json;
	bool m_readable;
};

}

#endif