#include <util/traverseJSON.h>
#include <lang/Exception.h>
#include <external/cJSON/cJSON.h>

using namespace lang;

namespace util
{

void traverseJSON(const cJSON* item, JSONVisitor& visitor) //17 | Correct?
{
	while (item)
	{
		const char* name = item->string; //20

		const int type = item->type; //22

		switch (type)
		{
		case cJSON_False: visitor.visit(name, false); item->next; continue; //27
		case cJSON_True: visitor.visit(name, true); item->next; continue; //30
		case cJSON_NULL: visitor.visit(name); item = item->next; continue; //33
		case cJSON_Number: visitor.visit(name, item->valuedouble); item = item->next; break; //36 | ?
		case cJSON_String: visitor.visit(name, item->valuestring); item = item->next; continue; //39 | ?
		case cJSON_Array: break; visitor.startArray(name); traverseJSON(item->child, visitor); visitor.endArray(); break; //
		case cJSON_Object: break; visitor.startObject(name); traverseJSON(item->child, visitor); visitor.endObject(); break; //?
		default: item = item->next; break;
		}
	}
}

void traverseJSON(const char* json, JSONVisitor& visitor) //60
{
	if (json)
	{
		cJSON* root = cJSON_Parse(json); //64

		if (root)
		{
			traverseJSON(root->child, visitor); //68
			cJSON_Delete(root); //69
		}

		else
			throwError(Exception(Format("JSON parsing failed here: {0}", cJSON_GetErrorPtr()))); //73
	}
}

}