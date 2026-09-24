#ifndef _UTIL_TRAVERSEJSON_H
#define _UTIL_TRAVERSEJSON_H

#include <util/JSONVisitor.h>

class cJSON;

namespace util
{

void traverseJSON(const cJSON* item, JSONVisitor& visitor);

void traverseJSON(const char* json, JSONVisitor& visitor);

}

#endif