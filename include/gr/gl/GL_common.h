#ifndef _GR_GL_COMMON_H
#define _GR_GL_COMMON_H

//Potentially unofficial header. Based off KA3D.

#include <external/glew/include/GL/glew.h> //OSX and supposedly Win? GL2, GLES2
#include <lang/pp.h>

//Realistically given they use the EXACT same files, here's some hackjobs
#ifdef GLES2
#define GL_NAMESPACE gles2
#include "GL2_Shader.h"
#endif

#ifdef GLES1
//#include <gl/GL.h>
//#include <gl/glext.h>
//#include "GL1_Shader.h"
#define GL_NAMESPACE gles1
#endif

#ifdef GL2
//#include <GLES/GL.h>
//#include <gl/glext.h>
#define GL_NAMESPACE gl2
#include "GL2_Shader.h"
#endif

#ifdef GL1
//#include <external/glew/include/GL/glew.h> //OSX and supposedly Win? GL2, GLES2
#define GL_NAMESPACE gl1
//#include "GL1_Shader.h"
#endif


#endif