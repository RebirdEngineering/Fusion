#ifndef _GR_GL_CREATECONTEXT_H
#define _GR_GL_CREATECONTEXT_H

#include <gr/Context.h>

BEGIN_NAMESPACE(gr)

#ifndef GL2  //I'm just as confused as you are
BEGIN_NAMESPACE(gles2)
#else
BEGIN_NAMESPACE(gl1)
#endif

Context* GL_createContext(int w, int h, Context::OrientationType orientation, void (*presentFunc)());

}
}

#endif