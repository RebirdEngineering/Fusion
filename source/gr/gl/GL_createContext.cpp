#include <gr/gl/GL_createContext.h>
#include <gr/gl/GL_Context.h>
//#include <gr/gl/GL2_Shader_Platform.h>

BEGIN_NAMESPACE(gr)
BEGIN_NAMESPACE(GL_NAMESPACE) //if ABS410 iOS

void createShadersTemplates(GL_Context* context)
{
#ifdef GL1 //Exists on GL1
	//context->addShaderTemplate(new GL_Shader_Default(this, "unlit-plain", 4096));
	//context->addShaderTemplate(new GL_Shader_Default(this, "unlit-tex", 4096));
	//context->addShaderTemplate(new GL_Shader_Default(this, "unlit-tex-alpha", 4096));
	//context->addShaderTemplate(new GL_Shader_Default(this, "diff-plain", 4096));
	//context->addShaderTemplate(new GL_Shader_Default(this, "diff-tex", 4096));
	//context->addShaderTemplate(new GL_Shader_Default(this, "diff-tex-alpha", 4096));
	//context->addShaderTemplate(new GL_Shader_Default(this, "diff-tex-alpha", 4096));
	//context->addShaderTemplate(GL_Shader_Default::setBlend(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	//context->addShaderTemplate(new GL_Shader_Default(this, "sprite-alpha", 4096));
	//context->addShaderTemplate(new GL_Shader_Default(this, "sprite-plain", 4096));
	//context->addShaderTemplate(new GL_Shader_Default(this, "sprite-alphaplain", 4096));
	//context->addShaderTemplate(new GL_Shader_Default(this, "sprite-alphaplain", 4096));
	//context->addShaderTemplate(new GL_Shader_Default(this, "sprite-alpha-reversed", 4096));
	//context->addShaderTemplate(new GL_Shader_Default(this, "sprite-alpha-reversed", 4096));
	//context->addShaderTemplate(new GL_Shader_Default(this, "lines-debug", 4096));
#endif
}


Context* GL_createContext(int w, int h, Context::OrientationType orientation, void (*presentFunc)()) //63 | On Android, no presentFunc?
{
	Context* context = new GL_Context(orientation == Context::ORIENTATION_90 ? h : w, orientation == Context::ORIENTATION_90 ? w : h, orientation, presentFunc); //71
	//Context* context = new GL_Context((orientation & 0xFFFFFFFD ? h : w), w, orientation, presentFunc); //According to decomp?
	createShadersTemplates((GL_Context*)context); //Function exists on Android (GLES2) but doesn't appear on iOS.
	return context; //Return var name is likely for GL1
}

}
}