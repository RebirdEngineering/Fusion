#include <gr/dx11/DX11_common.h>
#include <gr/dx11/DX11_Texture.h>
#include <gr/dx11/DX11_Context.h>
#include <gr/GraphicsException.h>

using namespace lang;
using namespace img;

namespace gr
{
	DX11_Texture::DX11_Texture(DX11_Context* context, int width, int height, int mipcount, int usageflags, SurfaceFormat format) : //1000CEC0
		m_width(width),
		m_height(height),
		m_format(format),
		m_context(context),
		id3d11texture2d3c(0),
		pid3d11shaderresourceview40(0),
		pid3d11rendertargetview44(0)
	{
		ID3D11Device* device = m_context->device();

		//bool unk = format.type() == SurfaceFormat::SURFACE_A8R3G3B2; //?

		D3D11_TEXTURE2D_DESC desc;
		desc.Width = width;
		desc.Width = height;
		desc.MipLevels = mipcount + 1;
		desc.ArraySize = 1;

		DXGI_FORMAT dxFormat; // = m_context->;

		switch (format.type())
		{
		case SurfaceFormat::SURFACE_DXT1: dxFormat = DXGI_FORMAT_BC1_UNORM; break;
		case SurfaceFormat::SURFACE_DXT3: dxFormat = DXGI_FORMAT_BC2_UNORM; break;
		case SurfaceFormat::SURFACE_DXT5: dxFormat = DXGI_FORMAT_BC3_UNORM; break;
		case SurfaceFormat::SURFACE_A8R8G8B8: dxFormat = DXGI_FORMAT_B8G8R8A8_UNORM; break;
		case SurfaceFormat::SURFACE_A8B8G8R8: dxFormat = DXGI_FORMAT_R8G8B8A8_UNORM; break;
		//default: m_format = m_context->
		}

		desc.Format = dxFormat;

		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;

		desc.Usage = (usageflags & Context::USAGE_DYNAMIC) != 0 ? D3D11_USAGE_STAGING : D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE; //TODO
		desc.CPUAccessFlags = (format.type() & SurfaceFormat::SURFACE_X8R8G8B8) != 0 ? D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ : 0;
		desc.MiscFlags = 0;

		if (FAILED(device->CreateTexture2D(&desc, 0, &id3d11texture2d3c)))
			throw GraphicsException(Format("Creating texture failed"));

		if ((desc.BindFlags & D3D11_BIND_RENDER_TARGET) != 0)
		{
			D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
			renderTargetViewDesc.Format = desc.Format;
			renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

			if (FAILED(device->CreateRenderTargetView(id3d11texture2d3c, &renderTargetViewDesc, &pid3d11rendertargetview44)))
				throw GraphicsException(Format("Creating RenderTargetView for Texture failed"));
		}

		if ((desc.BindFlags & D3D11_BIND_SHADER_RESOURCE) != 0)
		{
			D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
			shaderResourceViewDesc.Format = desc.Format;
			shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
			shaderResourceViewDesc.Buffer.FirstElement = -1;

			if (FAILED(device->CreateShaderResourceView(id3d11texture2d3c, &shaderResourceViewDesc, &pid3d11shaderresourceview40)))
				throw GraphicsException(Format("Creating ShaderResourceView for Texture failed"));
		}
	}

	int DX11_Texture::width() const //1000CD20
	{
		return m_width;
	}

	int DX11_Texture::height() const //10007E90
	{
		return m_height;
	}

	SurfaceFormat DX11_Texture::format() const //1000CD30
	{
		return m_format;
	}

	void DX11_Texture::blt(int x, int y, const void* data, int pitch, int miplevel, int w, int h, const img::SurfaceFormat& fmt) //1000CD50
	{
		ID3D11DeviceContext* deviceContext = m_context->deviceContext();
		
		D3D11_BOX dstBox;
		dstBox.left = x;
		dstBox.right = w + x;
		dstBox.top = y;
		dstBox.front = 0;
		dstBox.bottom = h + y;
		dstBox.back = 1;

		D3D11_TEXTURE2D_DESC desc;
		id3d11texture2d3c->GetDesc(&desc);
		
		deviceContext->UpdateSubresource(id3d11texture2d3c, miplevel, &dstBox, data, fmt.getMemoryUsage(w, 1), 0);
	}

	void DX11_Texture::clear()
	{
	}

	void DX11_Texture::lock(LockType lock) //Blank!
	{
	}

	void DX11_Texture::unlock() //Blank!
	{
	}

	Rect DX11_Texture::rect() const //1000CCF0
	{
		return Rect(width(), height());
	}

	[[noreturn]] void DX11_Texture::getData(void** bits, int* pitch) const //1000D1C0
	{
		throw Exception(Format("getData() is not supported on DX11"));
	}

	const std::string& DX11_Texture::getName() const //1000CD40
	{
		return m_name;
	}

	void DX11_Texture::setName(const std::string& name) //1000C8C0
	{
		m_name = name;
	}
}