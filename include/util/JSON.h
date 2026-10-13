#ifndef _UTIL_JSON_H
#define _UTIL_JSON_H

#include <lang/Exception.h>
#include <io/InputStream.h>
#include <external/vjson/vjson.h>

namespace util
{
class JSON : //23
	public lang::Object
{
public:	
	JSON(); //28

	typedef std::vector<JSON> array_type; //32
	typedef std::map<std::string, JSON> object_type; //33

	enum Type { Null, Bool, Number, String, Array, Object }; //35

	struct JSONException : public lang::Exception { JSONException(const lang::Format& msg) : Exception(msg) {} }; //40
	struct BadType : public JSONException { BadType(const lang::Format& msg) : JSONException(msg) {} }; //41
	struct KeyNotFound : public JSONException { KeyNotFound(const lang::Format& msg) : JSONException(msg) {} }; //42
	struct IndexOutOfBounds : public JSONException { IndexOutOfBounds(const lang::Format& msg) : JSONException(msg) {} }; //43
	struct ParseError : //44
		public JSONException
	{
	public:
		ParseError(const lang::Format& msg) : JSONException(msg) {} //47
		ParseError(const lang::Format& msg, int line, const std::string& desc, const std::string& position) : JSONException(msg), line(line), description(desc), position(position) {} //48
		virtual ~ParseError(); //49
		int line; //50
		std::string description; //51
		std::string position; //52
	};

	struct Visitor //58
	{
		virtual void visit(const std::string& name) = 0; //64

		virtual void visit(const std::string& name, bool b) = 0; //71

		virtual void visit(const std::string& name, double d, int64_t) = 0; //78

		virtual void visit(const std::string& name, const std::string& str) = 0; //85

		virtual void startObject(const std::string& name) = 0; //91

		virtual void endObject() = 0; //96

		virtual void startArray(const std::string& name) = 0; //102

		virtual void endArray() = 0; //107
	};

	JSON(const JSON& other); //114

	explicit JSON(bool value); //130 | //I feel like you could've used templates here but whatever

	explicit JSON(double value); //133

	explicit JSON(const char* value); //136

	explicit JSON(const std::string& value); //139

	explicit JSON(const array_type& value); //142

	explicit JSON(const object_type& value); //145

	JSON& parse(const std::string& jsonstr); //151

	JSON& operator=(const JSON& other); //154

	JSON& operator=(bool value); //162

	JSON& operator=(double value); //172

	JSON& operator=(const char* value); //175

	JSON& operator=(const std::string& value); //178

	JSON& operator=(const array_type& value); //181

	JSON& operator=(const object_type& value); //184

	JSON& operator[](size_t index); //189 | Undefined on iOS

	const JSON& operator[](size_t index) const; //195

	JSON& operator[](const std::string& key); //200

	const JSON& operator[](const std::string& key) const; //206

	const JSON& get(size_t index) const; //212 | Undefined on iOS

	const JSON& get(const std::string& key) const; //218

	bool getBool(size_t index) const; //225 | Undefined on iOS

	bool getBool(const std::string& key) const; //232

	int getInt(size_t index) const; //239 | Undefined on iOS

	int getInt(const std::string& key) const; //246

	int64_t getInt64(size_t index) const; //253 | Undefined on iOS

	int64_t getInt64(const std::string& key) const; //260

	uint64_t getUInt64(size_t index) const; //267 | Undefined on iOS

	uint64_t getUInt64(const std::string& key) const; //274 | Undefined on iOS

	float getFloat(size_t index) const; //281 | Undefined on iOS

	float getFloat(const std::string& key) const; //288

	double getDouble(size_t index) const; //295 | Undefined on iOS

	double getDouble(const std::string& key) const; //302

	const std::string& getString(size_t index) const; //309 | Undefined on iOS

	const std::string& getString(const std::string& key) const; //316

	const array_type& getArray(size_t index) const; //323 | Undefined on iOS

	const array_type& getArray(const std::string& key) const; //330

	const object_type& getObject(size_t index) const; //337 | Undefined on iOS

	const object_type& getObject(const std::string& key) const; //344

	std::string& getString(size_t index); //351 | Undefined on iOS

	std::string& getString(const std::string& key); //358

	array_type& getArray(size_t index); //365 | Undefined on iOS

	array_type& getArray(const std::string& key); //372

	object_type& getObject(size_t index); //379 | Undefined on iOS

	object_type& getObject(const std::string& key); //386

	bool has(size_t index) const; //389 | Undefined on iOS

	bool has(const std::string& key) const; //392

	bool hasNull(size_t index) const; //395 | Undefined on iOS

	bool hasNull(const std::string& key) const; //398 | Undefined on iOS

	bool hasBool(size_t index) const; //401 | Undefined on iOS

	bool hasBool(const std::string& key) const; //404

	bool hasNumber(size_t index) const; //407 | Undefined on iOS

	bool hasNumber(const std::string& key) const; //410

	bool hasString(size_t index) const; //413 | Undefined on iOS

	bool hasString(const std::string& key) const; //416

	bool hasArray(size_t index) const; //419 | Undefined on iOS

	bool hasArray(const std::string& key) const; //422

	bool hasObject(size_t index) const; //425 | Undefined on iOS

	bool hasObject(const std::string& key) const; //428

	Type getType() const; //431

	bool isNull() const; //434

	bool isBool() const; //437

	bool isNumber() const; //440

	bool isString() const; //443

	bool isArray() const; //446

	bool isObject() const; //449

	bool getBool() const; //455

	int getInt() const; //461

	int64_t getInt64() const; //467

	uint64_t getUInt64() const; //473

	float getFloat() const; //479

	double getDouble() const; //485

	const std::string& getString() const; //491

	const array_type& getArray() const; //497

	const object_type& getObject() const; //503

	std::string& getString(); //509

	array_type& getArray(); //515

	object_type& getObject(); //521

	void remove(size_t index); //526 | Undefined on iOS

	void remove(const std::string& key); //531 | Undefined on iOS

	void visit(Visitor& visitor) const; //537

	std::string toString(bool pretty) const; //543

	void patch(const JSON& other); //558 | Undefined on iOS, variable is guessed

private:
	void checkType(Type type) const; //569

	JSON& operator=(json_value* value); //571

	void visit(const std::string& name, Visitor& visitor) const; //573
	Type m_type; //561

	std::string m_string; //563
	array_type m_array; //564
	object_type m_object; //565
	double m_double; //566
	int64_t m_int64; //567
};

const char* toString(JSON::Type type);
util::JSON toJSON(const std::map<std::string, std::string>& map);
util::JSON toJSON(io::InputStream& in);

}

#endif