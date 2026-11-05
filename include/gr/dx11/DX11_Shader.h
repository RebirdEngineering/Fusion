#ifndef _GR_DX11_SHADER_H
#define _GR_DX11_SHADER_H

#include "DX11_common.h"
#include <gr/Shader.h>

namespace math
{ 
	class float4x4;}
	

BEGIN_NAMESPACE(gr) 

	
class BaseTexture;
class DX11_Context;

	
/**
 * DirectX surface shader.
 */
class DX11_Shader : //0x48 bytes.
	public Shader
{
public:
	/**
	 * Initializes the shader from fx file source code.
	 * @param context Rendering context.
	 * @param name Name of the shader.
	 * @param fxfilename FX source code file name.
	 * @param flags Compilation flags. See NS(Shader,Flags).
	 */
	explicit DX11_Shader( DX11_Context* context, const std::string& name, 
		const std::string& fxfilename, int flags );

	///
	~DX11_Shader();

	/**
	 * Returns clone of this shader.
	 * All parameters are unique to each clone, but code
	 * and other constants are shared.
	 */
	Shader*	clone() const;

	/**
	 * Sets rendering technique to be used when rendering objects using this shader.
	 * If the requested technique is not supported, the shader is disabled.
	 * @param name Name of the rendering technique to be set. Pass 0 or empty string to restore default technique.
	 */
	void	setTechnique( const char* name );

	/**
	 *
	 */
	bool		hasTechnique(const char* name);

	/**
	 * Sets shader texture parameter.
	 */
	void	setTexture( ParamType param, BaseTexture* value );

	/**
	 * Sets custom shader texture parameter which is not defined in ParamType.
	 */
	void	setTexture( const char* name, BaseTexture* value );

	/**
	 * Sets shader 4x4 matrix parameter.
	 */
	void	setMatrix( ParamType param, const NS(math,float4x4)& value );

	/**
	 * Sets custom shader 4x4 matrix parameter which is not defined in ParamType.
	 */
	void	setMatrix( const char* name, const NS(math,float4x4)& value );

	/**
	 * Sets shader 4x4 matrix array parameter.
	 */
	void	setMatrixArray( ParamType param, NS(math,float4x4)** values, int count );

	/**
	 * Sets shader 4-vector parameter.
	 */
	void	setVector( ParamType param, const NS(math,float4)& value );

	/**
	 * Sets custom shader 4-vector parameter which is not defined in ParamType.
	 */
	void	setVector( const char* name, const NS(math,float4)& value );

	/**
	 * Sets shader float parameter.
	 */
	void	setFloat( ParamType param, float value );

	/**
	 * Sets custom float parameter which is not defined in ParamType.
	 */
	void	setFloat( const char* name, float value );

	/**
	 * Gets shader texture parameter or 0 if texture not set.
	 */
	BaseTexture*	getTexture( const char* name );

	/**
	 * Gets shader matrix parameter or 0 if texture not set.
	 */
	NS(math,float4x4)	getMatrix( const char* name );

	/**
	 * Gets shader vector parameter or 0 if texture not set.
	 */
	NS(math,float4)	getVector( const char* name );

	/**
	 * Gets shader float parameter or 0 if texture not set.
	 */
	float			getFloat( const char* name );

	/**
	 * Begins rendering geometry using the shader.
	 * Prefer not using this method directly, but use Begin helper class instead.
	 * Rendering sequence:
	 * <ol>
	 * <li>First call NS(Shader,begin)() for the shader before rendering any geometry
	 * <li>Set shader parameters which need to be updated every frame, like transforms.
	 * <li>Call NS(Shader,beginPass)(0) to start rendering geometry using the first pass of the shader.
	 * <li>Call render() for each primitive to be rendered.
	 * <li>Call NS(Shader,endPass)() to stop rendering using this pass of the shader.
	 * <li>Loop to NS(Shader,beginPass)(i) for other passes, as many times as return value of begin() specified.
	 * <li>End rendering by calling NS(Shader,end)() for the shader.
	 * @return Number of passes to be rendered. 0 if shader is disabled.
	 */
	int		begin();
	
	/**
	 * Begins rendering using specified pass. See begin() for description
	 * of the rendering sequence.
	 */
	void	beginPass( int pass );

	/**
	 * Ends rendering using specified pass. See begin() for description
	 * of the rendering sequence.
	 */
	void	endPass();

	/**
	 * Ends rendering using this shader. See begin() for description
	 * of the rendering sequence.
	 */
	void	end();

	/**
	 * Sets name of the shader.
	 */
	void	setName( const std::string& name );

	/**
	 * Sets shader sorting mode.
	 */
	void	setSort( SortType sort );

	/**
	 * Called before reseting device.
	 */
	void	deviceLost();

	/**
	 * Called after reseting device.
	 */
	void	deviceReset();

	/**
	 * Returns priority of the shader.
	 * Higher priority shaders need to be rendered before lower priority ones.
	 * Default priority is 0. Priorities can be negative.
	 */
	int		priority() const;

	/**
	 * Returns preferred sort mode of the shader.
	 * Default sort mode is SORT_NONE.
	 */
	SortType sort() const;

	/**
	 * Returns true if the shader is enabled.
	 */
	bool	enabled() const;

	/**
	 * Returns name of the shader.
	 */
	const std::string& name() const;

	/**
	 * Returns object string description.
	 */
	std::string		toString() const;

private:
	int passes10;
	int currentPass14;
	bool				m_enabled; //0x18
	int8_t				m_priority; //0x19

	std::string			m_name; //0x1C

	SortType			m_sort; //0x38

	DX11_Shader( const DX11_Shader& );
	DX11_Shader& operator=( const DX11_Shader& );
};


} // gr


#endif // _GR_DX11_Shader_H
