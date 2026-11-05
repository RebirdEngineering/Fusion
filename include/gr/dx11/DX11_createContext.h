#ifndef _GR_DX11_CREATECONTEXT_H
#define _GR_DX11_CREATECONTEXT_H

#include <gr/Context.h>

namespace gr
{

Context* DX11_createContext(int w, int h, Context::OrientationType orientation, void (*presentFunc)());

}

#endif