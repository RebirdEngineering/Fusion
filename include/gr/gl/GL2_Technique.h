#ifndef _GR_GL2_TECHNIQUE_H
#define _GR_GL2_TECHNIQUE_H

#include "GL_common.h"
#include <gr/gl/GL2_Pass.h>

BEGIN_NAMESPACE(gr)
BEGIN_NAMESPACE(GL_NAMESPACE) //I'm just as confused as you are

class GL_Technique : //no cpp
	public lang::Object
{
public:
	GL_Technique(const std::string& name) :
		m_name(m_name)
	{
	}

	GL_Technique* clone() const
	{
		return new GL_Technique(*this);
	}
	~GL_Technique()
	{
		m_passes.clear();
	}

	const std::string& getName() const
	{
		return m_name;
	}

	GL_Pass* getPass(int pass) const
	{
		return m_passes[pass];
	}

	int getPassCount() const
	{
		return m_passes.size();
	}

	void addPass(GL_Pass* pass)
	{
		for (int i = 0; i < m_passes.size(); i++)
		{
			m_passes[i]->begin(); //?
		}
		//m_passes.push_back(pass); //?
	}
private:
	GL_Technique(const GL_Technique& other) :
		m_name(other.m_name)
	{
		for (int i = 0; i < m_passes.size(); i++)
		{
			m_passes[i]->clone();
		}
	}
	GL_Technique& operator=(const GL_Technique&);

	std::string m_name;
	std::vector<P(GL_Pass)> m_passes;

};

}
}

#endif