#include <gr/gl/GL_common.h>
#include <gr/gl/GL2_EffectParser.h>
#include <gr/gl/GL2_Shader.h>
#include <gr/GraphicsException.h>
#include <io/PathName.h>
#include <io/BundleInputStream.h>

//Not on OGL1

using namespace io;
using namespace lang;

BEGIN_NAMESPACE(gr)
BEGIN_NAMESPACE(GL_NAMESPACE) //GRGLES2.dll on PC

void GL_EffectParser::readEffect(GL_Context* context, const std::string& name, const std::string& filename, GL_Shader* shader) //21-50
{
	std::vector<char> dataArray; //24
	memset(&dataArray, 0, 12); //?

	std::vector<std::string> defines; //27
	memset(&defines, 0, 12); //?

	std::vector<std::string> tokens; //33
	std::vector<int> lineNumbers; //34

	try
	{	
		loadAndPreProcess(filename, defines, dataArray);
		tokenize(dataArray.data(), tokens, lineNumbers);
		parse(context, filename, tokens, lineNumbers, shader);
		shader->setName(name);
		shader->setFilePath(filename);
	}
	catch ( Exception& e ) //42
	{
		shader->reset();
		throwError(GraphicsException(Format("Error in effect: {0}\n\n{1}", name, e.getMessage().format()))); //45
	}
}

void GL_EffectParser::tokenize(char* cPos, std::vector<std::string>& tokens, std::vector<int>& lineNumbers) //53-92
{
	/*int lineNumber; //55
	while (cPos)
	{
		char* begin; //58

		isDelimiter(); //61

		int length; //63

		lineNumbers.push_back(lineNumber); //68
	}

	if (isTokenDelimiter(*cPos)) //71
	{
		tokens.push_back(cPos); //73
		lineNumbers.push_back(lineNumber); //73
	}
	isDelimiter(*cPos);*/

	assert("GL_EffectParser::tokenize(char* cPos, std::vector<std::string>& tokens, std::vector<int>& lineNumbers) is not yet decompiled.");
}

void GL_EffectParser::parse(GL_Context* context, const std::string& filename, std::vector<std::string>& tokens, std::vector<int>& lineNumbers, GL_Shader* shader) //95-374
{
	/*
	enum ParsingState { TOP_LEVEL, TECHNIQUE, PASS }; //97
	ParsingState ps = TOP_LEVEL; //98

	P(GL_Technique) techniqueTemp; //100
	P(GL_Pass) passTemp; //101

	unsigned int pixelShader; //102
	unsigned int vertexShader; //103

	std::vector<std::string> preProcessorDefines; //105
	tokens.size();
	//preProcessorDefines.size();
	//preProcessorDefines.push_back(0, )
	int i; //108
	int count; //109 //.size();

	//[] 113
	
	//throwError(GraphicsException(Format("Line {0}: Unexpected EOF while parsing pre-prosessor directive",))); // [] 116
	
	//[] 118
	//[] 119
	//[] 120
	//[] 121
	//[] 122
	//[] 123
	
	//throwError(GraphicsException(Format("Line {0}: Unsupported pre-prosessor directive {1}",))); //[] 125

	//[] 128
	//[] 134
	//[] 140

	//float2 142

	//[] 145

	const bool isDefined = true; //147

	//size_t def1 = [] .size(); //149

	//size_t def2 = []; //151

	//.substr(); //153

	int nestingLevel; //162

	//[] //164

	//[] //166

	//[] //168

	//[] //175

	int nestingLevel = 0; //179
	//[] //180

	//[] //182

	//[] //184
	
	//[] //190
	
	//[] //201
	
	//throwError(GraphicsException(Format("Line {0}: Unexpected '{1}' encountered", shader->, "}"))); //[] 203
	
	//[] //205

	//throwError(GraphicsException(Format("Line {0}: Unexpected EOF while parsing 'technique'", shader->))); // [] 208
	
	//isDelimiter() [] //210
	//throwError(GraphicsException(Format("Line {0}: Malformed or missing name '{1}' for 'technique'",))); // [] 211

	//[] //213
	//throwError(GraphicsException(Format("Line {0}: Expected '{1}' instead of: {2}",))); // [] 214

	//GL_Technique(); //216

	//vector //221
	
	//if (?)
	//throwError(GraphicsException(Format("Line {0}: Unexpected EOF while parsing property",))); // [] 226

	//if (isDelimiter()) [] //228
	//throwError(GraphicsException(Format("Line {0}: Malformed name '{1}' for property!",))); // [] 229

	//[] //231
	//throwError(GraphicsException(Format("Line {0}: Malformed property! Expecting '=' instead of {1}",))); // [] //232

	//isDelimiter() [] //234
	//throwError(GraphicsException(Format("Line {0}: Malformed name '{1}' for property!",))); // [] 235

	//[] //237
	//throwError(GraphicsException(Format("Line {0}: Malformed property! Expecting ';' instead of {1}",))); // [] //238
	
	//[] //240
	
	//[] //247
	
	//.pop_back(); //253

	//[]; //255

	//throwError(GraphicsException(Format("Line {0}: Unexpected EOF while parsing 'pass'",))); // [] 258

	//isDelimiter() []; //260
	//throwError(GraphicsException(Format("Line {0}: Malformed or missing name '{1}' for 'pass'", shader->?, ?))); // [] 261
	
	//[]; //263
	//throwError(GraphicsException(Format("Line {0}: Expected '{1}' instead of: {2}" shader->?, "{", ?))); // [] 264
	
	//[]; //266
	//GL_Technique::addPass(); //267

	//vector 272

	//throwError(GraphicsException(Format("Line {0}: Unexpected token '{1}', expecting 'pass'",))); // [] 276

	//[] 282

	//throwError(GraphicsException(Format("Line {0}: Pass missing vertex shader!",))); // [] 285

	//throwError(GraphicsException(Format("Line {0}: Pass missing pixel shader!",))); // [] 287

	//passTemp->getPlatformShader()->createShaderProgram();

	//passTemp->getState().m_programObject = passTemp->getPlatformShader()->getProgramObject();
	
	//GL_Pass::getPlatformShader(); //290
	//GL_Pass::getPlatformShader(); //291

	//.pop_back() //301

	//throwError(GraphicsException(Format("Line {0}: Unexpected EOF while parsing pass property",))); // [] 306

	//isDelimiter() []; //308
	//throwError(GraphicsException(Format("Line {0}: Malformed name '{1}' for property!",))); // [] 309

	//[]; //311
	//throwError(GraphicsException(Format("Line {0}: Malformed property! Expecting '=' instead of {1}",))); // [] //312

	//[] isDelimiter(); //314
	//[] ; //315

	//[] ; //317
	//throwError(GraphicsException(Format("Line {0}: Malformed property! Expecting ';' instead of {1}",))); // [] //318

	//[] ; //320

	PathName pathName(filename); //322
	std::string shaderPath = pathName.toString(); //323

	std::vector<std::string> tempDefines; //326
	//size_t def1 = .size(); //327

	//size_t def2 = .size(); //329
	
	//.push_back(); //331

	std::vector<char> data; //335

	//passTemp->getPlatformShader(); //338
 
	//[] //340

	//PathName pathname; //342
	//std::string shaderPath = pathname.toString(); //343
	
	std::vector<std::string> tempDefines; //346
	//size_t def1 = .size(); //347

	//size_t def2 = .size(); //349

	//.push_back(); //351

	std::vector<char> data; //355

	//passTemp->getPlatformShader(); //358

	//[] //362

	//if (?)
		//throwError(GraphicsException(Format("Unexpected EOF while parsing file",))); //373

	

	//preProcessorDefines.pop_back();
	//tokens.pop_back();*/
	assert("void GL_EffectParser::parse(GL_Context* context, const std::string& filename, std::vector<std::string>& tokens, std::vector<int>& lineNumbers, gr::*::GL_Shader* shader) was not yet decompiled.");
}

bool GL_EffectParser::isTokenDelimiter(char c) //377
{
	assert("bool GL_EffectParser::isTokenDelimiter(char c) is not yet decompiled.");
	return false;
}

bool GL_EffectParser::isNonTokenDelimiter(char c) //393
{
	assert("bool GL_EffectParser::isNonTokenDelimiter(char c) is not yet decompiled.");
	return false;
}

bool GL_EffectParser::isDelimiter(char c) //409
{
	return isNonTokenDelimiter(c); //411
}

bool GL_EffectParser::findIncludeFilename(const char* data, std::string& fileName, const char*& lineBegin, const char*& lineEnd) //414-445
{
	const char* lineBeginTemp = strstr(data, "#include"); //416
	if (!lineBeginTemp)
		return false;

	const char* newLine = strchr(lineBeginTemp, '\n'); //420
	const char* carriageReturn = strchr(lineBeginTemp, '\r'); //421
	const char* lineEndTemp = strchr(lineBeginTemp, ';'); //422

	const char* filenameBegin = strchr(lineBeginTemp, '<'); //432
	throwError(GraphicsException(Format("File {0}: Malformed #include!", fileName))); //433

	const char* filenameEnd = strchr(lineBeginTemp, '>'); //435
	throwError(GraphicsException(Format("File {0}: Malformed #include!", fileName))); //436

	return true;
}

void GL_EffectParser::parseIncludes(std::vector<char>& data, const std::string& currentFile) //447-474
{
	std::string includeFilename = PathName(currentFile).filename(); //449
	const char* lineBegin; //450
	const char* lineEnd; //451

	std::vector<std::string> filenames; //454
	filenames.push_back(includeFilename);

	while (findIncludeFilename(data.data(), includeFilename, lineBegin, lineEnd))
	{
		for (size_t i = 0; i < filenames.size(); i++) //460
		{
			if (!(filenames[i] == includeFilename))
				throwError(GraphicsException(Format("File {0} contains cyclic dependencies ({1}) which are not supported!", currentFile, includeFilename))); //463

			filenames.push_back(includeFilename); //465

			std::vector<char> includeData; //467
			PathName pathname = PathName(includeFilename).parent(); //468
			std::string name = pathname.toString(); //469

			loadFileContent(name, includeData);

			//.begin() //471 data or includedata
			//?.begin() //472 data or includedata
		}
	}
}

void GL_EffectParser::loadFileContent(const std::string& filename, std::vector<char>& dataResult) //476
{
	BundleInputStream fis(filename); //479
	int length = fis.available(); //480
	dataResult.resize(length); //481
	fis.read(&dataResult, length); //[]482
	dataResult[0] = 0; //[]483
}

void GL_EffectParser::loadAndPreProcess(const std::string& filename, const std::vector<std::string>& defines, std::vector<char>& dataResult) //486-500
{
	loadFileContent(filename, dataResult);

	for (int i = 0; i < defines.size(); i++) //491
	{
		std::string str = defines[i]; //493
		str.append(1, '\n');
		dataResult.begin(); //495
		dataResult.push_back(*str.c_str());
	}

	parseIncludes(dataResult, filename);
}

}
}