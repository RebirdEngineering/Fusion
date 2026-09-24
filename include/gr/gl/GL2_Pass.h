#ifndef _GR_GL_GL2_PASS_H
#define _GR_GL_GL2_PASS_H

#include "GL_common.h"
#include "GL_State.h"
#include <lang/Object.h>

BEGIN_NAMESPACE(gr)
BEGIN_NAMESPACE(GL_NAMESPACE) //I'm just as confused as you are

class GL_Shader_Platform;

class GL_Pass : //14
    public lang::Object
{
public:
    GL_Pass(const std::string& name); //18
    ~GL_Pass(); //19

    GL_Pass* clone() const; //21

    void addProperty(const std::string& key, const std::string& value); //29

    GL_Shader_Platform* getPlatformShader(); //31

    GL_State& getState(); //33

    void begin(); //35
    void end(); //36
private:
    GL_State m_state; //43
    std::string m_name; //44
    P(GL_Shader_Platform) m_platformShader; //44

    GL_Pass(const GL_Pass& other); //39
    GL_Pass& operator=(const GL_Pass&); //40
};

}
}

#endif