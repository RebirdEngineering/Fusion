#ifndef _UTIL_JSON_H
#define _UTIL_JSON_H

#include <lang/Exception.h>
#include <io/InputStream.h>
#include <external/vjson/vjson.h>

namespace util
{
class JSON :
	public lang::Object
{
public:
	struct JSONException : public lang::Exception { JSONException(const lang::Format& msg) : Exception(msg) {} };
	struct BadType : public JSONException { BadType(const lang::Format& msg) : JSONException(msg) {} };
	struct KeyNotFound : public JSONException { KeyNotFound(const lang::Format& msg) : JSONException(msg) {} };
	struct IndexOutOfBounds : public JSONException { IndexOutOfBounds(const lang::Format& msg) : JSONException(msg) {} };
	struct ParseError :
		public JSONException
	{
	public:
		int line;
		std::string description;
		std::string position;
		ParseError(const lang::Format& msg) : JSONException(msg) {}
		ParseError(const lang::Format& msg, int line, const std::string& desc, const std::string& position);
		virtual ~ParseError();
	};
	typedef long long uint64_t;
	typedef std::vector<JSON> array_type;
	typedef std::map<std::string, JSON> object_type;
	struct Visitor
	{
		virtual void visit(const std::string& name) = 0;

		virtual void visit(const std::string& name, bool b) = 0;

		virtual void visit(const std::string& name, double d, int64_t) = 0;

		virtual void visit(const std::string& name, const std::string& str) = 0;

		virtual void startObject(const std::string& name) = 0;

		virtual void endObject() = 0;

		virtual void startArray(const std::string& name) = 0;

		virtual void endArray() = 0;
	};
	enum Type
	{
		Null,
		Bool,
		Number,
		String,
		Array,
		Object
	};
	JSON();

	JSON(const JSON& other);

	explicit JSON(bool value);

	explicit JSON(double value);

	explicit JSON(const char* value);

	explicit JSON(const std::string& value);

	explicit JSON(const array_type& value);

	explicit JSON(const object_type& value);

	JSON& parse(const std::string& jsonstr);

	//I feel like you could've used templates here but whatever

	JSON& operator=(const JSON& other);

	JSON& operator=(bool value);

	JSON& operator=(double value);

	JSON& operator=(const char* value);

	JSON& operator=(const std::string& value);

	JSON& operator=(const array_type& value);

	JSON& operator=(const object_type& value);

	JSON& operator[](size_t index); //Undefined on iOS

	const JSON& operator[](size_t index) const;

	JSON& operator[](const std::string& key);

	const JSON& operator[](const std::string& key) const;

	const JSON& get(size_t index) const; //Undefined on iOS

	const JSON& get(const std::string& key) const;

	bool getBool(size_t index) const; //Undefined on iOS

	bool getBool(const std::string& key) const;

	int getInt(size_t index) const; //Undefined on iOS

	int getInt(const std::string& key) const;

	int64_t getInt64(size_t index) const; //Undefined on iOS

	int64_t getInt64(const std::string& key) const;

	uint64_t getUInt64(size_t index) const; //Undefined on iOS

	uint64_t getUInt64(const std::string& key) const; //Undefined on iOS

	float getFloat(size_t index) const; //Undefined on iOS

	float getFloat(const std::string& key) const;

	double getDouble(size_t index) const; //Undefined on iOS

	double getDouble(const std::string& key) const;

	const std::string& getString(size_t index) const; //Undefined on iOS

	const std::string& getString(const std::string& key) const;

	const array_type& getArray(size_t index) const; //Undefined on iOS

	const array_type& getArray(const std::string& key) const;

	const object_type& getObject(size_t index) const; //Undefined on iOS

	const object_type& getObject(const std::string& key) const;

	std::string& getString(size_t index); //Undefined on iOS

	std::string& getString(const std::string& key);

	array_type& getArray(size_t index); //Undefined on iOS

	array_type& getArray(const std::string& key);

	object_type& getObject(size_t index); //Undefined on iOS

	object_type& getObject(const std::string& key);

	bool has(size_t index) const; //Undefined on iOS

	bool has(const std::string& key) const;

	bool hasNull(size_t index) const; //Undefined on iOS

	bool hasNull(const std::string& key) const;

	bool hasBool(size_t index) const; //Undefined on iOS

	bool hasBool(const std::string& key) const;

	bool hasNumber(size_t index) const;

	bool hasNumber(const std::string& key) const;

	bool hasString(size_t index) const;

	bool hasString(const std::string& key) const;

	bool hasArray(size_t index) const;

	bool hasArray(const std::string& key) const;

	bool hasObject(size_t index) const;

	bool hasObject(const std::string& key) const;

	Type getType() const;

	bool isNull() const;

	bool isBool() const;

	bool isNumber() const;

	bool isString() const;

	bool isArray() const;

	bool isObject() const;

	bool getBool() const;

	int getInt() const;

	int64_t getInt64() const;

	uint64_t getUInt64() const;

	float getFloat() const;

	double getDouble() const;

	const std::string& getString() const;

	const array_type& getArray() const;

	const object_type& getObject() const;

	std::string& getString();

	array_type& getArray();

	object_type& getObject();

	void remove(size_t index); //Undefined on iOS

	void remove(const std::string& key); //Undefined on iOS

	void visit(Visitor& visitor) const;

	std::string toString(bool pretty) const;

	void patch(const JSON&);
private:
	void checkType(Type type) const;
	JSON& operator=(json_value* value);

	void visit(const std::string& name, Visitor& visitor) const;
	Type m_type;

	std::string m_string;
	array_type m_array;
	object_type m_object;
	double m_double;
	int64_t m_int64;
};

util::JSON toJSON(io::InputStream& in);

}

#endif