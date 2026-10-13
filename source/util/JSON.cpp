#include <util/JSON.h>
#include <lang/Throwable.h>
#include <lang/Exception.h>
#include <util/JSONWriter.h>

using namespace io;
using namespace lang;

namespace util
{

JSON::JSON()
{
	m_double = 0.0;
	m_string = "";
	m_int64 = 0;
	m_type = Null;
}

JSON::JSON(const JSON& other) //24
{
	m_type = other.m_type;
	m_string = other.m_string;
	m_array = other.m_array;
	m_object = other.m_object;
	m_double = other.m_double;
	m_int64 = other.m_int64;
}

JSON::JSON(bool value) //48
{
	m_type = Bool;
	m_int64 = value;
}

JSON::JSON(double value) //54
{
	m_type = Number;
	m_double = value;
	m_int64 = (int64_t)value;
}

JSON::JSON(const char* value) //61
{
	m_type = String;
	m_string = value;
}

JSON::JSON(const std::string& value) //67
{
	m_type = String;
	m_string = value;
}

JSON::JSON(const array_type& value) //73
{
	m_type = Array;
	m_array = value;
}

JSON::JSON(const object_type& value) //79
{
	m_type = Object;
	m_object = value;
}

JSON& JSON::parse(const std::string& jsonstr) //85
{
	if (!jsonstr.empty()) //88
	{
		const char* cstr = jsonstr.c_str(); //94
		std::vector<char> source(cstr, cstr + jsonstr.size() + 1); //95

		char* errorPos = 0; //97
		char* errorDesc = 0; //98
		int errorLine = 0; //99
		block_allocator allocator(131072); //100
		json_value* root = json_parse(source.data(), &errorPos, &errorDesc, &errorLine, &allocator); //101 | This relies off the very first commit of vjson since it relies off char** instead of const char**, which can be found here: https://github.com/vivkin/vjson/tree/bfbc82b7e5d006cfd11e9160e1c57d118cf803d6 and less than https://github.com/vivkin/vjson/commit/d140497ba17ab7b9cd95870fb15c63837997283a
		if (!root)
		{
			for (int i = 0; i++;) //105
			{
				if (!errorPos[i])
					throwError(ParseError(Format("Parsing JSON failed!\nReason: {0}\nLine: {1}\nInput: \"{2}\"", errorDesc, errorLine, errorPos)));
				if (errorPos[i] == '\n' || i >= 80)
					break;
			}
		}
		*this = root;
	}

	return *this;
}

JSON& JSON::operator=(const JSON& other) //121
{
	if (this != (JSON*)&other) //?
	{
		m_type = other.m_type;
		m_string = other.m_string;
		m_array = other.m_array;
		m_object = other.m_object;
		m_double = other.m_double;
		m_int64 = other.m_int64;
	}
	return *this;
}

JSON& JSON::operator=(bool value) //153
{
	return *this = JSON(value);
}

JSON& JSON::operator=(double value) //158
{
	return *this = JSON(value);
}

JSON& JSON::operator=(const char* value) //163
{
	return *this = JSON(value);
}

JSON& JSON::operator=(const std::string& value) //168
{
	return *this = JSON(value);
}

JSON& JSON::operator=(const array_type& value) //173
{
	return *this = JSON(value);
}

JSON& JSON::operator=(const object_type& value) //178
{
	return *this = JSON(value);
}

JSON& JSON::operator[](size_t index) //TODO
{
	if (m_type == Null)
		m_array = array_type();

	checkType(Array);

	while (m_array.size() < index)
		m_array.push_back(JSON());

	return m_array[index];
}

const JSON& JSON::operator[](size_t index) const //197
{
	checkType(Array);

	if (index >= m_array.size())
		throwError(IndexOutOfBounds(Format("Index {0} out of bounds, size: {1}", index, m_array.size()))); //203

	return m_array[index];
}

JSON& JSON::operator[](const std::string& key) //208
{
	if (m_type == Null)
		*this = m_object;

	checkType(Object);
	return m_object[key];
}

const JSON& JSON::operator[](const std::string& key) const //218
{
	checkType(Object);
	object_type::const_iterator it = m_object.find(key); //221

	if (it == m_object.end())
		throwError(KeyNotFound(Format("Key \"{0}\" not found", key))); //224

	return it->second.get(key);
}

const JSON& JSON::get(size_t index) const
{
	checkType(Array);

	if (index >= m_array.size())
		throwError(IndexOutOfBounds(Format("Index {0} out of bounds, size: {1}", index, m_array.size())));

	return m_array[index];
}

const JSON& JSON::get(const std::string& key) const //444
{
	checkType(Object);
	object_type::const_iterator it = m_object.find(key); //447

	if (it == m_object.end())
		throwError(KeyNotFound(Format("Key \"{0}\" not found", key))); //450

	return it->second;
}

bool JSON::getBool(size_t index) const
{
	checkType(Array);

	if (index >= m_array.size())
		throwError(IndexOutOfBounds(Format("Index {0} out of bounds, size: {1}", index, m_array.size())));

	return m_array[index].getBool();
}

bool JSON::getBool(const std::string& key) const //465
{
	checkType(Object);
	object_type::const_iterator it = m_object.find(key); //468

	if (it == m_object.end())
		throwError(KeyNotFound(Format("Key \"{0}\" not found", key))); //471

	return it->second.getBool(); //473
}

int JSON::getInt(size_t index) const
{
	checkType(Array);

	if (index >= m_array.size())
		throwError(IndexOutOfBounds(Format("Index {0} out of bounds, size: {1}", index, m_array.size())));

	return m_array[index].getInt();
}

int JSON::getInt(const std::string& key) const //486
{
	checkType(Object);
	object_type::const_iterator it = m_object.find(key); //489

	if (it == m_object.end())
		throwError(KeyNotFound(Format("Key \"{0}\" not found", key))); //492

	return it->second.getInt(); //494
}

int64_t JSON::getInt64(size_t index) const
{
	checkType(Array);

	if (index >= m_array.size())
		throwError(IndexOutOfBounds(Format("Index {0} out of bounds, size: {1}", index, m_array.size())));

	return m_array[index].getInt64();
}

int64_t JSON::getInt64(const std::string& key) const //507
{
	checkType(Object);
	object_type::const_iterator it = m_object.find(key); //510

	if (it == m_object.end())
		throwError(KeyNotFound(Format("Key \"{0}\" not found", key))); //513

	return it->second.getInt64(); //515
}

uint64_t JSON::getUInt64(size_t index) const
{
	checkType(Array);

	if (index >= m_array.size())
		throwError(IndexOutOfBounds(Format("Index {0} out of bounds, size: {1}", index, m_array.size())));

	return m_array[index].getUInt64();
}

float JSON::getFloat(size_t index) const
{
	checkType(Array);

	if (index >= m_array.size())
		throwError(IndexOutOfBounds(Format("Index {0} out of bounds, size: {1}", index, m_array.size())));

	return m_array[index].getFloat();
}

float JSON::getFloat(const std::string& key) const //549
{
	checkType(Object);
	object_type::const_iterator it = m_object.find(key); //552

	if (it == m_object.end())
		throwError(KeyNotFound(Format("Key \"{0}\" not found", key))); //55

	return it->second.getFloat(); //557
}

double JSON::getDouble(size_t index) const
{
	checkType(Array);

	if (index >= m_array.size())
		throwError(IndexOutOfBounds(Format("Index {0} out of bounds, size: {1}", index, m_array.size())));

	return m_array[index].getDouble();
}

double JSON::getDouble(const std::string& key) const //570
{
	checkType(Object);
	object_type::const_iterator it = m_object.find(key); //573

	if (it == m_object.end())
		throwError(KeyNotFound(Format("Key \"{0}\" not found", key))); //576

	return it->second.getDouble(); //578
}

const std::string& JSON::getString(size_t index) const
{
	checkType(Array);

	if (index >= m_array.size())
		throwError(IndexOutOfBounds(Format("Index {0} out of bounds, size: {1}", index, m_array.size())));

	return m_array[index].getString();
}

const std::string& JSON::getString(const std::string& key) const //591
{
	checkType(Object);
	object_type::const_iterator it = m_object.find(key); //594

	if (it == m_object.end())
		throwError(KeyNotFound(Format("Key \"{0}\" not found", key))); //597

	return it->second.getString(); //599
}

const JSON::array_type& JSON::getArray(size_t index) const
{
	checkType(Array);

	if (index >= m_array.size())
		throwError(IndexOutOfBounds(Format("Index {0} out of bounds, size: {1}", index, m_array.size())));

	return m_array[index].getArray();
}

const JSON::array_type& JSON::getArray(const std::string& key) const //612
{
	checkType(Object);
	object_type::const_iterator it = m_object.find(key); //615

	if (it == m_object.end())
		throwError(KeyNotFound(Format("Key \"{0}\" not found", key))); //618

	return it->second.getArray(); //620
}

const JSON::object_type& JSON::getObject(size_t index) const
{
	checkType(Array);

	if (index >= m_array.size())
		throwError(IndexOutOfBounds(Format("Index {0} out of bounds, size: {1}", index, m_array.size())));

	return m_array[index].getObject();
}

const JSON::object_type& JSON::getObject(const std::string& key) const //633
{
	checkType(Object);
	object_type::const_iterator it = m_object.find(key); //636

	if (it == m_object.end())
		throwError(KeyNotFound(Format("Key \"{0}\" not found", key))); //639

	return it->second.getObject(); //641
}

std::string& JSON::getString(size_t index)
{
	checkType(Array);

	if (index >= m_array.size())
		throwError(IndexOutOfBounds(Format("Index {0} out of bounds, size: {1}", index, m_array.size())));

	return m_array[index].getString();
}

std::string& JSON::getString(const std::string& key) //654
{
	checkType(Object);
	object_type::iterator it = m_object.find(key); //657

	if (it == m_object.end())
		throwError(KeyNotFound(Format("Key \"{0}\" not found", key))); //660

	return it->second.getString(); //662
}

JSON::array_type& JSON::getArray(size_t index)
{
	checkType(Array);

	if (index >= m_array.size())
		throwError(IndexOutOfBounds(Format("Index {0} out of bounds, size: {1}", index, m_array.size())));

	return m_array[index].getArray();
}

JSON::array_type& JSON::getArray(const std::string& key) //675
{
	checkType(Object);
	object_type::iterator it = m_object.find(key); //678

	if (it == m_object.end())
		throwError(KeyNotFound(Format("Key \"{0}\" not found", key))); //681

	return it->second.getArray(); //683
}

JSON::object_type& JSON::getObject(size_t index)
{
	checkType(Array);

	if (index >= m_array.size())
		throwError(IndexOutOfBounds(Format("Index {0} out of bounds, size: {1}", index, m_array.size())));

	return m_array[index].getObject();
}

JSON::object_type& JSON::getObject(const std::string& key) //696
{
	checkType(Object);
	object_type::iterator it = m_object.find(key); //699

	if (it == m_object.end())
		throwError(KeyNotFound(Format("Key \"{0}\" not found", key))); //702

	return it->second.getObject(); //704
}

bool JSON::has(size_t index) const
{
	return m_type == Array && index < m_array.size();
}

bool JSON::has(const std::string& key) const //236
{
	if (m_type != Object)
		return false;

	object_type::const_iterator& it = m_object.find(key); //239
	return it != m_object.end(); //240
}

bool JSON::hasNull(size_t index) const
{
	return m_type == Array && index < m_array.size() ? m_array[index].isNull() : false;
}

bool JSON::hasNull(const std::string& key) const
{
	if (m_type != Object)
		return false;

	object_type::const_iterator it = m_object.find(key);
	return it != m_object.end() ? it->second.isNull() : false;
}

bool JSON::hasBool(size_t index) const
{
	return m_type == Array && index < m_array.size() ? m_array[index].isBool() : false;
}

bool JSON::hasBool(const std::string& key) const //264
{
	if (m_type != Object)
		return false;

	object_type::const_iterator& it = m_object.find(key); //267
	return it != m_object.end() ? it->second.isBool() : false; //268
}

bool JSON::hasNumber(size_t index) const
{
	return m_type == Array && index < m_array.size() ? m_array[index].isNumber() : false;
}

bool JSON::hasNumber(const std::string& key) const //278
{
	if (m_type != Object)
		return false;

	object_type::const_iterator& it = m_object.find(key); //281
	return it != m_object.end() ? it->second.isNumber() : false; //282
}

bool JSON::hasString(const std::string& key) const //292
{
	if (m_type != Object)
		return false;

	object_type::const_iterator& it = m_object.find(key); //295
	return it->second.isString(); //296
}

bool JSON::hasArray(size_t index) const
{
	return m_type == Array && index < m_array.size() ? m_array[index].isArray() : false;
}

bool JSON::hasArray(const std::string& key) const //306
{
	if (m_type != Object)
		return false;

	object_type::const_iterator& it = m_object.find(key); //309
	return it->second.isArray(); //310
}

bool JSON::hasObject(size_t index) const
{
	return m_type == Array && index < m_array.size() ? m_array[index].isObject() : false;
}

bool JSON::hasObject(const std::string& key) const //320
{
	if (m_type != Object)
		return false;

	object_type::const_iterator& it = m_object.find(key); //323
	return it->second.isObject(); //324
}

JSON::Type JSON::getType() const
{
	return m_type;
}

bool JSON::isNull() const
{
	return m_type == Null;
}

bool JSON::isBool() const
{
	return m_type == Bool;
}

bool JSON::isNumber() const
{
	return m_type == Number;
}

bool JSON::isString() const
{
	return m_type == String;
}

bool JSON::isArray() const
{
	return m_type == Array;
}

bool JSON::isObject() const
{
	return m_type == Object;
}

bool JSON::getBool() const
{
	checkType(Bool); //364
	return m_int64 != false; //365
}

int JSON::getInt() const
{
	checkType(Number); //370
	return (int)m_int64; //371
}

int64_t JSON::getInt64() const
{
	checkType(Number); //376
	return m_int64; //377
}

uint64_t JSON::getUInt64() const
{
	checkType(Number); //382
	return m_int64; //383
}

float JSON::getFloat() const
{
	checkType(Number); //388
	return (float)m_double; //389
}

double JSON::getDouble() const //Not on iOS
{
	checkType(Number);
	return m_double;
}

const std::string& JSON::getString() const
{
	checkType(String); //400
	return m_string; //401
}

const JSON::array_type& JSON::getArray() const
{
	checkType(Array); //406
	return m_array; //407
}

const JSON::object_type& JSON::getObject() const
{
	checkType(Object); //412
	return m_object; //413
}

std::string& JSON::getString()
{
	checkType(String); //418
	return m_string; //419
}

JSON::array_type& JSON::getArray() 
{
	checkType(Array); //424
	return m_array; //425
}

JSON::object_type& JSON::getObject()
{
	checkType(Object); //430
	return m_object; //431
}

void JSON::remove(size_t index)
{
	checkType(Array);

	if (index < m_array.size())
	{
		for (array_type::iterator it = m_array.begin(); it != m_array.end(); it++)
			m_array.erase(it);
	}
}

void JSON::remove(const std::string& key)
{
	checkType(Object);

	m_object.erase(key);
}

void JSON::visit(Visitor& visitor) const //722
{
	visit("", visitor);
}

void JSON::visit(const std::string& name, Visitor& visitor) const //727 | TODO
{
	/*switch (m_type) //Convert to if statements?
	{
	case Null: visitor.visit(name); break; //732
	case Bool: visitor.visit(name, getBool()); break; //736
	case Number: visitor.visit(name, getInt64(), getDouble()); break; //740
	case String: visitor.visit(name, getString()); break; //744
	case Array:
		visitor.startArray(name);

		const array_type& arr = getArray(); //751
		for (array_type::const_iterator it = arr.begin(); it != arr.end(); it++) //752
			it->visit("", visitor);

		visitor.endArray(); //757
		break;
	case Object:
		visitor.startObject(name);

		const object_type& objects = getObject(); //765
		for (object_type::const_iterator it = objects.begin(); it != objects.end(); it++) //766
			it->second.visit(it->first, visitor);

		visitor.endObject(); //771
		break;
	default: assert(0); //776 of RCSSDKDBG
	}*/
}

void JSON::checkType(Type type) const //781
{
	if (m_type != type)
		throwError(BadType(Format("Expected type: {0}, got: {1}", util::toString(m_type), util::toString(type)))); //785
}

std::string JSON::toString(bool pretty) const //789
{
	JSONWriter writer(pretty); //791
	visit("", writer); //792
	return writer.getText();
}

JSON& JSON::operator=(json_value* value) //895
{
	/*switch (value->type)
	{
	case JSON_NULL: m_type = Null; return *this;
	case JSON_OBJECT:
		m_type = Object; //907
		m_object.clear(); //908
		for (json_value* it = value->first_child; it != value->next_sibling; it++) //909
		{
			if (!it->name)
				throwError(ParseError(Format("Parsing JSON failed!\nReason: Object \"{0}\" contains value without key", value->name))); //912

			m_object[it->name] = it->name;
		}
		break;
	case JSON_ARRAY:
	{
		m_type = Array;
		m_array.clear(); //921

		for (int i = 0; i < m_array.size(); i++)
		{
			for (json_value* it = value->first_child; it != value->next_sibling; it++) //925
			{
				m_array[i] = it->first_child;
			}
		}

		break;
	}
	case JSON_STRING: m_type = String; int count = strlen(value->string_value); m_string = value->string_value; break;
	case JSON_INT: m_type = Number; m_double = value->int_value; m_int64 = value->int_value; break;
	case JSON_FLOAT: m_type = Number; m_double = value->float_value; m_int64 = value->float_value; break;
	case JSON_BOOL: m_type = Bool; m_int64 = value->int_value; break;
	default: throwError(ParseError(Format("Unidentified object type"))); //970
	}*/

	//int count; //924
	//json_value* it; //925
	//int i; //930
	//json_value* it; //931

	//= 942 |string
	/*switch (value->type)
	{
	case JSON_NULL: m_type = Null; break;
	case JSON_OBJECT:
	{
		m_type = Object;
		m_object.clear(); //908
		//for (json_value* it = value->first_child; it != value->next_sibling; it++) //909
		{
			//if (!it->name)
				//throwError(ParseError(Format("Parsing JSON failed!\nReason: Object \"{0}\" contains value without key", value->name))); //912
			//m_object[it->name] = value->name;
		}
		break;
	}
	case JSON_ARRAY:

	{
		m_type = Array;
		break;
	}
	case JSON_STRING: m_type = String; int count = strlen(value->string_value); m_string = value->string_value; break;
	case JSON_INT: m_type = Number; m_double = value->int_value; m_int64 = value->int_value; break;
	case JSON_FLOAT: m_type = Number; m_double = value->float_value; m_int64 = value->float_value; break;
	case JSON_BOOL: m_type = Bool; m_int64 = value->int_value; break;
	default: throwError(ParseError(Format("Unidentified object type"))); //970
	//for (int i = 0);
	return ;*/
	return *this;
}

JSON toJSON(const std::map<std::string, std::string>& map) //1007
{
	JSON json; //1009
	for (std::map<std::string, std::string>::const_iterator it = map.begin(); it != map.end(); it++) //1010
	{
		json[it->first] = it->first; //1012
		json[it->second] = it->second;
	}

	return json;
}

JSON toJSON(InputStream& in) //1017
{
	JSON json; //1019
	return json.parse(toString(in));
}

const char* util::toString(JSON::Type type) //1404
{
	switch (type)
	{
	case JSON::Null: return "NULL";
	case JSON::Bool: return "Bool";
	case JSON::Number: return "Number";
	case JSON::String: return "String";
	case JSON::Array: return "Array";
	case JSON::Object: return "Object";
	default: return "";
	}
}

}