#ifndef _LANG_UNIQUE_PTR_H
#define _LANG_UNIQUE_PTR_H

#include <lang/pp.h>

namespace lang
{

//?

}

#define UP(MYCLASS) lang::unique_ptr<MYCLASS,lang::detail::default_delete<MYCLASS>>

#endif