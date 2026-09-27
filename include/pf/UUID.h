#ifndef _PF_UUID_H
#define _PF_UUID_H

#include <lang/Object.h>

namespace pf //6
{
class UUID : //12
	public lang::Object
{
public:
	UUID(); //20

	~UUID(); //25

	bool isSupported(); //30

	std::string generateUUID(); //35
private:
	class Impl;
	P(Impl) m_impl; //39

	UUID(const UUID&); //41
	UUID& operator=(const UUID&); //42
};

}

#endif