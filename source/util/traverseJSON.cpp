#include <util/traverseJSON.h>
#include <lang/Exception.h>
#include <external/cJSON/cJSON.h>
#include <external/vJSON/vJSON.h>

using namespace lang;

namespace util
{

void traverseJSON(const cJSON* item, JSONVisitor& visitor) //?
{
	while (item)
	{
		const int type = item->type;
		const char* name = item->string;
		switch (type)
		{
		case JSON_NULL: visitor.visit(name, false); break;
		case JSON_OBJECT: visitor.visit(name, true); break;
		case JSON_ARRAY: visitor.visit(name); break;
		case JSON_STRING: visitor.visit(name, item->valuedouble); break; //?
		case JSON_INT: visitor.visit(name, item->valuestring); item = item->next; continue; //?
		case JSON_FLOAT: break; visitor.startArray(name); traverseJSON(item->child, visitor); visitor.endArray(); break; //?
		case JSON_BOOL: break; visitor.startObject(name); traverseJSON(item->child, visitor); visitor.endObject(); break; //?
		default: item = item->next; break;
		}
	}
}

void traverseJSON(const char* json, JSONVisitor& visitor)
{
	if (!json)
		return;
	cJSON* root = cJSON_Parse(json);
	if (!root)
		throwError(Exception(Format("JSON parsing failed here: {0}", cJSON_GetErrorPtr())));
	traverseJSON(root->child, visitor);
	cJSON_Delete(root);
}

}