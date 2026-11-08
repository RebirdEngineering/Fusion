#include <lua/JSONExporter.h>

namespace lua
{

JSONExporter::JSONExporter() :
	m_json(""), m_currentState(false, kInvalidIndex) //11
{
}

void JSONExporter::visit(const char* name, const char* value) //15-25 | Correct?
{
	std::string stringValue = "\""; //17 //? Is this used?
	stringValue.append(backslashEscape(value)); //18

	addName(backslashEscape(name)); //21
	addValue(stringValue);

	m_currentState.m_firstItem = false; //24
}

void JSONExporter::visit(const char* name, double value) //27-35
{
	std::string stringValue = doubleToString(value); //29

	addName(backslashEscape(name)); //31
	addValue(stringValue);

	m_currentState.m_firstItem = false;
}

void JSONExporter::visit(const char* name, bool value) //37-45
{
	const char* stringValue = value ? "true" : "false"; //39

	addName(backslashEscape(name)); //41
	addValue(stringValue);

	m_currentState.m_firstItem = false;
}

void JSONExporter::visit(const char* name) //No code?
{
}

void JSONExporter::visit(int index, const char* value) //52-61
{
	std::string stringValue = "\""; //54
	stringValue.append(backslashEscape(value));
	
	addArrayItem(index, stringValue); //58

	m_currentState.m_firstItem = false; //60
}

void JSONExporter::visit(int index, double value) //63-70
{
	std::string stringValue = doubleToString(value); //65

	addArrayItem(index, stringValue); //67

	m_currentState.m_firstItem = false; //69
}

void JSONExporter::visit(int index, bool value) //72
{
	std::string stringValue = value ? "true" : "false"; //74

	addArrayItem(index, stringValue); //76

	m_currentState.m_firstItem = false; //78
}

void JSONExporter::visit(int index) //81 | No code?
{
}

void JSONExporter::openTable(const char* name) //86
{
	if (name)
	{
		addName(backslashEscape(name)); //91
	}

	else
	{
		if (m_currentState.m_firstItem) //m_currentState.m_firstItem ? m_json.append("[") : m_json.append(","); //Yeah sure
			m_json.append("["); //97
		else
			m_json.append(","); //101 | Yeah sure
	}

	if (name)
		m_currentState.m_currentIndex = kInvalidIndex; //106

	m_states.push(m_currentState); //108
	m_currentState.m_firstItem = true;
	m_currentState.m_currentIndex = kInvalidIndex;
}

void JSONExporter::closeTable()
{
	if (m_currentState.m_currentIndex == kInvalidIndex)
	{
		if (m_currentState.m_firstItem)
		{
			m_json.append("{}"); //119
		}
		else
		{
			m_json.append("}"); //123
		}
	}

	else
	{
		m_json.append("]"); //128
	}
	
	m_currentState = m_states.top(); //131
	m_states.pop(); //132
}

void JSONExporter::start() //Nothing? Prob no
{
}

void JSONExporter::end() //Correct?
{
	if (m_json.empty()) //142
	{
		m_json = "{}"; //145
	}

	else
	{
		if (m_currentState.m_currentIndex == kInvalidIndex) //m_json.append(m_currentState.m_currentIndex == kInvalidIndex ? "}" : "]");
		{
			m_json.append("}"); //151
		}
		else
		{
			m_json.append("]"); //155
		}
	}
}

std::string JSONExporter::getJSON()
{
	return m_json; //164
}

void JSONExporter::addName(const std::string& name) //167
{
	m_json.append(m_currentState.m_firstItem ? "{" : ",");
	m_json.append("\"");
	m_json.append(name);
	m_json.append("\":");
}

void JSONExporter::addValue(const std::string& value)
{
	m_json.append(value);
}

void JSONExporter::addArrayItem(int index, const std::string& value) //188
{
	if (m_currentState.m_firstItem)
	{
		m_currentState.m_currentIndex = 0;
		m_json.append("[");
	}

	else
	{
		m_currentState.m_currentIndex++;
		m_json.append(",");
	}

	m_json.append(value); //205
}

std::string JSONExporter::doubleToString(double value) //208
{
	char buffer[64]; //210
	sprintf(buffer, "%.16g", value);
	return buffer;
}

std::string JSONExporter::backslashEscape(const char* s) //216 | TODO
{
	std::string result; //218

	/*if (s)
	{
		unsigned char token = *s; //222
		while (token)
		{
			switch (token)
			{
			case '\b': result += "\\b";
			case '\t': result += "\\t";
			case '\n': result += "\\n";
			case '\f': result += "\\f";
			case '"': result += "\"";
			case '\r': result += "\\r";
			case '\\': result += "\\\\";
			
			//default: result + token;

			//token + 1;
		}

		char buffer[6]; //253
		sprintf(buffer, "u%04x", token); //254
		result.append(buffer); //255
	}*/

	assert("std::string JSONExporter::backslashEscape(const char* s) is not yet decompiled.");

	return result;
}

} // lua