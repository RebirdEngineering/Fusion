#include <gr/dx11/DX11_Context.h>
#include <gr/dx11/DX11_Image.h>
#include <gr/dx11/DX11_Texture.h>
#include <io/FileInputStream.h>
#include <io/FileOutputStream.h>
#include <io/FileFormat.h>
#include <img/ImageReader.h>
#include <img/ImageWriter.h>
#include <gr/GraphicsException.h>
#include <lang/Log.h>

using namespace lang;
using namespace math;
using namespace io;
using namespace img;

namespace gr
{
	DX11_Context::DX11_Context(HWND hwnd, OrientationType orientation) //WIP
	{
		D3D_FEATURE_LEVEL* featureLevel;
		HRESULT hr = D3D11CreateDevice(0, D3D_DRIVER_TYPE_HARDWARE, 0, 0, 0, 0, D3D11_SDK_VERSION, &pid3d11device31C, featureLevel, &pid3d11devicecontext320);

		hr = D3D11CreateDevice(0, D3D_DRIVER_TYPE_SOFTWARE, LoadLibraryW(L"D3D10WARP.dll"), 0, 0, 0, D3D11_SDK_VERSION, &pid3d11device31C, featureLevel, &pid3d11devicecontext320);
		if (FAILED(hr))
			throw Exception(Format("D3D11CreateDevice() failed"));

		createSwapChain(hwnd);

		float4x4 proj(1.0);
		setProjection(proj);
	}

	void DX11_Context::createSwapChain(HWND hwnd) //sub_10003A90 | TODO
	{
		//IDXGIDevice1* device1;
		//IDXGIAdapter* adapter;
		//IDXGIFactory* factory;
		//
		//HRESULT hr = pid3d11device31C->QueryInterface(IID_IDXGIDevice1, (void**)device1);
		//if (FAILED(hr))
		//	throw Exception(Format("Creating SwapChain failed"));
		//
		//HRESULT hr = adapter->QueryInterface(IID_IDXGIAdapter, (void**)device1);
		//if (FAILED(hr))
		//	throw Exception(Format("Creating SwapChain failed"));
		//
		//HRESULT hr = factory->QueryInterface(IID_IDXGIFactory, (void**)device1);
		//if (FAILED(hr))
		//	throw Exception(Format("Creating SwapChain failed"));
		//
		//RECT rect;
		//GetClientRect(hwnd, &rect);
		//
		//DXGI_SWAP_CHAIN_DESC desc;
		//desc.BufferDesc.Width = rect.right - rect.left;
		//desc.BufferCount = 1;
		//desc.BufferDesc.RefreshRate.Denominator = 1;
		//desc.SampleDesc.Count = 1;
		//desc.Windowed = TRUE;
		//desc.BufferDesc.Height = rect.bottom - rect.top;
		//desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		//desc.BufferDesc.RefreshRate.Numerator = 60;
		//desc.BufferUsage = 32;
		//desc.OutputWindow = hwnd;
		//desc.SampleDesc.Quality = 0;
		//desc.Flags = 0;
		//
		//reset(desc.BufferDesc.Width, desc.BufferDesc.Height);
		//factory->MakeWindowAssociation(hwnd, DXGI_MWA_NO_ALT_ENTER);
	}

	DX11_Context::~DX11_Context()
	{
		m_batcher->reset();

		m_plainShader = 0;
		m_plainAlphaShader = 0;
		m_spriteShader = 0;
		m_spriteAlphaShader = 0;
		m_dynamicPrimitives.clear();
		m_uniqueShaders.clear();
	}

	static SurfaceFormat convertToCompatibleSurfaceFormat(const SurfaceFormat& fmt) //Assumed via GLES2
	{
		switch (fmt.type())
		{
		case SurfaceFormat::SURFACE_A8R8G8B8: return SurfaceFormat(SurfaceFormat::SURFACE_A8R8G8B8);
		case SurfaceFormat::SURFACE_DXT1: return SurfaceFormat(SurfaceFormat::SURFACE_DXT1);
		case SurfaceFormat::SURFACE_DXT3: return SurfaceFormat(SurfaceFormat::SURFACE_DXT3);
		case SurfaceFormat::SURFACE_DXT5: return SurfaceFormat(SurfaceFormat::SURFACE_DXT5);
		default: return SurfaceFormat(SurfaceFormat::SURFACE_A8B8G8R8);
		}
	}

	Shader* DX11_Context::createShader(const std::string& name, int flags) //10007730
	{
		PathName pathname(name);
		std::string basename = pathname.basename();

		DX11_Shader* shader = m_uniqueShaders[basename];
		if (shader)
			return shader->clone();

		shader = new DX11_Shader(this, name, PathName(pathname.parent().toString(), basename + ".fx").toString(), flags);
		m_uniqueShaders[basename] = shader;
		return shader;
	}

	Texture* DX11_Context::createTexture(const std::string& filename) //10002E50 | TODO
	{
		P(InputStream) in = new FileInputStream(filename);
		P(ImageReader) rd = new ImageReader(in, guessFileFormat(filename));
		int w = rd->surfaceWidth();
		int h = rd->surfaceHeight();
		img::SurfaceFormat fmt = rd->format();
		
		Texture* tex = createTexture(w, h, rd->mipLevels() - 1, fmt, USAGE_STATIC);
		tex->setName(filename);
		img::SurfaceFormat texfmt = tex->format();
		
		for (int mipLevel = 0; mipLevel < rd->mipLevels(); mipLevel++)
		{
			w = rd->surfaceWidth();
			h = rd->surfaceHeight();
		
			std::vector<uint8_t> texData;
			int dataSize = fmt.getMemoryUsage(w, h);
		
			int pitch = fmt.getMemoryUsage(w, 1);
			rd->readSurface(&texData, pitch, w, h, texfmt, 0, img::SurfaceFormat()); //Correct?
			tex->blt(0, 0, &texData, pitch, mipLevel, w, h, texfmt);
		
			if (mipLevel >= 1)
				statistics.allocatedTextureMemory += dataSize;
		}
		
		return tex;
	}

	Texture* DX11_Context::createTexture(int width, int height, int mipcount, const img::SurfaceFormat& fmt, int usageflags) //10003090
	{
		DX11_Texture* tex = new DX11_Texture(this, width, height, mipcount, usageflags, convertToCompatibleSurfaceFormat(fmt));
		statistics.allocatedTextures++;
		statistics.allocatedTextureMemory += fmt.getMemoryUsage(width, height);
		m_textures.push_back(tex);
		return tex;
	}

	ID3D11DeviceContext* DX11_Context::sub_10002030() //10002030
	{
		return pid3d11devicecontext320;
	}

	[[noreturn]] CubeTexture* DX11_Context::createCubeTexture(const std::string& filename) //10003E00
	{
		throw GraphicsException(Format("Cube textures not supported"));
	}

	Image* DX11_Context::createImage(io::InputStream& in, const std::string& filename) //10003150 | TODO?
	{
		P(InputStream) inPtr = new InputStream(in);
		P(ImageReader) rd = new ImageReader(inPtr, guessFileFormat(filename));
		int w = rd->surfaceWidth();
		int h = rd->surfaceHeight();
		img::SurfaceFormat fmt = rd->format();

		Image* img = createImage(w, h, rd->mipLevels() - 1, fmt, USAGE_STATIC);
		img->getTexture()->setName(filename);
		img::SurfaceFormat imgfmt = img->format();

		for (int mipLevel = 0; mipLevel < rd->mipLevels(); mipLevel++)
		{
			w = rd->surfaceWidth();
			h = rd->surfaceHeight();

			std::vector<uint8_t> imgdata(w * h); //imgdata.resize(w * h); //?
			int dataSize = imgfmt.getMemoryUsage(w, h);

			int pitch = imgfmt.getMemoryUsage(w, 1);
			rd->readSurface(&imgdata, pitch, w, h, imgfmt, 0, img::SurfaceFormat());
			img->blt(0, 0, &imgdata, pitch, mipLevel, w, h, imgfmt);

			if (mipLevel >= 1)
				statistics.allocatedImageMemory += dataSize;
		}

		return img;
	}

	Image* DX11_Context::createImage(int width, int height, int mipcount, const img::SurfaceFormat& fmt, UsageFlags usage) //100011F0
	{
		Image* img = new DX11_Image(this, width, height, mipcount, usage, convertToCompatibleSurfaceFormat(fmt), usage);
		statistics.allocatedImages++;
		statistics.allocatedImageMemory += img->format().getMemoryUsage(width, height);
		return img;
	}

	Primitive* DX11_Context::createPrimitive(Primitive::PrimType prim, const VertexFormat& vf, int vertices, int indices, UsageFlags usage) //100012A0
	{
		return new DX11_Primitive(this, prim, vf, vertices, indices, usage);
	}

	Primitive* DX11_Context::getDynamicPrimitive(Primitive::PrimType prim, const VertexFormat& vf, int vertices, int indices) //10006F50 | TODO
	{
		for (size_t i = 0; i < m_dynamicPrimitives.size(); ++i) //677
		{
			Primitive* p = m_dynamicPrimitives[i]; //679
			if (p->vertexFormat() == vf &&
				p->type() == prim &&
				p->vertices() >= vertices &&
				p->indices() >= indices)
			{
				return p;
			}
		}

		m_dynamicPrimitives.push_back(new DX11_Primitive(this, prim, vf, (vertices + 31) & ~31, (indices + 31) & ~31, Context::USAGE_DYNAMIC));
		return m_dynamicPrimitives.back(); //691
	}

	void DX11_Context::begin2D() //Blank!
	{
	}

	void DX11_Context::end2D() //Blank!
	{
	}

	void DX11_Context::drawLine2D(unsigned int color, int x0, int y0, int x1, int y1, int lineWidth) //10003E90 | TODO
	{
	}

	void DX11_Context::drawLine2D(unsigned int color, int* vertices, int count, int lineWidth) //Blank!
	{
	}

	void DX11_Context::drawCircle2D(unsigned int color, int x, int y, int radius, int lineWidth) //Blank!
	{
	}

	void DX11_Context::fillTriangle2D(unsigned int color, int x0, int y0, int x1, int y1, int x2, int y2)
	{
	}

	void DX11_Context::fillRect2D(unsigned int color, int x, int y, int w, int h, Blend blend)
	{

	}

	void DX11_Context::fillCircle2D(unsigned int color, int x, int y, int radius)
	{
	}

	void DX11_Context::texturizeTriangle2D(Image* image, const float4& scaleBias, int x0, int y0, int x1, int y1, int x2, int y2)
	{
	}

	void DX11_Context::texturizeRect2D(Image* image, const float4& scalebias, int x, int y, int width, int height)
	{
	}

	void DX11_Context::texturizeCircle2D(Image* image, const float4& scalebias, int x, int y, int radius)
	{
	}

	std::string DX11_Context::getGraphicsDriverVendor() //10003DD0
	{
		return "Unknown";
	}

	std::string DX11_Context::getGraphicsDriverVersion() //10003DD0
	{
		return "Unknown";
	}

	std::string DX11_Context::getGraphicsDriverRenderer() //10003DD0
	{
		return "Unknown";
	}

	RenderState2D& DX11_Context::getRenderState2D()
	{
		return m_renderState2D;
	}

	const Rect& DX11_Context::viewport() const
	{
		return m_viewport;
	}

	SurfaceFormat DX11_Context::SurfaceFormat() const
	{
		return SurfaceFormat::SURFACE_A8B8G8R8;
	}

	int DX11_Context::width() const //10001630
	{
		return 0;
	}

	int DX11_Context::height() const //10001650
	{
		return 0;
	}

	float DX11_Context::time() const //10001670
	{
		return 0.0;
	}

	const float3x4& DX11_Context::customModelTransform() const
	{
		return m_customModelTM;
	}

	bool DX11_Context::customModelTransformEnabled() const
	{
		return m_customModelTMEnabled;
	}

	const float4x4& DX11_Context::projectionTransform() const
	{
		return m_projtm;
	}

	const float4x4& DX11_Context::viewTransform() const
	{
		return m_viewtm;
	}

	const float2& DX11_Context::getFovScaleBias() const
	{
		return m_fovScaleBias;
	}

	Context::PlatformType DX11_Context::platform() const
	{
		return PLATFORM_DX11;
	}

	Context::OrientationType DX11_Context::orientation() const
	{
		return m_orientation;
	}

	bool DX11_Context::ready() const
	{
		return true;
	}

	const std::string& DX11_Context::shaderPath() const
	{
		return m_shaderPath;
	}

	void DX11_Context::setRenderState2D(const RenderState2D& state)
	{
		m_renderState2D = state;
	}

	void DX11_Context::setViewport(const Rect& rect)
	{
		
	}

	void DX11_Context::setClipRect(const Rect& rect)
	{

	}

	void DX11_Context::setWireframeEnabled(bool enabled)
	{

	}

	void DX11_Context::setOrientation(OrientationType orientation)
	{
		m_orientation = orientation;
	}

	void DX11_Context::setFovScaleBias(const float2& scalebias) //10001780
	{
		m_fovScaleBias = scalebias;
	}

	void DX11_Context::setCustomModelTransform(const float3x4& customtm) //100017A0
	{
		m_customModelTM = customtm;
	}

	void DX11_Context::setCustomModelTransformEnabled(bool enabled) //100017C0
	{
		m_customModelTMEnabled = enabled;
	}

	void DX11_Context::setPerspectiveProjection(float aspect, float fov, float front, float back) //100017D0
	{
		float4x4 tm(m_projtm);
		tm.setPerspectiveProjection(aspect, fov, front, back);
	}

	void DX11_Context::setOrthographicProjection() //10001830
	{
		setProjection(float4x4(1.f));
	}

	void DX11_Context::setProjection(const float4x4& projtm)
	{
		m_projtm = projtm;
		if (m_renderTarget)
		{
			float4x4 invy(1.0f); //1198
			invy *= m_projtm; //?
		}
	}

	void DX11_Context::setViewTransform(const float4x4& viewtm) //10001900
	{
		m_viewtm = viewtm;
	}

	void DX11_Context::setTime(float time) //10001920
	{
		m_time = time;
	}

	void DX11_Context::setShaderPath(const std::string& path) //100052B0
	{
		m_shaderPath = path;
	}

	void DX11_Context::reset(int w, int h) //100052D0
	{
		//Autogen?
		//delete pid3d11rendertargetview328;
		//delete pid3d11depthstencilview33C;
		//delete pid3d11rendertargetview338;

		DXGI_SWAP_CHAIN_DESC desc;
		pidxgiswapchain324->GetDesc(&desc);

		HRESULT hr = pidxgiswapchain324->ResizeBuffers(desc.BufferCount, w, h, desc.BufferDesc.Format, desc.Flags);

		if (FAILED(hr))
			throw Exception(Format("Resizing SwapChain failed"));

		ID3D11Resource* surface = 0;

		hr = pidxgiswapchain324->GetBuffer(0, IID_ID3D11Texture1D, (void**)surface);

		if (FAILED(hr))
			throw Exception(Format("Getting backbuffer failed"));

		hr = pid3d11device31C->CreateRenderTargetView(surface, 0, &pid3d11rendertargetview328);

		if (FAILED(hr))
			throw Exception(Format("Getting backbuffer failed"));

		hr = pidxgiswapchain324->GetDesc(&desc);

		if (FAILED(hr))
			throw Exception(Format("GetDesc failed"));

		if (m_width == w || m_height == h)
			return;

		m_width = w;
		m_height = h;

		setViewport(Rect(0, 0, width(), height()));

		//Autogen?
	}

	void DX11_Context::beginScene()
	{

	}

	void DX11_Context::endScene()
	{

	}

	void DX11_Context::reloadShaders()
	{

	}

	void DX11_Context::present() //10005620
	{
		m_batcher->flush();
		HRESULT hr = pidxgiswapchain324->Present(0, 0);

		if (FAILED(hr))
			throw Exception(Format("Cannot present context"));
	}

	void DX11_Context::getColorF(int color, float* colorf) //Inlined
	{
		img::SurfaceFormat fmt(SurfaceFormat::SURFACE_A32B32G32R32F);
		fmt.copyPixels(colorf, img::SurfaceFormat(), 0, SurfaceFormat::SURFACE_A8R8G8B8, this, img::SurfaceFormat(), 0, 1);
	}

	void DX11_Context::clear(unsigned int color, bool clearColor, bool clearDepth, bool clearStencil) //10001F10
	{
		m_batcher->flush();
		setClipRect(m_renderState2D.getClip());

		unsigned int clearFlags;

		float colorf[4]; 
		getColorF(color, colorf);

		if (clearColor)
			pid3d11devicecontext320->ClearRenderTargetView(pid3d11rendertargetview338, colorf);

		if (pid3d11depthstencilview33C)
		{
			if (clearDepth)
				clearFlags |= D3D11_CLEAR_DEPTH;

			if (clearStencil)
				clearFlags |= D3D11_CLEAR_STENCIL;

			pid3d11devicecontext320->ClearDepthStencilView(pid3d11depthstencilview33C, clearFlags, 0.5, 0);
		}
	}

	void DX11_Context::capture(const std::string& filename) //10001930
	{
		FileOutputStream out(filename);
		FileFormat ff = guessFileFormat(filename);
		capture(out, ff);
	}

	void DX11_Context::capture(OutputStream& out, FileFormat ff) //100056F0 |
	{
		m_batcher->flush();

		int width = m_renderTarget ? m_renderTarget->width() : m_width;
		int height = m_renderTarget ? m_renderTarget->height() : m_height;

		std::vector<unsigned int> data;
		std::vector<unsigned int> reserved;

		Texture* tex = createTexture(width, height, 0, SurfaceFormat(), USAGE_DYNAMIC);

		if (m_renderTarget)
		{
			//pid3d11devicecontext320->CopyResource(tex->sub_1000CDF0(), m_renderTarget->sub_1000CDF0());
		}

		else
		{
			//dword324->
			//pid3d11devicecontext320->CopyResource(tex->sub_1000CDF0(), 0);
		}

		//if (FAILED(pid3d11devicecontext320->Map(? , 0, D3D11_MAP_READ, 0, tex))
		{
			throw GraphicsException(Format("Texture Map failed"));
		}

		ImageWriter::write(out, ff, &data, width, height, SurfaceFormat::SURFACE_A8B8G8R8, SurfaceFormat());
		//pid3d11devicecontext320->Unmap(tex->sub_10002030(), ) //Autogen?
	}

	P(Image) DX11_Context::capture(P(Image) image) //TODO
	{
		m_batcher->flush();

		return image;
	}

	void DX11_Context::flipWindingOrder() //10002040
	{
		m_batcher->flush();
	}

	void DX11_Context::hibernateContext()
	{
	}

	void DX11_Context::resumeContext()
	{
	}

	void DX11_Context::flush() //10002040
	{
		m_batcher->flush();
	}

	void DX11_Context::saveCachedState(const std::string& name)
	{
		//m_stateStorage[name] = GL_State::sm_current; //
	}

	void DX11_Context::restoreCachedState(const std::string& name)
	{
		//if (&m_stateStorage.find(name))
			//m_stateStorage[name] = GL_State::sm_current;
	}

	void DX11_Context::resetCachedState()
	{
	}

	void* DX11_Context::getBackbuffer() //100021D0
	{
		ID3D11Texture2D* backBuffer = 0;
		HRESULT hr = pidxgiswapchain324->GetBuffer(0, IID_ID3D11Texture2D, (void**)backBuffer);

		if (SUCCEEDED(hr))
			return backBuffer;

		//backBuffer->Release(); //Autogen?

		return 0;
	}
}