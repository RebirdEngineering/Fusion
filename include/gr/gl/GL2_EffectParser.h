#ifndef _GR_GL2_EFFECTPARSER_H
#define _GR_GL2_EFFECTPARSER_H

#include "GL_common.h"
#include <lang/pp.h>

//Not on OGL1

BEGIN_NAMESPACE(gr)
BEGIN_NAMESPACE(GL_NAMESPACE) //I'm just as confused as you are

class GL_Context;
class GL_Shader;

class GL_EffectParser
{
public:
	static void readEffect(GL_Context* context, const std::string& name, const std::string& filename, GL_Shader* shader); //18 | Mangled symbol suggests this order.
private:
	static bool isTokenDelimiter(char c); //24

	static bool isNonTokenDelimiter(char c); //29

	static bool isDelimiter(char c); //34

	static void tokenize(char* cPos, std::vector<std::string>& tokens, std::vector<int>& lineNumbers); //39

	static void parse(GL_Context* context, const std::string& filename, std::vector<std::string>& tokens, std::vector<int>& lineNumbers, GL_Shader* shader); //44

	static void loadAndPreProcess(const std::string& filename, const std::vector<std::string>& defines, std::vector<char>& dataResult); //49

	static bool findIncludeFilename(const char* data, std::string& fileName, const char*& lineBegin, const char*& lineEnd); //54

	static void parseIncludes(std::vector<char>& data, const std::string& currentFile); //60

	static void loadFileContent(const std::string& filename, std::vector<char>& dataResult); //65
};

}
}

#endif