#ifndef _UTIL_JSONVISITOR_H
#define _UTIL_JSONVISITOR_H

#include <lang/pp.h>

namespace util
{

class JSONVisitor
{
public:
	virtual ~JSONVisitor(); //12

	virtual void visit(const char* name, const char* value) = 0; //15
	virtual void visit(const char*, double) = 0; //16
	virtual void visit(const char*, bool) = 0; //17
	virtual void visit(const char*) = 0; //18

	virtual void startObject(const char*) = 0; //21
	virtual void endObject() = 0; //22

	virtual void startArray(const char*) = 0; //25
	virtual void endArray() = 0; //26
};

}

#endif