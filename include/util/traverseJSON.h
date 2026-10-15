#ifndef _UTIL_TRAVERSEJSON_H
#define _UTIL_TRAVERSEJSON_H

#include <util/JSONVisitor.h>

struct cJSON;

namespace util
{

static void traverseJSON(const cJSON* item, JSONVisitor& visitor);

static void traverseJSON(const char* json, JSONVisitor& visitor);

}

#endif