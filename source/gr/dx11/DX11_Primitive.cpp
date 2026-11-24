#include <gr/dx11/DX11_common.h>
#include <gr/dx11/DX11_Primitive.h>
#include <gr/dx11/DX11_Context.h>

namespace gr
{
	DX11_Primitive::DX11_Primitive(DX11_Context* context, PrimType prim, const VertexFormat& vf, int vertices, int indices, Context::UsageFlags usage) : //1000B980
		m_context(context),
		m_prim(prim),
		//vf(),
		//m_v
		//m_in
		m_usage(usage)
	{
		m_context->deviceContext();
	}

	DX11_Primitive::~DX11_Primitive()
	{
		deallocate();
	}

	void DX11_Primitive::lock(LockType lock) //
	{
		m_locked = lock;
	}

	/*void sub_1000A2B0(ID3D11InputLayout* inputLayout)?
	{
		m_fx->
		throw GraphicsException(Format("Couldn't get pass description"));
		throw GraphicsException(Format("Couldn't get shader description"));
		throw GraphicsException(Format("Couldn't get vertex shader description"));

		ID3D11Device* device = m_context->device();
		if (FAILED(device->CreateInputLayout(
		throw GraphicsException(Format("Failed to create a input layout."));
	}
	*/

	void DX11_Primitive::setShader(Shader* shader) //10009990
	{
		m_fx = (DX11_Shader*)shader;
	}

	void DX11_Primitive::render() //1000B420 | TODO
	{
		//DX11_Context* context = m_context;
		//Shader::SortType sort = context->sort();
		//if (m_fx->sort() && m_prim == PRIM_TRI)
		//{
		//	int tricount = triangleListSize();
		//	if (tricount > 0) // don't sort lines, strips or fans
		//	{
		//		Lock lk(this, LOCK_READWRITE);
		//
		//		//switch (m_fx->sort())
		//		//{
		//		//case Shader::SORT_OUTSIDEIN:
		//		//	sortOutsideIn(m_context->sortbuffer);
		//		//	break;
		//		//
		//		//case Shader::SORT_INSIDEOUT:
		//		//	sortInsideOut(m_context->sortbuffer);
		//		//	break;
		//		//
		//		//case Shader::SORT_FRONTTOBACK:
		//		//	sortFrontToBack(context->camerapos.xyz(), context->worldtm, context->boneworldtm.begin(), context->boneworldtm.size(), context->sortbuffer);
		//		//	break;
		//		//
		//		//case Shader::SORT_BACKTOFRONT:
		//		//	sortBackToFront(context->camerapos.xyz(), context->worldtm, context->boneworldtm.begin(), context->boneworldtm.size(), context->sortbuffer);
		//		//	break;
		//		//}
		//	}
		//}
		//
		//ID3D11DeviceContext* deviceContext;
		//
		//deviceContext->IASetInputLayout(pid3d11inputlayout124);
		//
		//D3D_PRIMITIVE_TOPOLOGY topology;
		//switch (m_prim)
		//{
		//case PRIM_POINT:
		//	topology = D3D_PRIMITIVE_TOPOLOGY_POINTLIST;
		//	break;
		//case PRIM_LINE:
		//	topology = D3D_PRIMITIVE_TOPOLOGY_LINELIST;
		//	break;
		//case PRIM_LINESTRIP:
		//	topology = D3D_PRIMITIVE_TOPOLOGY_LINESTRIP;
		//	break;
		//case PRIM_TRI:
		//	topology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		//	break;
		//case PRIM_TRISTRIP:
		//	topology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
		//	break;
		//default:
		//	topology = D3D_PRIMITIVE_TOPOLOGY_UNDEFINED;
		//	break;
		//}
		//
		//deviceContext->IASetPrimitiveTopology(topology);
		//
		//if (!pid3d11buffer100)
		//{
		//	deviceContext->IASetIndexBuffer(pid3d11buffer100, DXGI_FORMAT_R16_UINT, 0);
		//	deviceContext->DrawIndexed(indices(), m_indexRangeBegin, 0);
		//}
		//
		//else
		//	deviceContext->Draw(vertexRangeEnd() - vertexRangeBegin(), vertexRangeBegin());
	}

	void DX11_Primitive::getVertexDataPtr(VertexFormat::DataType dt, uint8_t** data, int* pitch) //10009880 | TODO
	{
	}
	
	void DX11_Primitive::getIndexDataPtr(uint16_t** data, int* indexsize) //10008F00
	{
		if (indices() > 0)
		{
			ID3D11DeviceContext* deviceContext;
			D3D11_MAPPED_SUBRESOURCE subRes;

			//deviceContext->Map(pid3d11buffer100, 0, D3D11_MAP_WRITE_DISCARD, 0, &subRes);

			// = subRes.pData?

			*data = (uint16_t*)subRes.pData;
			*indexsize = 2;
		}
	}

	Primitive::PrimType DX11_Primitive::type() const //10008EF0
	{
		return m_prim;
	}

	Shader* DX11_Primitive::shader() const //10009010
	{
		return m_fx;
	}

	void DX11_Primitive::allocate(const VertexFormat& vf, int vertices, int indices) //1000A9D0 | TODO
	{
		//m_context->deviceContext();
	}

	void DX11_Primitive::deallocate() //1000A000
	{
		//m_context->sub_10002020();
	}
}